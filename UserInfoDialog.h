#pragma once

#include <QDialog>
#include "TicketSystem.h"

namespace Ui {
    class UserInfoDialog;
}

class UserInfoDialog : public QDialog
{
    Q_OBJECT

public:
    UserInfoDialog(TicketSystem& ticketSystem, QWidget* parent = nullptr);
    ~UserInfoDialog();

private slots:
    void onSaveButtonClicked();
    void onCancelButtonClicked();

private:
    void loadUserInfo();

    Ui::UserInfoDialog* ui;
    TicketSystem& m_ticketSystem;
    std::string m_originalPassword; // 保存原始密码用于验证
    std::string m_originalUsername; // 保存原始用户名
    std::string m_originalPhone;    // 保存原始手机号
};