/********************************************************************************
** Form generated from reading UI file 'WelcomeDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEDIALOG_H
#define UI_WELCOMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WelcomDialogClass
{
public:
    QPushButton *userLoginBtn;
    QPushButton *adminLoginBtn;
    QPushButton *exitBtn;

    void setupUi(QDialog *WelcomDialogClass)
    {
        if (WelcomDialogClass->objectName().isEmpty())
            WelcomDialogClass->setObjectName("WelcomDialogClass");
        WelcomDialogClass->resize(600, 400);
        userLoginBtn = new QPushButton(WelcomDialogClass);
        userLoginBtn->setObjectName("userLoginBtn");
        userLoginBtn->setGeometry(QRect(20, 30, 81, 24));
        adminLoginBtn = new QPushButton(WelcomDialogClass);
        adminLoginBtn->setObjectName("adminLoginBtn");
        adminLoginBtn->setGeometry(QRect(20, 70, 81, 24));
        exitBtn = new QPushButton(WelcomDialogClass);
        exitBtn->setObjectName("exitBtn");
        exitBtn->setGeometry(QRect(20, 110, 81, 24));

        retranslateUi(WelcomDialogClass);

        QMetaObject::connectSlotsByName(WelcomDialogClass);
    } // setupUi

    void retranslateUi(QDialog *WelcomDialogClass)
    {
        WelcomDialogClass->setWindowTitle(QCoreApplication::translate("WelcomDialogClass", "WelcomDialog", nullptr));
        userLoginBtn->setText(QCoreApplication::translate("WelcomDialogClass", "PushButton", nullptr));
        adminLoginBtn->setText(QCoreApplication::translate("WelcomDialogClass", "PushButton", nullptr));
        exitBtn->setText(QCoreApplication::translate("WelcomDialogClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomDialogClass: public Ui_WelcomDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEDIALOG_H
