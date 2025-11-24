#include "LoginDialog.h"
#include "ui_LoginDialog.h"  
#include "RegisterDialog.h"
#include "TicketSystem.h"
#include "User.h"
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <stdlib.h> 
#include <QApplication>

using namespace std;

LoginDialog::LoginDialog(TicketSystem& ticketSystem, QWidget* parent)
    : QDialog(parent), ui(new Ui::LoginDialog), m_ticketSystem(ticketSystem), m_loggedInUser(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("铁路票务系统 - 用户登录");
    

    // 连接信号槽
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &LoginDialog::onExitClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginDialog::onRegisterClicked);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

User* LoginDialog::getLoggedInUser() const
{
    return m_loggedInUser;
}

void LoginDialog::onLoginClicked() {
    QString username = ui->usernameEdit->text().replace("\"", "").trimmed();
    QString password = ui->passwordEdit->text().replace("\"", "").trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名和密码不能为空");
        return;
    }

    if (m_ticketSystem.validateLogin(username, password)) {
        m_loggedInUser = m_ticketSystem.getCurrentUser();

        // 登录成功，根据用户角色决定是否显示管理员欢迎信息
        if (m_loggedInUser && m_ticketSystem.isAdminUser(m_loggedInUser->getUserId())) {
            QMessageBox::information(this, "登录成功", "管理员登录成功！");
        }
        else {
            QMessageBox::information(this, "登录成功", "用户登录成功！");
        }

        accept();  // 登录成功，关闭对话框
    }
    else {
        m_loggedInUser = nullptr;
        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
    }
}

void LoginDialog::onExitClicked()
{
    qDebug() << "退出按钮被点击，正在退出程序...";
    exit(0); // 强制退
}

void LoginDialog::onRegisterClicked()
{
    RegisterDialog registerDialog(m_ticketSystem, this);
    if (registerDialog.exec() == QDialog::Accepted) {
        // 注册成功后自动填充用户名
        QString username = registerDialog.getUsername();
        if (!username.isEmpty()) {
            ui->usernameEdit->setText(username);
            ui->passwordEdit->setFocus(); // 将焦点设置到密码框
        }
        QMessageBox::information(this, "注册成功", "用户注册成功，请登录");
    }
}