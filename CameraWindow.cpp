#include "CameraWindow.h"
#include "ui_CameraWindow.h"
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>

CameraWindow::CameraWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraWindow),
    m_camera(nullptr),
    m_imageCapture(nullptr)
{
    ui->setupUi(this);

    // Настраиваем камеру
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty()) {
        QMessageBox::warning(this, "Camera", "No cameras found");
        return;
    }

    m_camera.reset(new QCamera(cameras.first()));
    m_imageCapture.reset(new QImageCapture);

#if QT_VERSION >= 0x060000
    // Настройка для Qt6
    m_captureSession.setCamera(m_camera.get());
    m_captureSession.setImageCapture(m_imageCapture.get());
    m_captureSession.setVideoOutput(ui->viewfinderWidget);
#else
    // Настройка для Qt5
    m_camera->setViewfinder(ui->viewfinderWidget);
    m_camera->setCaptureMode(QCamera::CaptureStillImage);
    m_imageCapture->setCaptureDestination(QImageCapture::CaptureToFile);
#endif

    connect(ui->captureButton, &QPushButton::clicked, this, &CameraWindow::takePhoto);
    connect(m_imageCapture.get(), &QImageCapture::imageSaved, this, &CameraWindow::imageSaved);
    connect(m_imageCapture.get(), &QImageCapture::errorOccurred, this, &CameraWindow::errorOccurred);

    m_camera->start();
}

CameraWindow::~CameraWindow()
{
    delete ui;
}

void CameraWindow::setSavePath(const QString &path)
{
    // Раскрываем тильду и другие специальные символы в пути
    QString expandedPath = path;
    expandedPath.replace("~", QStandardPaths::writableLocation(QStandardPaths::HomeLocation));

    m_savePath = expandedPath;

    // Убеждаемся, что путь заканчивается на "/"
    if (!m_savePath.endsWith("/") && !m_savePath.endsWith("\\")) {
        m_savePath += "/";
    }

    // Создаем папку для сохранения фото
    QDir dir;
    if (!dir.exists(m_savePath)) {
        if (!dir.mkpath(m_savePath)) {
            QMessageBox::warning(this, "Error", "Cannot create directory: " + m_savePath);
            return;
        }
    } else {
    }

    ui->statusLabel->setText("Save path: " + m_savePath);
}

void CameraWindow::takePhoto()
{
    if (m_imageCapture->isReadyForCapture()) {
        QString fileName = QString("photo_%1.jpg")
                               .arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
        QString fullPath = m_savePath + fileName;

        ui->statusLabel->setText("Capturing: " + fileName);
        m_imageCapture->captureToFile(fullPath);
    } else {
        ui->statusLabel->setText("Not ready for capture");
    }
}

void CameraWindow::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id)
    ui->statusLabel->setText("Saved: " + fileName);

    // Проверяем, что файл действительно создан
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists()) {
        ui->statusLabel->setText("Success: " + fileName);
    } else {
        ui->statusLabel->setText("File not found: " + fileName);
    }
}

void CameraWindow::errorOccurred(int id, QImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id)
    Q_UNUSED(error)
    ui->statusLabel->setText("Error: " + errorString);
    QMessageBox::warning(this, "Capture Error", errorString);
}
