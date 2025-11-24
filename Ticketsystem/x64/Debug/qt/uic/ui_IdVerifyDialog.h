/********************************************************************************
** Form generated from reading UI file 'IdVerifyDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDVERIFYDIALOG_H
#define UI_IDVERIFYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_IdVerifyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *idLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *verifyButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *IdVerifyDialog)
    {
        if (IdVerifyDialog->objectName().isEmpty())
            IdVerifyDialog->setObjectName("IdVerifyDialog");
        IdVerifyDialog->resize(400, 200);
        verticalLayout = new QVBoxLayout(IdVerifyDialog);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(IdVerifyDialog);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        idLineEdit = new QLineEdit(IdVerifyDialog);
        idLineEdit->setObjectName("idLineEdit");

        verticalLayout->addWidget(idLineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verifyButton = new QPushButton(IdVerifyDialog);
        verifyButton->setObjectName("verifyButton");

        horizontalLayout->addWidget(verifyButton);

        cancelButton = new QPushButton(IdVerifyDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(IdVerifyDialog);
        //QObject::connect(verifyButton, &QPushButton::clicked, IdVerifyDialog, qOverload<>(&QDialog::on_verifyButton_clicked));
        //QObject::connect(cancelButton, &QPushButton::clicked, IdVerifyDialog, qOverload<>(&QDialog::on_cancelButton_clicked));

        QMetaObject::connectSlotsByName(IdVerifyDialog);
    } // setupUi

    void retranslateUi(QDialog *IdVerifyDialog)
    {
        IdVerifyDialog->setWindowTitle(QCoreApplication::translate("IdVerifyDialog", "\350\272\253\344\273\275\351\252\214\350\257\201", nullptr));
        label->setText(QCoreApplication::translate("IdVerifyDialog", "\350\257\267\350\276\223\345\205\245\350\272\253\344\273\275\350\257\201\345\217\267\350\277\233\350\241\214\351\252\214\350\257\201\357\274\232", nullptr));
        verifyButton->setText(QCoreApplication::translate("IdVerifyDialog", "\351\252\214\350\257\201", nullptr));
        cancelButton->setText(QCoreApplication::translate("IdVerifyDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IdVerifyDialog: public Ui_IdVerifyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDVERIFYDIALOG_H
