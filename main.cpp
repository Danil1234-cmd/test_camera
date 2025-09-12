#include "CameraWindow.h"
#include <QApplication>
#include <QDir>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraWindow w;

    // Заменяем тильду на абсолютный путь
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString savePath = homeDir + "/projects/camera/build/test_barcodes/";

    w.setSavePath(savePath);

    w.show();
    return a.exec();
}
