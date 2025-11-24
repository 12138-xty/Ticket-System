/********************************************************************************
** Form generated from reading UI file 'LoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *mainLayout;
    QSpacerItem *topSpacer;
    QFrame *loginFrame;
    QVBoxLayout *frameLayout;
    QLabel *titleLabel;
    QSpacerItem *titleSpacer;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QCheckBox *rememberCheckBox;
    QLabel *colorHintLabel;
    QSpacerItem *formSpacer;
    QVBoxLayout *buttonLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *exitButton;
    QSpacerItem *bottomSpacer;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 380);
        LoginDialog->setMinimumSize(QSize(400, 380));
        mainLayout = new QVBoxLayout(LoginDialog);
        mainLayout->setObjectName("mainLayout");
        topSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainLayout->addItem(topSpacer);

        loginFrame = new QFrame(LoginDialog);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        frameLayout = new QVBoxLayout(loginFrame);
        frameLayout->setObjectName("frameLayout");
        titleLabel = new QLabel(loginFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        frameLayout->addWidget(titleLabel);

        titleSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        frameLayout->addItem(titleSpacer);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(loginFrame);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, usernameLabel);

        usernameEdit = new QLineEdit(loginFrame);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setClearButtonEnabled(true);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameEdit);

        passwordLabel = new QLabel(loginFrame);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, passwordLabel);

        passwordEdit = new QLineEdit(loginFrame);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, passwordEdit);


        frameLayout->addLayout(formLayout);

        rememberCheckBox = new QCheckBox(loginFrame);
        rememberCheckBox->setObjectName("rememberCheckBox");
        rememberCheckBox->setChecked(false);

        frameLayout->addWidget(rememberCheckBox);

        colorHintLabel = new QLabel(loginFrame);
        colorHintLabel->setObjectName("colorHintLabel");
        colorHintLabel->setAlignment(Qt::AlignCenter);

        frameLayout->addWidget(colorHintLabel);

        formSpacer = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        frameLayout->addItem(formSpacer);

        buttonLayout = new QVBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");

        buttonLayout->addWidget(loginButton);

        registerButton = new QPushButton(loginFrame);
        registerButton->setObjectName("registerButton");

        buttonLayout->addWidget(registerButton);

        exitButton = new QPushButton(loginFrame);
        exitButton->setObjectName("exitButton");

        buttonLayout->addWidget(exitButton);


        frameLayout->addLayout(buttonLayout);


        mainLayout->addWidget(loginFrame);

        bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainLayout->addItem(bottomSpacer);


        retranslateUi(LoginDialog);

        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\351\223\201\350\267\257\347\245\250\345\212\241\347\263\273\347\273\237 - \347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        LoginDialog->setStyleSheet(QCoreApplication::translate("LoginDialog", "\n"
"				QDialog {\n"
"				background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"				stop: 0 #667eea, stop: 1 #764ba2);\n"
"				font-family: \"Microsoft YaHei\", \"Segoe UI\";\n"
"				}\n"
"				QFrame#loginFrame {\n"
"				background-color: white;\n"
"				border-radius: 10px;\n"
"				padding: 20px;\n"
"				}\n"
"				QLabel#titleLabel {\n"
"				font-size: 24px;\n"
"				font-weight: bold;\n"
"				color: #2d3748;\n"
"				padding: 10px;\n"
"				}\n"
"				QLabel {\n"
"				color: #4a5568;\n"
"				font-weight: 500;\n"
"				}\n"
"				QLabel#colorHintLabel {\n"
"				font-size: 12px;\n"
"				color: #718096;\n"
"				margin-top: 5px;\n"
"				}\n"
"				QLineEdit {\n"
"				padding: 12px;\n"
"				border: 2px solid #e2e8f0;\n"
"				border-radius: 6px;\n"
"				background-color: #f7fafc;\n"
"				font-size: 14px;\n"
"				selection-background-color: #4299e1;\n"
"				}\n"
"				QLineEdit:focus {\n"
"				border-color: #4299e1;\n"
"				background-color: white;\n"
"				}\n"
"				QLineEdit#passwordEdit {\n"
"				font-family: \"Cou"
                        "rier New\";\n"
"				}\n"
"				QPushButton {\n"
"				padding: 12px;\n"
"				border: none;\n"
"				border-radius: 6px;\n"
"				font-weight: 600;\n"
"				font-size: 14px;\n"
"				margin: 5px 0;\n"
"				color: white;\n"
"				}\n"
"				/* \350\223\235\350\211\262\346\214\211\351\222\256\357\274\232\347\231\273\345\275\225\345\212\237\350\203\275 - \350\241\245\345\205\205\345\212\237\350\203\275\350\257\264\346\230\216\346\226\207\345\255\227\346\240\267\345\274\217 */\n"
"				QPushButton#loginButton {\n"
"				background-color: #4299e1;\n"
"				}\n"
"				QPushButton#loginButton:hover {\n"
"				background-color: #3182ce;\n"
"				}\n"
"				QPushButton#loginButton:pressed {\n"
"				background-color: #2b6cb0;\n"
"				}\n"
"				/* \347\273\277\350\211\262\346\214\211\351\222\256\357\274\232\346\263\250\345\206\214\345\212\237\350\203\275 - \350\241\245\345\205\205\345\212\237\350\203\275\350\257\264\346\230\216\346\226\207\345\255\227\346\240\267\345\274\217 */\n"
"				QPushButton#registerButton {\n"
"				background-col"
                        "or: #48bb78;\n"
"				}\n"
"				QPushButton#registerButton:hover {\n"
"				background-color: #38a169;\n"
"				}\n"
"				/* \347\272\242\350\211\262\346\214\211\351\222\256\357\274\232\351\200\200\345\207\272\345\212\237\350\203\275 - \350\241\245\345\205\205\345\212\237\350\203\275\350\257\264\346\230\216\346\226\207\345\255\227\346\240\267\345\274\217 */\n"
"				QPushButton#exitButton {\n"
"				background-color: #f56565;\n"
"				}\n"
"				QPushButton#exitButton:hover {\n"
"				background-color: #e53e3e;\n"
"				}\n"
"				QCheckBox {\n"
"				color: #4a5568;\n"
"				spacing: 8px;\n"
"				}\n"
"				QCheckBox::indicator {\n"
"				width: 16px;\n"
"				height: 16px;\n"
"				border: 2px solid #cbd5e0;\n"
"				border-radius: 3px;\n"
"				}\n"
"				QCheckBox::indicator:checked {\n"
"				background-color: #4299e1;\n"
"				border-color: #4299e1;\n"
"				}\n"
"				QCheckBox::indicator:checked:hover {\n"
"				background-color: #3182ce;\n"
"				border-color: #3182ce;\n"
"				}\n"
"			", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginDialog", "\360\237\232\204 \347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginDialog", "\360\237\221\244 \347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267ID", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginDialog", "\360\237\224\222 \345\257\206\347\240\201\357\274\232", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        rememberCheckBox->setText(QCoreApplication::translate("LoginDialog", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        colorHintLabel->setText(QCoreApplication::translate("LoginDialog", "\360\237\224\265 \350\223\235\350\211\262=\347\231\273\345\275\225\347\263\273\347\273\237 | \360\237\237\242 \347\273\277\350\211\262=\346\263\250\345\206\214\350\264\246\345\217\267 | \360\237\224\264 \347\272\242\350\211\262=\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginDialog", "\360\237\224\265 \347\231\273\345\275\225\347\263\273\347\273\237", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginDialog", "\360\237\237\242 \346\263\250\345\206\214\346\226\260\347\224\250\346\210\267", nullptr));
        exitButton->setText(QCoreApplication::translate("LoginDialog", "\360\237\224\264 \351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
