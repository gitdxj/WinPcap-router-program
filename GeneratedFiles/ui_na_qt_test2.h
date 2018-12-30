/********************************************************************************
** Form generated from reading UI file 'na_qt_test2.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NA_QT_TEST2_H
#define UI_NA_QT_TEST2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NA_Qt_test2Class
{
public:
    QWidget *centralWidget;
    QTextBrowser *deviceInfo;
    QTextBrowser *contentBrowser;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *add_button;
    QLineEdit *network_line;
    QLineEdit *mask_line;
    QLineEdit *next_line;
    QTextBrowser *route_browser;
    QPushButton *route_button;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NA_Qt_test2Class)
    {
        if (NA_Qt_test2Class->objectName().isEmpty())
            NA_Qt_test2Class->setObjectName(QStringLiteral("NA_Qt_test2Class"));
        NA_Qt_test2Class->resize(905, 687);
        centralWidget = new QWidget(NA_Qt_test2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        deviceInfo = new QTextBrowser(centralWidget);
        deviceInfo->setObjectName(QStringLiteral("deviceInfo"));
        deviceInfo->setGeometry(QRect(70, 10, 651, 141));
        contentBrowser = new QTextBrowser(centralWidget);
        contentBrowser->setObjectName(QStringLiteral("contentBrowser"));
        contentBrowser->setGeometry(QRect(70, 160, 651, 191));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(70, 510, 351, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(460, 510, 93, 28));
        add_button = new QPushButton(centralWidget);
        add_button->setObjectName(QStringLiteral("add_button"));
        add_button->setGeometry(QRect(690, 580, 93, 28));
        network_line = new QLineEdit(centralWidget);
        network_line->setObjectName(QStringLiteral("network_line"));
        network_line->setGeometry(QRect(90, 580, 131, 22));
        mask_line = new QLineEdit(centralWidget);
        mask_line->setObjectName(QStringLiteral("mask_line"));
        mask_line->setGeometry(QRect(300, 580, 131, 22));
        next_line = new QLineEdit(centralWidget);
        next_line->setObjectName(QStringLiteral("next_line"));
        next_line->setGeometry(QRect(500, 580, 131, 22));
        route_browser = new QTextBrowser(centralWidget);
        route_browser->setObjectName(QStringLiteral("route_browser"));
        route_browser->setGeometry(QRect(70, 360, 651, 131));
        route_button = new QPushButton(centralWidget);
        route_button->setObjectName(QStringLiteral("route_button"));
        route_button->setGeometry(QRect(740, 370, 93, 28));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(14, 580, 61, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(240, 580, 55, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(450, 580, 55, 16));
        NA_Qt_test2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NA_Qt_test2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 905, 26));
        NA_Qt_test2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NA_Qt_test2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        NA_Qt_test2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NA_Qt_test2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        NA_Qt_test2Class->setStatusBar(statusBar);

        retranslateUi(NA_Qt_test2Class);

        QMetaObject::connectSlotsByName(NA_Qt_test2Class);
    } // setupUi

    void retranslateUi(QMainWindow *NA_Qt_test2Class)
    {
        NA_Qt_test2Class->setWindowTitle(QApplication::translate("NA_Qt_test2Class", "NA_Qt_test2", 0));
        pushButton->setText(QApplication::translate("NA_Qt_test2Class", "send", 0));
        add_button->setText(QApplication::translate("NA_Qt_test2Class", "add", 0));
        route_button->setText(QApplication::translate("NA_Qt_test2Class", "show route", 0));
        label->setText(QApplication::translate("NA_Qt_test2Class", "network:", 0));
        label_2->setText(QApplication::translate("NA_Qt_test2Class", "mask:", 0));
        label_3->setText(QApplication::translate("NA_Qt_test2Class", "next:", 0));
    } // retranslateUi

};

namespace Ui {
    class NA_Qt_test2Class: public Ui_NA_Qt_test2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NA_QT_TEST2_H
