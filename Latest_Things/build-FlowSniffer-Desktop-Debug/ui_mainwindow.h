/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *enter;
    QPushButton *log;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(475, 314);
        MainWindow->setStyleSheet(QString::fromUtf8("color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(150, 60, 181, 141));
        frame->setStyleSheet(QString::fromUtf8("image:url(:/flower.png)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 20, 291, 31));
        label->setStyleSheet(QString::fromUtf8("font: 63 15pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(200, 220, 101, 71));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        enter = new QPushButton(layoutWidget);
        enter->setObjectName(QString::fromUtf8("enter"));
        enter->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));

        verticalLayout->addWidget(enter);

        log = new QPushButton(layoutWidget);
        log->setObjectName(QString::fromUtf8("log"));
        log->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));

        verticalLayout->addWidget(log);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Welcome To Use Flow Sniffer!", nullptr));
        enter->setText(QApplication::translate("MainWindow", "ENTER", nullptr));
        log->setText(QApplication::translate("MainWindow", "MYLOG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
