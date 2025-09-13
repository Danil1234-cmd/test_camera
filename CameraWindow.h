#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QDialog>
#include <QCamera>
#include <QImageCapture>
#include <QMediaDevices>
#include <QScopedPointer>

#if QT_VERSION >= 0x060000
#include <QVideoWidget>
#include <QMediaCaptureSession>
#else
#include <QCameraViewfinder>
#endif

namespace Ui {
class CameraWindow;
}

class CameraWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent = nullptr);
    ~CameraWindow();

    // Метод для установки пути сохранения
    void setSavePath(const QString &path);

private slots:
    void takePhoto();
    void imageSaved(int id, const QString &fileName);
    void errorOccurred(int id, QImageCapture::Error error, const QString &errorString);

    /*void onCameraSelected(int index);*/
    void onCameraChanged(int index);

private:
    Ui::CameraWindow *ui;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QImageCapture> m_imageCapture;

#if QT_VERSION >= 0x060000
    QMediaCaptureSession m_captureSession;
#endif

    QString m_savePath;
    QList<QCameraDevice> m_availableCameras;

    /*void choiceCameraFunc(const QString &cameraName);*/
    void setupCamera(const QCameraDevice &cameraDevice);
    void updateCameraList();

};

#endif // CAMERAWINDOW_H
