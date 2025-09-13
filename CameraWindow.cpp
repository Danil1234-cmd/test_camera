#include "CameraWindow.h"
#include "ui_CameraWindow.h"

#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QCoreApplication>
#include <QDebug>

CameraWindow::CameraWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CameraWindow)
{
    ui->setupUi(this);

    // Подключаем кнопки
    connect(ui->captureButton, &QPushButton::clicked, this, &CameraWindow::takePhoto);
    //connect(ui->exitButton, &QPushButton::clicked, this, &CameraWindow::close);

    // Обновляем список камер
    updateCameraList();

    // Если есть хоть одна камера — сразу выбрать первую
    if (ui->comboBoxCamera->count() > 0) {
        ui->comboBoxCamera->setCurrentIndex(0);
        onCameraChanged(0);
    }
}

CameraWindow::~CameraWindow()
{
    // Отключаем сессию
#if QT_VERSION >= 0x060000
    m_captureSession.setCamera(nullptr);
    m_captureSession.setImageCapture(nullptr);
    m_captureSession.setVideoOutput(nullptr);
#endif

    if (m_camera) {
        m_camera->stop();
        m_camera->deleteLater();
        m_camera = nullptr;
    }
    if (m_imageCapture) {
        m_imageCapture->deleteLater();
        m_imageCapture = nullptr;
    }

    delete ui;
}

void CameraWindow::updateCameraList()
{
    ui->comboBoxCamera->blockSignals(true);
    ui->comboBoxCamera->clear();

    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : cameras) {
        // Фильтрация: игнорируем фантомные устройства (ACPI и т.п.)
        const QString desc = cameraDevice.description();
        if (desc.contains("WebCam", Qt::CaseInsensitive) ||
            desc.contains("Camera", Qt::CaseInsensitive)) {
            ui->comboBoxCamera->addItem(desc, QVariant::fromValue(cameraDevice));
        } else {
            qDebug() << "Игнорируем устройство:" << desc;
        }
    }

    ui->comboBoxCamera->blockSignals(false);
}

void CameraWindow::setupCamera(const QCameraDevice &cameraDevice)
{
    if (cameraDevice.isNull()) {
        QMessageBox::warning(this, "Camera", "Выбрана некорректная камера");
        return;
    }

    // Отключаем сессию от старых объектов
#if QT_VERSION >= 0x060000
    m_captureSession.setCamera(nullptr);
    m_captureSession.setImageCapture(nullptr);
    m_captureSession.setVideoOutput(nullptr);
#endif

    if (m_camera) {
        disconnect(m_camera, nullptr, this, nullptr);
        m_camera->stop();
        m_camera->deleteLater();
        m_camera = nullptr;
    }
    if (m_imageCapture) {
        disconnect(m_imageCapture, nullptr, this, nullptr);
        m_imageCapture->deleteLater();
        m_imageCapture = nullptr;
    }

    QCoreApplication::processEvents(QEventLoop::AllEvents, 50);

    // Создаём новые объекты
    m_camera = new QCamera(cameraDevice, this);
    m_imageCapture = new QImageCapture(this);

#if QT_VERSION >= 0x060000
    m_captureSession.setCamera(m_camera);
    m_captureSession.setImageCapture(m_imageCapture);
    m_captureSession.setVideoOutput(ui->viewfinderWidget);
#else
    m_camera->setViewfinder(ui->viewfinderWidget);
    m_camera->setCaptureMode(QCamera::CaptureStillImage);
    m_imageCapture->setCaptureDestination(QImageCapture::CaptureToFile);
#endif

    connect(m_imageCapture, &QImageCapture::imageSaved,
            this, &CameraWindow::imageSaved);
    connect(m_imageCapture, &QImageCapture::errorOccurred,
            this, &CameraWindow::errorOccurred);

    m_camera->start();

    if (m_camera->error() != QCamera::NoError) {
        QMessageBox::critical(this, "Camera Error",
                              "Не удалось инициализировать камеру: " + m_camera->errorString());
        m_camera->deleteLater();
        m_camera = nullptr;
    }
}

void CameraWindow::onCameraChanged(int index)
{
    if (index < 0) return;

    QVariant data = ui->comboBoxCamera->itemData(index);
    if (!data.isValid()) return;

    QCameraDevice device = data.value<QCameraDevice>();
    setupCamera(device);
}

void CameraWindow::takePhoto()
{
    if (!m_camera || !m_imageCapture) return;

    QString picturesDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QDir dir(picturesDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString fileName = picturesDir + "/photo_" +
                       QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".jpg";

    m_imageCapture->captureToFile(fileName);
}

void CameraWindow::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    ui->statusLabel->setText("Фото сохранено: " + fileName);
}

void CameraWindow::errorOccurred(int id, QImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, "Ошибка", "Ошибка при сохранении изображения: " + errorString);
}

void CameraWindow::setSavePath(const QString &path)
{
    QString expandedPath = path;
    expandedPath.replace("~", QStandardPaths::writableLocation(QStandardPaths::HomeLocation));

    m_savePath = expandedPath;
    if (!m_savePath.endsWith("/") && !m_savePath.endsWith("\\")) {
        m_savePath += "/";
    }

    QDir dir;
    if (!dir.exists(m_savePath)) {
        if (!dir.mkpath(m_savePath)) {
            QMessageBox::warning(this, "Error", "Cannot create directory: " + m_savePath);
            return;
        }
    }

    if (ui && ui->statusLabel) {
        ui->statusLabel->setText("Путь для сохранения: " + m_savePath);
    }
}
