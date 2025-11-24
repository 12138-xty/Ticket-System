/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSearch;
    QAction *actionBook;
    QAction *actionMyOrders;
    QAction *actionCancelOrder;
    QAction *actionAdmin;
    QAction *actionLogout;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *navLayout;
    QGroupBox *userInfoCard;
    QVBoxLayout *userLayout;
    QLabel *userNameLabel;
    QLabel *userTypeLabel;
    QPushButton *searchButton;
    QPushButton *bookingButton;
    QPushButton *adminButton;
    QSpacerItem *navSpacer;
    QPushButton *userInfoButton;
    QPushButton *deleteAccountButton;
    QPushButton *logoutButton;
    QStackedWidget *contentStack;
    QWidget *welcomePage;
    QVBoxLayout *welcomeLayout;
    QSpacerItem *welcomeTopSpacer;
    QLabel *welcomeTitleLabel;
    QLabel *welcomeMessageLabel;
    QLabel *featureLabel;
    QSpacerItem *welcomeBottomSpacer;
    QWidget *searchPage;
    QWidget *bookingPage;
    QWidget *adminPage;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTicket;
    QMenu *menuOrder;
    QMenu *menuSystem;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        MainWindow->setMinimumSize(QSize(1000, 700));
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName("actionSearch");
        actionBook = new QAction(MainWindow);
        actionBook->setObjectName("actionBook");
        actionMyOrders = new QAction(MainWindow);
        actionMyOrders->setObjectName("actionMyOrders");
        actionCancelOrder = new QAction(MainWindow);
        actionCancelOrder->setObjectName("actionCancelOrder");
        actionAdmin = new QAction(MainWindow);
        actionAdmin->setObjectName("actionAdmin");
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName("actionLogout");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        navLayout = new QVBoxLayout();
        navLayout->setObjectName("navLayout");
        userInfoCard = new QGroupBox(centralWidget);
        userInfoCard->setObjectName("userInfoCard");
        userLayout = new QVBoxLayout(userInfoCard);
        userLayout->setObjectName("userLayout");
        userNameLabel = new QLabel(userInfoCard);
        userNameLabel->setObjectName("userNameLabel");

        userLayout->addWidget(userNameLabel);

        userTypeLabel = new QLabel(userInfoCard);
        userTypeLabel->setObjectName("userTypeLabel");

        userLayout->addWidget(userTypeLabel);


        navLayout->addWidget(userInfoCard);

        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName("searchButton");

        navLayout->addWidget(searchButton);

        bookingButton = new QPushButton(centralWidget);
        bookingButton->setObjectName("bookingButton");

        navLayout->addWidget(bookingButton);

        adminButton = new QPushButton(centralWidget);
        adminButton->setObjectName("adminButton");
        adminButton->setVisible(false);

        navLayout->addWidget(adminButton);

        navSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        navLayout->addItem(navSpacer);

        userInfoButton = new QPushButton(centralWidget);
        userInfoButton->setObjectName("userInfoButton");

        navLayout->addWidget(userInfoButton);

        deleteAccountButton = new QPushButton(centralWidget);
        deleteAccountButton->setObjectName("deleteAccountButton");

        navLayout->addWidget(deleteAccountButton);

        logoutButton = new QPushButton(centralWidget);
        logoutButton->setObjectName("logoutButton");

        navLayout->addWidget(logoutButton);


        horizontalLayout->addLayout(navLayout);

        contentStack = new QStackedWidget(centralWidget);
        contentStack->setObjectName("contentStack");
        welcomePage = new QWidget();
        welcomePage->setObjectName("welcomePage");
        welcomeLayout = new QVBoxLayout(welcomePage);
        welcomeLayout->setObjectName("welcomeLayout");
        welcomeTopSpacer = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        welcomeLayout->addItem(welcomeTopSpacer);

        welcomeTitleLabel = new QLabel(welcomePage);
        welcomeTitleLabel->setObjectName("welcomeTitleLabel");
        welcomeTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        welcomeLayout->addWidget(welcomeTitleLabel);

        welcomeMessageLabel = new QLabel(welcomePage);
        welcomeMessageLabel->setObjectName("welcomeMessageLabel");
        welcomeMessageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        welcomeLayout->addWidget(welcomeMessageLabel);

        featureLabel = new QLabel(welcomePage);
        featureLabel->setObjectName("featureLabel");
        featureLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        welcomeLayout->addWidget(featureLabel);

        welcomeBottomSpacer = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        welcomeLayout->addItem(welcomeBottomSpacer);

        contentStack->addWidget(welcomePage);
        searchPage = new QWidget();
        searchPage->setObjectName("searchPage");
        contentStack->addWidget(searchPage);
        bookingPage = new QWidget();
        bookingPage->setObjectName("bookingPage");
        contentStack->addWidget(bookingPage);
        adminPage = new QWidget();
        adminPage->setObjectName("adminPage");
        contentStack->addWidget(adminPage);

        horizontalLayout->addWidget(contentStack);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1200, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuTicket = new QMenu(menuBar);
        menuTicket->setObjectName("menuTicket");
        menuOrder = new QMenu(menuBar);
        menuOrder->setObjectName("menuOrder");
        menuSystem = new QMenu(menuBar);
        menuSystem->setObjectName("menuSystem");
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTicket->menuAction());
        menuBar->addAction(menuOrder->menuAction());
        menuBar->addAction(menuSystem->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionLogout);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTicket->addAction(actionSearch);
        menuTicket->addAction(actionBook);
        menuOrder->addAction(actionMyOrders);
        menuOrder->addAction(actionCancelOrder);
        menuSystem->addAction(actionAdmin);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        contentStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\351\223\201\350\267\257\347\245\250\345\212\241\347\263\273\347\273\237", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"				 {\n"
"				background-color: #f8f9fa;\n"
"				font-family: \"Segoe UI\", \"Microsoft YaHei\";\n"
"				color: #212529; /* \346\267\273\345\212\240\351\273\230\350\256\244\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QWidget {\n"
"				background-color: #ffffff;\n"
"				color: #212529; /* \346\267\273\345\212\240\351\273\230\350\256\244\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QGroupBox {\n"
"				font-weight: bold;\n"
"				border: 1px solid #dee2e6;\n"
"				border-radius: 6px;\n"
"				margin-top: 10px;\n"
"				padding-top: 15px;\n"
"				background-color: white;\n"
"				color: #212529; /* \346\267\273\345\212\240\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QGroupBox::title {\n"
"				subcontrol-origin: margin;\n"
"				left: 10px;\n"
"				padding: 0 5px 0 5px;\n"
"				color: #495057;\n"
"				}\n"
"				QPushButton {\n"
"				background-color: #007bff;\n"
"				color: white;\n"
"				border: none;\n"
"				border-radius: 6px;\n"
"				pad"
                        "ding: 10px 16px;\n"
"				font-size: 14px;\n"
"				font-weight: 500;\n"
"				}\n"
"				QPushButton:hover {\n"
"				background-color: #0056b3;\n"
"				}\n"
"				QPushButton:pressed {\n"
"				background-color: #004085;\n"
"				}\n"
"				QPushButton:disabled {\n"
"				background-color: #6c757d;\n"
"				color: #ced4da;\n"
"				}\n"
"				QListWidget {\n"
"				background-color: white;\n"
"				border: 1px solid #dee2e6;\n"
"				border-radius: 6px;\n"
"				padding: 4px;\n"
"				color: #212529; /* \346\267\273\345\212\240\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QListWidget::item {\n"
"				padding: 8px;\n"
"				border-bottom: 1px solid #e9ecef;\n"
"				color: #212529; /* \346\267\273\345\212\240\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QListWidget::item:selected {\n"
"				background-color: #cce5ff;\n"
"				color: #004085;\n"
"				}\n"
"				QListWidget::item:hover {\n"
"				background-color: #e9ecef;\n"
"				}\n"
"				QTableWidget {\n"
"				background-color: white;\n"
""
                        "				border: 1px solid #dee2e6;\n"
"				border-radius: 6px;\n"
"				gridline-color: #dee2e6;\n"
"				selection-background-color: #cce5ff;\n"
"				color: #212529; /* \346\267\273\345\212\240\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QTableWidget::item:selected {\n"
"				background-color: #cce5ff;\n"
"				color: #212529; /* \346\267\273\345\212\240\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QHeaderView::section {\n"
"				background-color: #e9ecef;\n"
"				padding: 8px;\n"
"				border: none;\n"
"				font-weight: 600;\n"
"				color: #495057;\n"
"				}\n"
"				QLineEdit, QComboBox, QDateEdit {\n"
"				border: 1px solid #ced4da;\n"
"				border-radius: 4px;\n"
"				padding: 6px;\n"
"				background-color: white;\n"
"				min-height: 25px;\n"
"				color: #212529; /* \346\267\273\345\212\240\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QLineEdit:focus, QComboBox:focus, QDateEdit:focus {\n"
"				border-color: #80bdff;\n"
"				outline: none;\n"
"		"
                        "		}\n"
"				QTabWidget::pane {\n"
"				border: 1px solid #dee2e6;\n"
"				border-radius: 6px;\n"
"				background: white;\n"
"				margin-top: 10px;\n"
"				}\n"
"				QTabBar::tab {\n"
"				background: #e9ecef;\n"
"				border: 1px solid #dee2e6;\n"
"				padding: 8px 16px;\n"
"				margin-right: 2px;\n"
"				border-top-left-radius: 4px;\n"
"				border-top-right-radius: 4px;\n"
"				color: #495057;\n"
"				}\n"
"				QTabBar::tab:selected {\n"
"				background: white;\n"
"				border-bottom-color: white;\n"
"				color: #007bff;\n"
"				}\n"
"				QTabBar::tab:hover {\n"
"				background: #dee2e6;\n"
"				}\n"
"				QLabel {\n"
"				color: #212529; /* \347\241\256\344\277\235\346\211\200\346\234\211\346\240\207\347\255\276\351\203\275\346\234\211\346\255\243\347\241\256\347\232\204\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"				}\n"
"				QLabel#titleLabel {\n"
"				font-size: 18px;\n"
"				font-weight: bold;\n"
"				color: #212529;\n"
"				padding: 10px 0;\n"
"				}\n"
"				QLabel#userNameLabel {\n"
"				font-"
                        "size: 16px;\n"
"				font-weight: bold;\n"
"				color: #212529;\n"
"				}\n"
"				QLabel#userTypeLabel {\n"
"				font-size: 14px;\n"
"				color: #6c757d;\n"
"				}\n"
"				QStatusBar {\n"
"				background-color: #e9ecef;\n"
"				color: #495057;\n"
"				border-top: 1px solid #dee2e6;\n"
"				}\n"
"			", nullptr));
        actionSearch->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\350\275\246\347\245\250", nullptr));
        actionBook->setText(QCoreApplication::translate("MainWindow", "\351\242\204\350\256\242\350\275\246\347\245\250", nullptr));
        actionMyOrders->setText(QCoreApplication::translate("MainWindow", "\350\256\242\345\215\225", nullptr));
        actionCancelOrder->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210\350\256\242\345\215\225", nullptr));
        actionAdmin->setText(QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\351\235\242\346\235\277", nullptr));
        actionLogout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        userInfoCard->setTitle(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        userNameLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\252\347\231\273\345\275\225", nullptr));
        userTypeLabel->setText(QString());
        searchButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 \350\275\246\347\245\250\346\237\245\350\257\242", nullptr));
        bookingButton->setText(QCoreApplication::translate("MainWindow", "\360\237\216\253 \350\256\242\345\215\225", nullptr));
        adminButton->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 \347\263\273\347\273\237\347\256\241\347\220\206", nullptr));
        userInfoButton->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 \344\277\256\346\224\271\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        deleteAccountButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\264\346\263\250\351\224\200\350\264\246\346\210\267", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\360\237\232\252 \351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        welcomeTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 28px; font-weight: bold; color: #212529; margin: 20px;", nullptr));
        welcomeTitleLabel->setText(QCoreApplication::translate("MainWindow", "\351\223\201\350\267\257\347\245\250\345\212\241\347\263\273\347\273\237", nullptr));
        welcomeMessageLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 16px; color: #6c757d; margin: 10px;", nullptr));
        welcomeMessageLabel->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\344\275\277\347\224\250\351\223\201\350\267\257\347\245\250\345\212\241\347\263\273\347\273\237\\n\350\257\267\347\231\273\345\275\225\344\273\245\345\274\200\345\247\213\344\275\277\347\224\250", nullptr));
        featureLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #495057; margin: 20px; background-color: white; padding: 15px; border-radius: 8px; border: 1px solid #dee2e6;", nullptr));
        featureLabel->setText(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\345\212\237\350\203\275\357\274\232\\n\342\200\242 \350\275\246\347\245\250\346\237\245\350\257\242\344\270\216\351\242\204\350\256\242\\n\342\200\242 \350\256\242\345\215\225\347\256\241\347\220\206\\n\342\200\242 \350\275\246\346\254\241\344\277\241\346\201\257\346\237\245\347\234\213\\n\342\200\242 \347\263\273\347\273\237\347\256\241\347\220\206\357\274\210\347\256\241\347\220\206\345\221\230\357\274\211", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menuTicket->setTitle(QCoreApplication::translate("MainWindow", "\350\275\246\347\245\250(&T)", nullptr));
        menuOrder->setTitle(QCoreApplication::translate("MainWindow", "\350\256\242\345\215\225(&O)", nullptr));
        menuSystem->setTitle(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237(&S)", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
