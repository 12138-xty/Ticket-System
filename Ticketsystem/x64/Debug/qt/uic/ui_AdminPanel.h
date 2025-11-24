/********************************************************************************
** Form generated from reading UI file 'AdminPanel.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPANEL_H
#define UI_ADMINPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AdminPanel
{
public:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QLabel *captchaLabel;
    QHBoxLayout *captchaLayout;
    QLineEdit *captchaEdit;
    QLabel *captchaDisplay;
    QPushButton *refreshCaptchaButton;
    QCheckBox *rememberPasswordCheckBox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *buttonLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *exitButton;
    QLabel *securityNoticeLabel;

    void setupUi(QDialog *AdminPanel)
    {
        if (AdminPanel->objectName().isEmpty())
            AdminPanel->setObjectName("AdminPanel");
        AdminPanel->resize(450, 350);
        AdminPanel->setMinimumSize(QSize(450, 350));
        mainLayout = new QVBoxLayout(AdminPanel);
        mainLayout->setObjectName("mainLayout");
        titleLabel = new QLabel(AdminPanel);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(titleLabel);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainLayout->addItem(verticalSpacer);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(AdminPanel);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, usernameLabel);

        usernameEdit = new QLineEdit(AdminPanel);
        usernameEdit->setObjectName("usernameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameEdit);

        passwordLabel = new QLabel(AdminPanel);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, passwordLabel);

        passwordEdit = new QLineEdit(AdminPanel);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, passwordEdit);

        captchaLabel = new QLabel(AdminPanel);
        captchaLabel->setObjectName("captchaLabel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, captchaLabel);

        captchaLayout = new QHBoxLayout();
        captchaLayout->setObjectName("captchaLayout");
        captchaEdit = new QLineEdit(AdminPanel);
        captchaEdit->setObjectName("captchaEdit");
        captchaEdit->setMaximumWidth(100);

        captchaLayout->addWidget(captchaEdit);

        captchaDisplay = new QLabel(AdminPanel);
        captchaDisplay->setObjectName("captchaDisplay");
        captchaDisplay->setAlignment(Qt::AlignCenter);
        captchaDisplay->setMinimumWidth(80);

        captchaLayout->addWidget(captchaDisplay);

        refreshCaptchaButton = new QPushButton(AdminPanel);
        refreshCaptchaButton->setObjectName("refreshCaptchaButton");
        refreshCaptchaButton->setMaximumWidth(60);

        captchaLayout->addWidget(refreshCaptchaButton);


        formLayout->setLayout(2, QFormLayout::ItemRole::FieldRole, captchaLayout);


        mainLayout->addLayout(formLayout);

        rememberPasswordCheckBox = new QCheckBox(AdminPanel);
        rememberPasswordCheckBox->setObjectName("rememberPasswordCheckBox");

        mainLayout->addWidget(rememberPasswordCheckBox);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainLayout->addItem(verticalSpacer_2);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        loginButton = new QPushButton(AdminPanel);
        loginButton->setObjectName("loginButton");

        buttonLayout->addWidget(loginButton);

        registerButton = new QPushButton(AdminPanel);
        registerButton->setObjectName("registerButton");

        buttonLayout->addWidget(registerButton);

        exitButton = new QPushButton(AdminPanel);
        exitButton->setObjectName("exitButton");

        buttonLayout->addWidget(exitButton);


        mainLayout->addLayout(buttonLayout);

        securityNoticeLabel = new QLabel(AdminPanel);
        securityNoticeLabel->setObjectName("securityNoticeLabel");
        securityNoticeLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(securityNoticeLabel);


        retranslateUi(AdminPanel);

        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(AdminPanel);
    } // setupUi

    void retranslateUi(QDialog *AdminPanel)
    {
        AdminPanel->setWindowTitle(QCoreApplication::translate("AdminPanel", "\347\256\241\347\220\206\345\221\230\347\231\273\345\275\225 - \351\223\201\350\267\257\347\245\250\345\212\241\347\263\273\347\273\237", nullptr));
        AdminPanel->setStyleSheet(QCoreApplication::translate("AdminPanel", "\n"
"				QDialog {\n"
"				background-color: #f5f5f5;\n"
"				}\n"
"				QLabel#titleLabel {\n"
"				font-size: 18px;\n"
"				font-weight: bold;\n"
"				color: #2c3e50;\n"
"				}\n"
"				QLineEdit {\n"
"				padding: 8px;\n"
"				border: 1px solid #ddd;\n"
"				border-radius: 4px;\n"
"				background-color: white;\n"
"				}\n"
"				QLineEdit:focus {\n"
"				border-color: #3498db;\n"
"				}\n"
"				QPushButton {\n"
"				padding: 8px 16px;\n"
"				border: none;\n"
"				border-radius: 4px;\n"
"				font-weight: bold;\n"
"				}\n"
"				QPushButton#loginButton {\n"
"				background-color: #3498db;\n"
"				color: white;\n"
"				}\n"
"				QPushButton#loginButton:hover {\n"
"				background-color: #2980b9;\n"
"				}\n"
"				QPushButton#registerButton {\n"
"				background-color: #27ae60;\n"
"				color: white;\n"
"				}\n"
"				QPushButton#registerButton:hover {\n"
"				background-color: #229954;\n"
"				}\n"
"				QPushButton#exitButton {\n"
"				background-color: #e74c3c;\n"
"				color: white;\n"
"				}\n"
"				QPushButton#e"
                        "xitButton:hover {\n"
"				background-color: #c0392b;\n"
"				}\n"
"				QCheckBox {\n"
"				spacing: 5px;\n"
"				}\n"
"				QCheckBox::indicator {\n"
"				width: 16px;\n"
"				height: 16px;\n"
"				}\n"
"			", nullptr));
        titleLabel->setText(QCoreApplication::translate("AdminPanel", "\347\256\241\347\220\206\345\221\230\347\231\273\345\275\225", nullptr));
        usernameLabel->setText(QCoreApplication::translate("AdminPanel", "\347\256\241\347\220\206\345\221\230\350\264\246\345\217\267\357\274\232", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("AdminPanel", "\350\257\267\350\276\223\345\205\245\347\256\241\347\220\206\345\221\230\350\264\246\345\217\267", nullptr));
        passwordLabel->setText(QCoreApplication::translate("AdminPanel", "\347\231\273\345\275\225\345\257\206\347\240\201\357\274\232", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("AdminPanel", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        captchaLabel->setText(QCoreApplication::translate("AdminPanel", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        captchaEdit->setPlaceholderText(QCoreApplication::translate("AdminPanel", "\350\276\223\345\205\245\351\252\214\350\257\201\347\240\201", nullptr));
        captchaDisplay->setText(QCoreApplication::translate("AdminPanel", "ABCD", nullptr));
        captchaDisplay->setStyleSheet(QCoreApplication::translate("AdminPanel", "\n"
"											background-color: #ecf0f1;\n"
"											border: 1px solid #bdc3c7;\n"
"											padding: 5px;\n"
"											font-weight: bold;\n"
"											letter-spacing: 2px;\n"
"											color: #2c3e50;\n"
"										", nullptr));
        refreshCaptchaButton->setText(QCoreApplication::translate("AdminPanel", "\345\210\267\346\226\260", nullptr));
        rememberPasswordCheckBox->setText(QCoreApplication::translate("AdminPanel", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        loginButton->setText(QCoreApplication::translate("AdminPanel", "\347\231\273\345\275\225", nullptr));
        registerButton->setText(QCoreApplication::translate("AdminPanel", "\346\263\250\345\206\214\347\256\241\347\220\206\345\221\230", nullptr));
        exitButton->setText(QCoreApplication::translate("AdminPanel", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
        securityNoticeLabel->setText(QCoreApplication::translate("AdminPanel", "\346\263\250\346\204\217\357\274\232\346\255\244\347\225\214\351\235\242\344\273\205\351\231\220\346\216\210\346\235\203\347\256\241\347\220\206\345\221\230\344\275\277\347\224\250\357\274\214\346\234\252\347\273\217\346\216\210\346\235\203\347\246\201\346\255\242\350\256\277\351\227\256", nullptr));
        securityNoticeLabel->setStyleSheet(QCoreApplication::translate("AdminPanel", "color: #e74c3c; font-size: 10px;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminPanel: public Ui_AdminPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPANEL_H
