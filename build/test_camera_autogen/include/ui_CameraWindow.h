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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topLayout;
    QComboBox *cameraCombo;
    QPushButton *startButton;
    QPushButton *stopButton;
    QWidget *viewfinderPlaceholder;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CameraWindow)
    {
        if (CameraWindow->objectName().isEmpty())
            CameraWindow->setObjectName("CameraWindow");
        CameraWindow->resize(800, 600);
        centralwidget = new QWidget(CameraWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        topLayout = new QHBoxLayout();
        topLayout->setObjectName("topLayout");
        cameraCombo = new QComboBox(centralwidget);
        cameraCombo->setObjectName("cameraCombo");

        topLayout->addWidget(cameraCombo);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");

        topLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");

        topLayout->addWidget(stopButton);


        verticalLayout->addLayout(topLayout);

        viewfinderPlaceholder = new QWidget(centralwidget);
        viewfinderPlaceholder->setObjectName("viewfinderPlaceholder");
        viewfinderPlaceholder->setMinimumSize(QSize(640, 480));

        verticalLayout->addWidget(viewfinderPlaceholder);

        CameraWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(CameraWindow);
        statusbar->setObjectName("statusbar");
        CameraWindow->setStatusBar(statusbar);

        retranslateUi(CameraWindow);

        QMetaObject::connectSlotsByName(CameraWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CameraWindow)
    {
        CameraWindow->setWindowTitle(QCoreApplication::translate("CameraWindow", "Camera selector", nullptr));
        startButton->setText(QCoreApplication::translate("CameraWindow", "Start", nullptr));
        stopButton->setText(QCoreApplication::translate("CameraWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraWindow: public Ui_CameraWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWINDOW_H
