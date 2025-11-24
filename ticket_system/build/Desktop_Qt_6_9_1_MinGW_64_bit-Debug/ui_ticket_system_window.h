/********************************************************************************
** Form generated from reading UI file 'ticket_system_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKET_SYSTEM_WINDOW_H
#define UI_TICKET_SYSTEM_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ticket_system_Window
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Ticket_system_Window)
    {
        if (Ticket_system_Window->objectName().isEmpty())
            Ticket_system_Window->setObjectName("Ticket_system_Window");
        Ticket_system_Window->resize(800, 600);
        centralwidget = new QWidget(Ticket_system_Window);
        centralwidget->setObjectName("centralwidget");
        Ticket_system_Window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Ticket_system_Window);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        Ticket_system_Window->setMenuBar(menubar);
        statusbar = new QStatusBar(Ticket_system_Window);
        statusbar->setObjectName("statusbar");
        Ticket_system_Window->setStatusBar(statusbar);

        retranslateUi(Ticket_system_Window);

        QMetaObject::connectSlotsByName(Ticket_system_Window);
    } // setupUi

    void retranslateUi(QMainWindow *Ticket_system_Window)
    {
        Ticket_system_Window->setWindowTitle(QCoreApplication::translate("Ticket_system_Window", "Ticket_system_Window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ticket_system_Window: public Ui_Ticket_system_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKET_SYSTEM_WINDOW_H
