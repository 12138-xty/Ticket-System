#pragma once
#include "TicketSystem.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "StringHelper.h"
#include <String>

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(TicketSystem& ticketSystem, QWidget* parent = nullptr);
    ~RegisterDialog();

    QString getUsername() const { return m_usernameEdit->text(); }
    QString getPassword() const { return m_passwordEdit->text(); }
    QString getDisplayName() const { return m_displayNameEdit->text(); }
    QString getPhone() const { return m_phoneEdit->text(); }
    QString getIdCard() const { return m_idCardEdit->text(); }

private slots:
    void onRegisterClicked();
    void validateInput();

private:
    TicketSystem& m_ticketSystem;
    QString m_username;

    QLineEdit* m_usernameEdit;
    QLineEdit* m_passwordEdit;
    QLineEdit* m_confirmPasswordEdit;
    QLineEdit* m_displayNameEdit;
    QLineEdit* m_phoneEdit;
    QLineEdit* m_idCardEdit;
    QPushButton* m_registerBtn;
    QComboBox* m_roleCombo;
};