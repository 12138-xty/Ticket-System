/********************************************************************************
** Form generated from reading UI file 'UserInfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFODIALOG_H
#define UI_USERINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserInfoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QLabel *newpasswordLabel;
    QLineEdit *newPasswordLineEdit;
    QLabel *confirmpasswordlabel;
    QLineEdit *confirmPasswordLineEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *UserInfoDialog)
    {
        if (UserInfoDialog->objectName().isEmpty())
            UserInfoDialog->setObjectName("UserInfoDialog");
        UserInfoDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(UserInfoDialog);
        verticalLayout->setObjectName("verticalLayout");
        nameLabel = new QLabel(UserInfoDialog);
        nameLabel->setObjectName("nameLabel");

        verticalLayout->addWidget(nameLabel);

        usernameLineEdit = new QLineEdit(UserInfoDialog);
        usernameLineEdit->setObjectName("usernameLineEdit");

        verticalLayout->addWidget(usernameLineEdit);

        phoneLabel = new QLabel(UserInfoDialog);
        phoneLabel->setObjectName("phoneLabel");

        verticalLayout->addWidget(phoneLabel);

        phoneLineEdit = new QLineEdit(UserInfoDialog);
        phoneLineEdit->setObjectName("phoneLineEdit");

        verticalLayout->addWidget(phoneLineEdit);

        newpasswordLabel = new QLabel(UserInfoDialog);
        newpasswordLabel->setObjectName("newpasswordLabel");

        verticalLayout->addWidget(newpasswordLabel);

        newPasswordLineEdit = new QLineEdit(UserInfoDialog);
        newPasswordLineEdit->setObjectName("newPasswordLineEdit");
        newPasswordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(newPasswordLineEdit);

        confirmpasswordlabel = new QLabel(UserInfoDialog);
        confirmpasswordlabel->setObjectName("confirmpasswordlabel");

        verticalLayout->addWidget(confirmpasswordlabel);

        confirmPasswordLineEdit = new QLineEdit(UserInfoDialog);
        confirmPasswordLineEdit->setObjectName("confirmPasswordLineEdit");
        confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(confirmPasswordLineEdit);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        saveButton = new QPushButton(UserInfoDialog);
        saveButton->setObjectName("saveButton");

        buttonLayout->addWidget(saveButton);

        cancelButton = new QPushButton(UserInfoDialog);
        cancelButton->setObjectName("cancelButton");

        buttonLayout->addWidget(cancelButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(UserInfoDialog);

        QMetaObject::connectSlotsByName(UserInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *UserInfoDialog)
    {
        UserInfoDialog->setWindowTitle(QCoreApplication::translate("UserInfoDialog", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        nameLabel->setText(QCoreApplication::translate("UserInfoDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        phoneLabel->setText(QCoreApplication::translate("UserInfoDialog", "\346\211\213\346\234\272\345\217\267\357\274\232", nullptr));
        newpasswordLabel->setText(QCoreApplication::translate("UserInfoDialog", "\346\226\260\345\257\206\347\240\201\357\274\210\347\225\231\347\251\272\345\210\231\344\270\215\344\277\256\346\224\271\357\274\211\357\274\232", nullptr));
        confirmpasswordlabel->setText(QCoreApplication::translate("UserInfoDialog", "\347\241\256\350\256\244\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        saveButton->setText(QCoreApplication::translate("UserInfoDialog", "\344\277\235\345\255\230", nullptr));
        cancelButton->setText(QCoreApplication::translate("UserInfoDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInfoDialog: public Ui_UserInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFODIALOG_H
