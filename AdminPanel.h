#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QTabWidget>
#include "TicketSystem.h" 
#include "ChangeOrderDialog.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QDebug>
#include <climits>
#include <string>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <QScreen>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMenu>
#include <QGroupBox>
#include <QStackedWidget>
#include <QListWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QTimer>
#include <QLabel>
#include <QCoreApplication>
#include <QGridLayout>
#include <QTimeEdit>
#include <QSpinBox>
#include <QGridLayout>

namespace Ui {
    class AdminPanel; 
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(TicketSystem& ticketSystem, QWidget* parent = nullptr);
    ~AdminPanel();

private slots:
    void onAddTrainClicked();
    void onEditTrainClicked();
    void onDeleteTrainClicked();
    void onAddUserClicked();
    void onEditUserClicked();
    void onDeleteUserClicked();
    void onRefreshCaptchaClicked();
    void onAdminLoginClicked(); 
    void onSearchUserClicked();
    void onClearSearchClicked();
    void onLockUserClicked();
    void onUnlockUserClicked();
    void refreshUserData();
    void refreshOrderData();
    void onAddStationClicked();
    void onDeleteStationClicked();
    void refreshStationData();
    QWidget* createStationManagementTab();
    void onCancelOrderClicked();
    void onChangeOrderClicked();

private:
    Ui::AdminPanel* ui; 
    TicketSystem& m_ticketSystem;
    QTabWidget* m_tabWidget;
    QTableWidget* m_trainTable; // 列车表格
    QTableWidget* m_userTable;  // 用户表格
    QTableWidget* m_orderTable;
    QPushButton* m_addTrainBtn;
    QPushButton* m_editTrainBtn;
    QPushButton* m_deleteTrainBtn;
    QPushButton* m_addUserBtn;
    QPushButton* m_editUserBtn;
    QPushButton* m_deleteUserBtn;
    QPushButton* m_lockUserBtn;
    QPushButton* m_unlockUserBtn;
    QLineEdit* m_usernameEdit;
    QLineEdit* m_passwordEdit;
    QLineEdit* m_captchaEdit;
    QLabel* m_captchaDisplay;
    QPushButton* m_refreshCaptchaButton;
    QPushButton* m_loginButton;
    QPushButton* m_registerButton;
    QPushButton* m_exitButton;
    QCheckBox* m_rememberPasswordCheckBox;

    QWidget* createTrainManagementTab(); // 创建列车管理标签页
    QWidget* createUserManagementTab();
    QWidget* createOrderManagementTab();
    QString generateCaptcha();           // 生成验证码
    QLineEdit* m_searchUserEdit;
    QTableWidget* m_stationTable;
    
    void refreshTrainData();
};

#endif // ADMINPANEL_H