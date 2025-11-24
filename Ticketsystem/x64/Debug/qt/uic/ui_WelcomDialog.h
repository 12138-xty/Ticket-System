/********************************************************************************
** Form generated from reading UI file 'WelcomDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMDIALOG_H
#define UI_WELCOMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_WelcomDialogClass
{
public:

    void setupUi(QDialog *WelcomDialogClass)
    {
        if (WelcomDialogClass->objectName().isEmpty())
            WelcomDialogClass->setObjectName("WelcomDialogClass");
        WelcomDialogClass->resize(600, 400);

        retranslateUi(WelcomDialogClass);

        QMetaObject::connectSlotsByName(WelcomDialogClass);
    } // setupUi

    void retranslateUi(QDialog *WelcomDialogClass)
    {
        WelcomDialogClass->setWindowTitle(QCoreApplication::translate("WelcomDialogClass", "WelcomDialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomDialogClass: public Ui_WelcomDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMDIALOG_H
