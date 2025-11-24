#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class TicketSystem;
class User;

QT_BEGIN_NAMESPACE
namespace Ui {
    class LoginDialog;
}
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(TicketSystem& ticketSystem, QWidget* parent = nullptr);
    ~LoginDialog() override;

    // 获取登录成功的用户
    User* getLoggedInUser() const;

    void onExitClicked();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    Ui::LoginDialog* ui;
    TicketSystem& m_ticketSystem;
    User* m_loggedInUser;
};

#endif // LOGINDIALOG_H