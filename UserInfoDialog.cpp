#include "UserInfoDialog.h"
#include "ui_UserInfoDialog.h"
#include <QMessageBox>
#include "User.h"
#include <QDebug>

UserInfoDialog::UserInfoDialog(TicketSystem& ticketSystem, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::UserInfoDialog),
    m_ticketSystem(ticketSystem)
{
    ui->setupUi(this);
    setWindowTitle("修改用户信息");

    connect(ui->saveButton, &QPushButton::clicked, this, &UserInfoDialog::onSaveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &UserInfoDialog::onCancelButtonClicked);

    // 加载用户信息
    loadUserInfo();
}

UserInfoDialog::~UserInfoDialog()
{
    delete ui;
}

void UserInfoDialog::onSaveButtonClicked()
{
    // 获取用户输入
    std::string username = ui->usernameLineEdit->text().toStdString();
    std::string phone = ui->phoneLineEdit->text().toStdString();
    std::string newPassword = ui->newPasswordLineEdit->text().toStdString();
    std::string confirmPassword = ui->confirmPasswordLineEdit->text().toStdString();

    // 验证必填字段
    if (username.empty()) {
        QMessageBox::warning(this, "输入错误", "用户名不能为空");
        return;
    }

    // 验证手机号格式（简单验证）
    if (phone.empty()) {
        QMessageBox::warning(this, "输入错误", "手机号不能为空");
        return;
    }

    // 如果用户输入了新密码，验证新密码
    if (!newPassword.empty()) {
        if (newPassword == m_originalPassword) {
            QMessageBox::warning(this, "密码错误", "新密码不能与当前密码相同");
            return;
        }

        if (newPassword != confirmPassword) {
            QMessageBox::warning(this, "密码不匹配", "新密码和确认密码不一致");
            return;
        }
    }

    qDebug() << "保存用户信息 - 用户名:" << username.c_str()
        << "手机号:" << phone.c_str();

    // 决定使用哪个密码：如果用户输入了新密码就用新密码，否则保持原密码
    std::string passwordToUse = newPassword.empty() ? m_originalPassword : newPassword;

    // 调用TicketSystem保存用户信息
    if (m_ticketSystem.updateUserInfo(username, phone, passwordToUse)) {
        QMessageBox::information(this, "成功", "用户信息更新成功");
        accept();
    }
    else {
        QMessageBox::warning(this, "错误", "用户信息更新失败");
    }
}

void UserInfoDialog::onCancelButtonClicked()
{
    reject();
}

void UserInfoDialog::loadUserInfo()
{
    // 从TicketSystem获取当前用户信息
    User* currentUser = m_ticketSystem.getCurrentUser();
    if (!currentUser) {
        QMessageBox::warning(this, "错误", "无法获取当前用户信息");
        return;
    }

    qDebug() << "加载用户信息 - 用户ID:" << QString::fromStdString(currentUser->getUserId());

    // 保存原始信息
    m_originalPassword = currentUser->getPassword();
    m_originalUsername = currentUser->getUsername();
    m_originalPhone = currentUser->getPhone();

    // 设置界面显示
    ui->usernameLineEdit->setText(QString::fromStdString(m_originalUsername));
    ui->phoneLineEdit->setText(QString::fromStdString(m_originalPhone));

    // 清空密码字段
    ui->newPasswordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();
}