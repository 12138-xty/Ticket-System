/********************************************************************************
** Form generated from reading UI file 'SeatTemplate.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEATTEMPLATE_H
#define UI_SEATTEMPLATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_SeatTemplateClass
{
public:

    void setupUi(QDialog *SeatTemplateClass)
    {
        if (SeatTemplateClass->objectName().isEmpty())
            SeatTemplateClass->setObjectName("SeatTemplateClass");
        SeatTemplateClass->resize(600, 400);

        retranslateUi(SeatTemplateClass);

        QMetaObject::connectSlotsByName(SeatTemplateClass);
    } // setupUi

    void retranslateUi(QDialog *SeatTemplateClass)
    {
        SeatTemplateClass->setWindowTitle(QCoreApplication::translate("SeatTemplateClass", "SeatTemplate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SeatTemplateClass: public Ui_SeatTemplateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEATTEMPLATE_H
