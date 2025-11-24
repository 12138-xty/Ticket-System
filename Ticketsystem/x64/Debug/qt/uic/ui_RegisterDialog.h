/********************************************************************************
** Form generated from reading UI file 'RegisterDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *scrollLayout;
    QFrame *registerFrame;
    QVBoxLayout *formContainerLayout;
    QLabel *titleLabel;
    QSpacerItem *titleSpacer;
    QGridLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordEdit;
    QLabel *displayNameLabel;
    QLineEdit *displayNameEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneEdit;
    QLabel *idCardLabel;
    QLineEdit *idCardEdit;
    QCheckBox *termsCheckBox;
    QSpacerItem *formSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *leftButtonSpacer;
    QPushButton *registerBtn;
    QPushButton *cancelBtn;
    QSpacerItem *rightButtonSpacer;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(500, 600);
        RegisterDialog->setMinimumSize(QSize(500, 600));
        RegisterDialog->setMaximumSize(QSize(600, 600));
        mainLayout = new QVBoxLayout(RegisterDialog);
        mainLayout->setObjectName("mainLayout");
        scrollArea = new QScrollArea(RegisterDialog);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignHCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 480, 500));
        scrollLayout = new QVBoxLayout(scrollAreaWidgetContents);
        scrollLayout->setObjectName("scrollLayout");
        registerFrame = new QFrame(scrollAreaWidgetContents);
        registerFrame->setObjectName("registerFrame");
        registerFrame->setFrameShape(QFrame::StyledPanel);
        registerFrame->setFrameShadow(QFrame::Raised);
        formContainerLayout = new QVBoxLayout(registerFrame);
        formContainerLayout->setObjectName("formContainerLayout");
        titleLabel = new QLabel(registerFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        formContainerLayout->addWidget(titleLabel);

        titleSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formContainerLayout->addItem(titleSpacer);

        formLayout = new QGridLayout();
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(registerFrame);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->addWidget(usernameLabel, 0, 0, 1, 1);

        usernameEdit = new QLineEdit(registerFrame);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setClearButtonEnabled(true);
        usernameEdit->setMaxLength(20);

        formLayout->addWidget(usernameEdit, 0, 1, 1, 1);

        passwordLabel = new QLabel(registerFrame);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->addWidget(passwordLabel, 1, 0, 1, 1);

        passwordEdit = new QLineEdit(registerFrame);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setMaxLength(20);

        formLayout->addWidget(passwordEdit, 1, 1, 1, 1);

        confirmPasswordLabel = new QLabel(registerFrame);
        confirmPasswordLabel->setObjectName("confirmPasswordLabel");

        formLayout->addWidget(confirmPasswordLabel, 2, 0, 1, 1);

        confirmPasswordEdit = new QLineEdit(registerFrame);
        confirmPasswordEdit->setObjectName("confirmPasswordEdit");
        confirmPasswordEdit->setEchoMode(QLineEdit::Password);

        formLayout->addWidget(confirmPasswordEdit, 2, 1, 1, 1);

        displayNameLabel = new QLabel(registerFrame);
        displayNameLabel->setObjectName("displayNameLabel");

        formLayout->addWidget(displayNameLabel, 3, 0, 1, 1);

        displayNameEdit = new QLineEdit(registerFrame);
        displayNameEdit->setObjectName("displayNameEdit");

        formLayout->addWidget(displayNameEdit, 3, 1, 1, 1);

        phoneLabel = new QLabel(registerFrame);
        phoneLabel->setObjectName("phoneLabel");

        formLayout->addWidget(phoneLabel, 4, 0, 1, 1);

        phoneEdit = new QLineEdit(registerFrame);
        phoneEdit->setObjectName("phoneEdit");
        phoneEdit->setMaxLength(11);

        formLayout->addWidget(phoneEdit, 4, 1, 1, 1);

        idCardLabel = new QLabel(registerFrame);
        idCardLabel->setObjectName("idCardLabel");

        formLayout->addWidget(idCardLabel, 5, 0, 1, 1);

        idCardEdit = new QLineEdit(registerFrame);
        idCardEdit->setObjectName("idCardEdit");
        idCardEdit->setMaxLength(18);

        formLayout->addWidget(idCardEdit, 5, 1, 1, 1);


        formContainerLayout->addLayout(formLayout);

        termsCheckBox = new QCheckBox(registerFrame);
        termsCheckBox->setObjectName("termsCheckBox");

        formContainerLayout->addWidget(termsCheckBox);

        formSpacer = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formContainerLayout->addItem(formSpacer);


        scrollLayout->addWidget(registerFrame);

        scrollArea->setWidget(scrollAreaWidgetContents);

        mainLayout->addWidget(scrollArea);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        leftButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(leftButtonSpacer);

        registerBtn = new QPushButton(RegisterDialog);
        registerBtn->setObjectName("registerBtn");
        registerBtn->setEnabled(false);

        buttonLayout->addWidget(registerBtn);

        cancelBtn = new QPushButton(RegisterDialog);
        cancelBtn->setObjectName("cancelBtn");

        buttonLayout->addWidget(cancelBtn);

        rightButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(rightButtonSpacer);


        mainLayout->addLayout(buttonLayout);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267\346\263\250\345\206\214 - \351\223\201\350\267\257\347\245\250\345\212\241\347\263\273\347\273\237", nullptr));
        RegisterDialog->setStyleSheet(QCoreApplication::translate("RegisterDialog", "\n"
"				QDialog {\n"
"				background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"				stop: 0 #4facfe, stop: 1 #00f2fe);\n"
"				font-family: \"Microsoft YaHei\", \"Segoe UI\";\n"
"				}\n"
"				QScrollArea {\n"
"				border: none;\n"
"				background: transparent;\n"
"				}\n"
"				QScrollArea > QWidget > QWidget {\n"
"				background: transparent;\n"
"				}\n"
"				QFrame#registerFrame {\n"
"				background-color: white;\n"
"				border-radius: 12px;\n"
"				padding: 25px;\n"
"				margin: 20px;\n"
"				}\n"
"				QLabel {\n"
"				color: #2d3748;\n"
"				font-weight: 500;\n"
"				font-size: 14px;\n"
"				}\n"
"				QLabel#titleLabel {\n"
"				font-size: 22px;\n"
"				font-weight: bold;\n"
"				color: #2d3748;\n"
"				padding: 10px;\n"
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
"				border-color: #4299"
                        "e1;\n"
"				background-color: white;\n"
"				}\n"
"				QLineEdit:placeholder {\n"
"				color: #a0aec0;\n"
"				}\n"
"				QLineEdit[isValid=\"false\"] {\n"
"				border-color: #f56565;\n"
"				background-color: #fed7d7;\n"
"				}\n"
"				QLineEdit[isValid=\"true\"] {\n"
"				border-color: #48bb78;\n"
"				}\n"
"				QPushButton {\n"
"				padding: 12px 20px;\n"
"				border: none;\n"
"				border-radius: 6px;\n"
"				font-weight: 600;\n"
"				font-size: 14px;\n"
"				margin: 5px;\n"
"				}\n"
"				QPushButton#registerBtn {\n"
"				background-color: #48bb78;\n"
"				color: white;\n"
"				}\n"
"				QPushButton#registerBtn:hover {\n"
"				background-color: #38a169;\n"
"				}\n"
"				QPushButton#registerBtn:pressed {\n"
"				background-color: #2f855a;\n"
"				}\n"
"				QPushButton#registerBtn:disabled {\n"
"				background-color: #a0aec0;\n"
"				color: #e2e8f0;\n"
"				}\n"
"				QPushButton#cancelBtn {\n"
"				background-color: #718096;\n"
"				color: white;\n"
"				}\n"
"				QPushButton#cancelBtn:hover {\n"
"				backgr"
                        "ound-color: #4a5568;\n"
"				}\n"
"				QCheckBox {\n"
"				color: #4a5568;\n"
"				spacing: 8px;\n"
"				font-size: 13px;\n"
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
"				.validationIcon {\n"
"				color: #e53e3e;\n"
"				font-weight: bold;\n"
"				}\n"
"				.validationIcon.valid {\n"
"				color: #38a169;\n"
"				}\n"
"			", nullptr));
        titleLabel->setText(QCoreApplication::translate("RegisterDialog", "\360\237\223\235 \347\224\250\346\210\267\346\263\250\345\206\214", nullptr));
        usernameLabel->setText(QCoreApplication::translate("RegisterDialog", "\360\237\221\244 \347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
#if QT_CONFIG(tooltip)
        usernameLabel->setToolTip(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\2453-20\344\270\252\345\255\227\347\254\246\347\232\204\347\224\250\346\210\267\345\220\215", nullptr));
#endif // QT_CONFIG(tooltip)
        usernameEdit->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215\357\274\2103-20\344\270\252\345\255\227\347\254\246\357\274\211", nullptr));
        passwordLabel->setText(QCoreApplication::translate("RegisterDialog", "\360\237\224\222 \345\257\206\347\240\201\357\274\232", nullptr));
#if QT_CONFIG(tooltip)
        passwordLabel->setToolTip(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\2456-20\344\270\252\345\255\227\347\254\246\347\232\204\345\257\206\347\240\201", nullptr));
#endif // QT_CONFIG(tooltip)
        passwordEdit->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201\357\274\2106-20\344\270\252\345\255\227\347\254\246\357\274\211", nullptr));
        confirmPasswordLabel->setText(QCoreApplication::translate("RegisterDialog", "\342\234\205 \347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        confirmPasswordEdit->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\350\257\267\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        displayNameLabel->setText(QCoreApplication::translate("RegisterDialog", "\360\237\221\224 \345\247\223\345\220\215\357\274\232", nullptr));
#if QT_CONFIG(tooltip)
        displayNameLabel->setToolTip(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\245\347\234\237\345\256\236\345\247\223\345\220\215", nullptr));
#endif // QT_CONFIG(tooltip)
        displayNameEdit->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\245\347\234\237\345\256\236\345\247\223\345\220\215", nullptr));
        phoneLabel->setText(QCoreApplication::translate("RegisterDialog", "\360\237\223\261 \346\211\213\346\234\272\345\217\267\357\274\232", nullptr));
#if QT_CONFIG(tooltip)
        phoneLabel->setToolTip(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\24511\344\275\215\346\211\213\346\234\272\345\217\267\347\240\201", nullptr));
#endif // QT_CONFIG(tooltip)
        phoneEdit->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\245\346\211\213\346\234\272\345\217\267\347\240\201", nullptr));
        phoneEdit->setInputMask(QCoreApplication::translate("RegisterDialog", "99999999999", nullptr));
        idCardLabel->setText(QCoreApplication::translate("RegisterDialog", "\360\237\206\224 \350\272\253\344\273\275\350\257\201\345\217\267\357\274\232", nullptr));
#if QT_CONFIG(tooltip)
        idCardLabel->setToolTip(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\24518\344\275\215\350\272\253\344\273\275\350\257\201\345\217\267\347\240\201", nullptr));
#endif // QT_CONFIG(tooltip)
        idCardEdit->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\350\257\267\350\276\223\345\205\245\350\272\253\344\273\275\350\257\201\345\217\267\347\240\201", nullptr));
        termsCheckBox->setText(QCoreApplication::translate("RegisterDialog", "\346\210\221\345\267\262\351\230\205\350\257\273\345\271\266\345\220\214\346\204\217\343\200\212\347\224\250\346\210\267\345\215\217\350\256\256\343\200\213\345\222\214\343\200\212\351\232\220\347\247\201\346\224\277\347\255\226\343\200\213", nullptr));
        registerBtn->setText(QCoreApplication::translate("RegisterDialog", "\360\237\232\200 \347\253\213\345\215\263\346\263\250\345\206\214", nullptr));
        cancelBtn->setText(QCoreApplication::translate("RegisterDialog", "\342\235\214 \345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
