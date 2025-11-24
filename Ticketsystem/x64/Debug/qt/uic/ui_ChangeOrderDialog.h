/********************************************************************************
** Form generated from reading UI file 'ChangeOrderDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEORDERDIALOG_H
#define UI_CHANGEORDERDIALOG_H

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

class Ui_ChangeOrderDialog
{
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *searchLayout;
    QLabel *startLabel;
    QComboBox *startStationCombo;
    QLabel *endLabel;
    QComboBox *endStationCombo;
    QLabel *dateLabel;
    QDateEdit *dateEdit;
    QPushButton *searchBtn;
    QTableWidget *trainTable;
    QPushButton *confirmBtn;

    void setupUi(QDialog *ChangeOrderDialog)
    {
        if (ChangeOrderDialog->objectName().isEmpty())
            ChangeOrderDialog->setObjectName("ChangeOrderDialog");
        ChangeOrderDialog->resize(800, 600);
        ChangeOrderDialog->setMinimumSize(QSize(800, 600));
        mainLayout = new QVBoxLayout(ChangeOrderDialog);
        mainLayout->setObjectName("mainLayout");
        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        startLabel = new QLabel(ChangeOrderDialog);
        startLabel->setObjectName("startLabel");
        startLabel->setMinimumSize(QSize(60, 0));

        searchLayout->addWidget(startLabel);

        startStationCombo = new QComboBox(ChangeOrderDialog);
        startStationCombo->setObjectName("startStationCombo");
        startStationCombo->setMinimumSize(QSize(120, 0));

        searchLayout->addWidget(startStationCombo);

        endLabel = new QLabel(ChangeOrderDialog);
        endLabel->setObjectName("endLabel");
        endLabel->setMinimumSize(QSize(60, 0));

        searchLayout->addWidget(endLabel);

        endStationCombo = new QComboBox(ChangeOrderDialog);
        endStationCombo->setObjectName("endStationCombo");
        endStationCombo->setMinimumSize(QSize(120, 0));

        searchLayout->addWidget(endStationCombo);

        dateLabel = new QLabel(ChangeOrderDialog);
        dateLabel->setObjectName("dateLabel");
        dateLabel->setMinimumSize(QSize(40, 0));

        searchLayout->addWidget(dateLabel);

        dateEdit = new QDateEdit(ChangeOrderDialog);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setCalendarPopup(true);
        dateEdit->setMinimumDate(QDate(2023, 1, 1));
        dateEdit->setMinimumSize(QSize(120, 0));

        searchLayout->addWidget(dateEdit);

        searchBtn = new QPushButton(ChangeOrderDialog);
        searchBtn->setObjectName("searchBtn");
        searchBtn->setMinimumSize(QSize(90, 0));

        searchLayout->addWidget(searchBtn);


        mainLayout->addLayout(searchLayout);

        trainTable = new QTableWidget(ChangeOrderDialog);
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
        trainTable->setColumnCount(6);
        trainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        trainTable->setSelectionMode(QAbstractItemView::SingleSelection);
        trainTable->setShowGrid(true);
        // 设置水平表头可见性
        trainTable->horizontalHeader()->setVisible(true);

        // 设置垂直表头可见性  
        trainTable->verticalHeader()->setVisible(false);

        mainLayout->addWidget(trainTable);

        confirmBtn = new QPushButton(ChangeOrderDialog);
        confirmBtn->setObjectName("confirmBtn");
        confirmBtn->setEnabled(false);
        confirmBtn->setMinimumSize(QSize(100, 35));

        mainLayout->addWidget(confirmBtn);


        retranslateUi(ChangeOrderDialog);

        QMetaObject::connectSlotsByName(ChangeOrderDialog);
    } // setupUi

    void retranslateUi(QDialog *ChangeOrderDialog)
    {
        ChangeOrderDialog->setWindowTitle(QCoreApplication::translate("ChangeOrderDialog", "\350\275\246\347\245\250\346\224\271\347\255\276", nullptr));
        ChangeOrderDialog->setStyleSheet(QCoreApplication::translate("ChangeOrderDialog", "\n"
"				QDialog {\n"
"				background-color: #f8f9fa;\n"
"				font-family: \"Microsoft YaHei\", \"Segoe UI\";\n"
"				}\n"
"				QLabel {\n"
"				color: #2d3748;\n"
"				font-weight: 500;\n"
"				}\n"
"				QComboBox, QDateEdit {\n"
"				padding: 6px;\n"
"				border: 1px solid #cbd5e0;\n"
"				border-radius: 4px;\n"
"				background-color: white;\n"
"				min-width: 100px;\n"
"				}\n"
"				QComboBox:focus, QDateEdit:focus {\n"
"				border-color: #4299e1;\n"
"				outline: none;\n"
"				}\n"
"				QPushButton {\n"
"				padding: 8px 16px;\n"
"				border: none;\n"
"				border-radius: 4px;\n"
"				font-weight: 500;\n"
"				}\n"
"				QPushButton#searchBtn {\n"
"				background-color: #4299e1;\n"
"				color: white;\n"
"				}\n"
"				QPushButton#searchBtn:hover {\n"
"				background-color: #3182ce;\n"
"				}\n"
"				QPushButton#confirmBtn {\n"
"				background-color: #38a169;\n"
"				color: white;\n"
"				}\n"
"				QPushButton#confirmBtn:hover {\n"
"				background-color: #2f855a;\n"
"				}\n"
"				QPushButton:disabled {\n"
""
                        "				background-color: #a0aec0;\n"
"				color: #e2e8f0;\n"
"				}\n"
"				QTableWidget {\n"
"				background-color: white;\n"
"				border: 1px solid #e2e8f0;\n"
"				border-radius: 6px;\n"
"				gridline-color: #e2e8f0;\n"
"				selection-background-color: #ebf8ff;\n"
"				selection-color: #2d3748;\n"
"				}\n"
"				QTableWidget::item:selected {\n"
"				background-color: #ebf8ff;\n"
"				}\n"
"				QHeaderView::section {\n"
"				background-color: #edf2f7;\n"
"				padding: 8px;\n"
"				border: none;\n"
"				font-weight: 600;\n"
"				color: #4a5568;\n"
"				}\n"
"			", nullptr));
        startLabel->setText(QCoreApplication::translate("ChangeOrderDialog", "\345\207\272\345\217\221\347\253\231:", nullptr));
        endLabel->setText(QCoreApplication::translate("ChangeOrderDialog", "\345\210\260\350\276\276\347\253\231:", nullptr));
        dateLabel->setText(QCoreApplication::translate("ChangeOrderDialog", "\346\227\245\346\234\237:", nullptr));
        searchBtn->setText(QCoreApplication::translate("ChangeOrderDialog", "\346\237\245\350\257\242\350\275\246\346\254\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem = trainTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChangeOrderDialog", "\350\275\246\346\254\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = trainTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChangeOrderDialog", "\345\207\272\345\217\221\347\253\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = trainTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ChangeOrderDialog", "\345\210\260\350\276\276\347\253\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = trainTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ChangeOrderDialog", "\345\207\272\345\217\221\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = trainTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ChangeOrderDialog", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = trainTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ChangeOrderDialog", "\344\275\231\347\245\250", nullptr));
        confirmBtn->setText(QCoreApplication::translate("ChangeOrderDialog", "\347\241\256\350\256\244\346\224\271\347\255\276", nullptr));
        confirmBtn->setStyleSheet(QCoreApplication::translate("ChangeOrderDialog", "font-weight: bold;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeOrderDialog: public Ui_ChangeOrderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEORDERDIALOG_H
