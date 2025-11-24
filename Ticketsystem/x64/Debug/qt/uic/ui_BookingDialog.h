/********************************************************************************
** Form generated from reading UI file 'BookingDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKINGDIALOG_H
#define UI_BOOKINGDIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BookingDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *searchLayout;
    QLabel *startLabel;
    QComboBox *startStationCombo;
    QLabel *endLabel;
    QComboBox *endStationCombo;
    QLabel *dateLabel;
    QDateEdit *dateEdit;
    QPushButton *searchBtn;
    QTableWidget *trainTable;
    QPushButton *bookBtn;

    void setupUi(QDialog *BookingDialog)
    {
        if (BookingDialog->objectName().isEmpty())
            BookingDialog->setObjectName("BookingDialog");
        BookingDialog->resize(600, 400);
        BookingDialog->setMinimumSize(QSize(600, 400));
        verticalLayout = new QVBoxLayout(BookingDialog);
        verticalLayout->setObjectName("verticalLayout");
        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        startLabel = new QLabel(BookingDialog);
        startLabel->setObjectName("startLabel");

        searchLayout->addWidget(startLabel);

        startStationCombo = new QComboBox(BookingDialog);
        startStationCombo->setObjectName("startStationCombo");

        searchLayout->addWidget(startStationCombo);

        endLabel = new QLabel(BookingDialog);
        endLabel->setObjectName("endLabel");

        searchLayout->addWidget(endLabel);

        endStationCombo = new QComboBox(BookingDialog);
        endStationCombo->setObjectName("endStationCombo");

        searchLayout->addWidget(endStationCombo);

        dateLabel = new QLabel(BookingDialog);
        dateLabel->setObjectName("dateLabel");

        searchLayout->addWidget(dateLabel);

        dateEdit = new QDateEdit(BookingDialog);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setCalendarPopup(true);
        dateEdit->setDate(QDate(2023, 1, 1));

        searchLayout->addWidget(dateEdit);

        searchBtn = new QPushButton(BookingDialog);
        searchBtn->setObjectName("searchBtn");

        searchLayout->addWidget(searchBtn);


        verticalLayout->addLayout(searchLayout);

        trainTable = new QTableWidget(BookingDialog);
        if (trainTable->columnCount() < 6)
            trainTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        trainTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        trainTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        trainTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        trainTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        trainTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        trainTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        trainTable->setObjectName("trainTable");
        trainTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        trainTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        trainTable->setShowGrid(true);
        trainTable->setColumnCount(6);
        trainTable->horizontalHeader()->setVisible(true);
        trainTable->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(trainTable);

        bookBtn = new QPushButton(BookingDialog);
        bookBtn->setObjectName("bookBtn");
        bookBtn->setEnabled(false);

        verticalLayout->addWidget(bookBtn);


        retranslateUi(BookingDialog);

        QMetaObject::connectSlotsByName(BookingDialog);
    } // setupUi

    void retranslateUi(QDialog *BookingDialog)
    {
        BookingDialog->setWindowTitle(QCoreApplication::translate("BookingDialog", "\350\275\246\347\245\250\351\242\204\350\256\242", nullptr));
        startLabel->setText(QCoreApplication::translate("BookingDialog", "\345\207\272\345\217\221\347\253\231:", nullptr));
        endLabel->setText(QCoreApplication::translate("BookingDialog", "\345\210\260\350\276\276\347\253\231:", nullptr));
        dateLabel->setText(QCoreApplication::translate("BookingDialog", "\346\227\245\346\234\237:", nullptr));
        searchBtn->setText(QCoreApplication::translate("BookingDialog", "\346\237\245\350\257\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem = trainTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("BookingDialog", "\345\210\227\350\275\246\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = trainTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("BookingDialog", "\345\207\272\345\217\221\347\253\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = trainTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("BookingDialog", "\345\210\260\350\276\276\347\253\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = trainTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("BookingDialog", "\345\207\272\345\217\221\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = trainTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("BookingDialog", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = trainTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("BookingDialog", "\344\275\231\347\245\250", nullptr));
        bookBtn->setText(QCoreApplication::translate("BookingDialog", "\351\242\204\350\256\242\351\200\211\344\270\255\350\275\246\347\245\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookingDialog: public Ui_BookingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKINGDIALOG_H
