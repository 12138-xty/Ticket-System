/********************************************************************************
** Form generated from reading UI file 'Ticketsystem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKETSYSTEM_H
#define UI_TICKETSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TicketsystemClass
{
public:
    QWidget *centralWidget;
    QPushButton *loginButton;
    QPushButton *logoutButton;
    QPushButton *queryButton;
    QPushButton *bookButton;
    QPushButton *cancelButton;
    QPushButton *changeButton;
    QPushButton *undoButton;
    QPushButton *redoButton;
    QListWidget *trainListWidget;
    QListWidget *orderListWidget;
    QLineEdit *userIdEdit;
    QLineEdit *passwordEdit;
    QLineEdit *startStationEdit;
    QLineEdit *endStationEdit;
    QLineEdit *dateEdit;
    QLineEdit *trainIdEdit;
    QLineEdit *bookDateEdit;
    QLineEdit *orderIdEdit;
    QLabel *userStatusLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TicketsystemClass)
    {
        if (TicketsystemClass->objectName().isEmpty())
            TicketsystemClass->setObjectName("TicketsystemClass");
        TicketsystemClass->resize(838, 400);
        centralWidget = new QWidget(TicketsystemClass);
        centralWidget->setObjectName("centralWidget");
        loginButton = new QPushButton(centralWidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(10, 0, 81, 24));
        logoutButton = new QPushButton(centralWidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(10, 30, 81, 24));
        queryButton = new QPushButton(centralWidget);
        queryButton->setObjectName("queryButton");
        queryButton->setGeometry(QRect(10, 60, 81, 24));
        bookButton = new QPushButton(centralWidget);
        bookButton->setObjectName("bookButton");
        bookButton->setGeometry(QRect(10, 90, 81, 24));
        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(10, 120, 81, 24));
        changeButton = new QPushButton(centralWidget);
        changeButton->setObjectName("changeButton");
        changeButton->setGeometry(QRect(10, 150, 81, 24));
        undoButton = new QPushButton(centralWidget);
        undoButton->setObjectName("undoButton");
        undoButton->setGeometry(QRect(10, 180, 81, 24));
        redoButton = new QPushButton(centralWidget);
        redoButton->setObjectName("redoButton");
        redoButton->setGeometry(QRect(10, 210, 81, 24));
        trainListWidget = new QListWidget(centralWidget);
        trainListWidget->setObjectName("trainListWidget");
        trainListWidget->setGeometry(QRect(100, 190, 256, 192));
        orderListWidget = new QListWidget(centralWidget);
        orderListWidget->setObjectName("orderListWidget");
        orderListWidget->setGeometry(QRect(380, 190, 256, 192));
        userIdEdit = new QLineEdit(centralWidget);
        userIdEdit->setObjectName("userIdEdit");
        userIdEdit->setGeometry(QRect(120, 10, 113, 23));
        passwordEdit = new QLineEdit(centralWidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(260, 10, 113, 23));
        startStationEdit = new QLineEdit(centralWidget);
        startStationEdit->setObjectName("startStationEdit");
        startStationEdit->setGeometry(QRect(120, 40, 113, 23));
        endStationEdit = new QLineEdit(centralWidget);
        endStationEdit->setObjectName("endStationEdit");
        endStationEdit->setGeometry(QRect(260, 40, 113, 23));
        dateEdit = new QLineEdit(centralWidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(120, 70, 113, 23));
        trainIdEdit = new QLineEdit(centralWidget);
        trainIdEdit->setObjectName("trainIdEdit");
        trainIdEdit->setGeometry(QRect(260, 70, 113, 23));
        bookDateEdit = new QLineEdit(centralWidget);
        bookDateEdit->setObjectName("bookDateEdit");
        bookDateEdit->setGeometry(QRect(120, 110, 113, 23));
        orderIdEdit = new QLineEdit(centralWidget);
        orderIdEdit->setObjectName("orderIdEdit");
        orderIdEdit->setGeometry(QRect(260, 110, 113, 23));
        userStatusLabel = new QLabel(centralWidget);
        userStatusLabel->setObjectName("userStatusLabel");
        userStatusLabel->setGeometry(QRect(460, 50, 54, 16));
        TicketsystemClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TicketsystemClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 838, 33));
        TicketsystemClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TicketsystemClass);
        mainToolBar->setObjectName("mainToolBar");
        TicketsystemClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TicketsystemClass);
        statusBar->setObjectName("statusBar");
        TicketsystemClass->setStatusBar(statusBar);

        retranslateUi(TicketsystemClass);

        QMetaObject::connectSlotsByName(TicketsystemClass);
    } // setupUi

    void retranslateUi(QMainWindow *TicketsystemClass)
    {
        TicketsystemClass->setWindowTitle(QCoreApplication::translate("TicketsystemClass", "Ticketsystem", nullptr));
        loginButton->setText(QCoreApplication::translate("TicketsystemClass", "\347\231\273\345\275\225", nullptr));
        logoutButton->setText(QCoreApplication::translate("TicketsystemClass", "\351\200\200\345\207\272", nullptr));
        queryButton->setText(QCoreApplication::translate("TicketsystemClass", "\346\237\245\350\257\242", nullptr));
        bookButton->setText(QCoreApplication::translate("TicketsystemClass", "\351\242\204\350\256\242", nullptr));
        cancelButton->setText(QCoreApplication::translate("TicketsystemClass", "PushButton", nullptr));
        changeButton->setText(QCoreApplication::translate("TicketsystemClass", "PushButton", nullptr));
        undoButton->setText(QCoreApplication::translate("TicketsystemClass", "PushButton", nullptr));
        redoButton->setText(QCoreApplication::translate("TicketsystemClass", "PushButton", nullptr));
        userStatusLabel->setText(QCoreApplication::translate("TicketsystemClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TicketsystemClass: public Ui_TicketsystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKETSYSTEM_H
