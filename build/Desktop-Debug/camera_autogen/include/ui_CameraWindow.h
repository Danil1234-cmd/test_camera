/********************************************************************************
** Form generated from reading UI file 'CameraWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAWINDOW_H
#define UI_CAMERAWINDOW_H

#include <QtCore/QVariant>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CameraWindow
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *comboBoxCamera;
    QVideoWidget *viewfinderWidget;
    QLabel *statusLabel;
    QPushButton *captureButton;

    void setupUi(QDialog *CameraWindow)
    {
        if (CameraWindow->objectName().isEmpty())
            CameraWindow->setObjectName("CameraWindow");
        CameraWindow->resize(640, 480);
        verticalLayout = new QVBoxLayout(CameraWindow);
        verticalLayout->setObjectName("verticalLayout");
        comboBoxCamera = new QComboBox(CameraWindow);
        comboBoxCamera->setObjectName("comboBoxCamera");

        verticalLayout->addWidget(comboBoxCamera);

        viewfinderWidget = new QVideoWidget(CameraWindow);
        viewfinderWidget->setObjectName("viewfinderWidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(viewfinderWidget->sizePolicy().hasHeightForWidth());
        viewfinderWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(viewfinderWidget);

        statusLabel = new QLabel(CameraWindow);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        captureButton = new QPushButton(CameraWindow);
        captureButton->setObjectName("captureButton");

        verticalLayout->addWidget(captureButton);


        retranslateUi(CameraWindow);

        QMetaObject::connectSlotsByName(CameraWindow);
    } // setupUi

    void retranslateUi(QDialog *CameraWindow)
    {
        CameraWindow->setWindowTitle(QCoreApplication::translate("CameraWindow", "Camera", nullptr));
        comboBoxCamera->setProperty("fdsfsaf", QVariant(QString()));
        statusLabel->setText(QCoreApplication::translate("CameraWindow", "Ready", nullptr));
        captureButton->setText(QCoreApplication::translate("CameraWindow", "Take Photo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraWindow: public Ui_CameraWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWINDOW_H
