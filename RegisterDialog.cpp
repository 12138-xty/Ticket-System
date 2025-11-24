#include "RegisterDialog.h"
#include "User.h"
#include "TicketSystem.h"
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QScrollArea>

RegisterDialog::RegisterDialog(TicketSystem& ticketSystem, QWidget* parent)
    : QDialog(parent), m_ticketSystem(ticketSystem), m_username("") {
    setWindowTitle("用户注册");
    setMinimumSize(400, 500);
    setMaximumSize(600, 600);

    // 创建滚动区域
    QScrollArea* scrollArea = new QScrollArea(this);
    QWidget* scrollContent = new QWidget(scrollArea);

    // 创建UI组件
    QLabel* usernameLabel = new QLabel("用户名:", scrollContent);
    m_usernameEdit = new QLineEdit(scrollContent);
    m_usernameEdit->setPlaceholderText("请输入用户名");

    QLabel* passwordLabel = new QLabel("密码:", scrollContent);
    m_passwordEdit = new QLineEdit(scrollContent);
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText("请输入密码");

    QLabel* confirmPasswordLabel = new QLabel("确认密码:", scrollContent);
    m_confirmPasswordEdit = new QLineEdit(scrollContent);
    m_confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    m_confirmPasswordEdit->setPlaceholderText("请再次输入密码");

    QLabel* displayNameLabel = new QLabel("姓名:", scrollContent);
    m_displayNameEdit = new QLineEdit(scrollContent);
    m_displayNameEdit->setPlaceholderText("请输入真实姓名");

    QLabel* phoneLabel = new QLabel("手机号:", scrollContent);
    m_phoneEdit = new QLineEdit(scrollContent);
    m_phoneEdit->setPlaceholderText("请输入手机号码");

    QLabel* idCardLabel = new QLabel("身份证号:", scrollContent);
    m_idCardEdit = new QLineEdit(scrollContent);
    m_idCardEdit->setPlaceholderText("请输入身份证号码");

    m_registerBtn = new QPushButton("注册", scrollContent);
    QPushButton* cancelBtn = new QPushButton("取消", scrollContent);

    QLabel* roleLabel = new QLabel("身份:", scrollContent);
    m_roleCombo = new QComboBox(scrollContent);
    m_roleCombo->addItem("普通用户");
    m_roleCombo->addItem("管理员");
    m_roleCombo->setCurrentIndex(0);

    // 表单布局
    QGridLayout* formLayout = new QGridLayout(scrollContent);
    formLayout->addWidget(usernameLabel, 0, 0);
    formLayout->addWidget(m_usernameEdit, 0, 1);
    formLayout->addWidget(passwordLabel, 1, 0);
    formLayout->addWidget(m_passwordEdit, 1, 1);
    formLayout->addWidget(confirmPasswordLabel, 2, 0);
    formLayout->addWidget(m_confirmPasswordEdit, 2, 1);
    formLayout->addWidget(displayNameLabel, 3, 0);
    formLayout->addWidget(m_displayNameEdit, 3, 1);
    formLayout->addWidget(phoneLabel, 4, 0);
    formLayout->addWidget(m_phoneEdit, 4, 1);
    formLayout->addWidget(idCardLabel, 5, 0);
    formLayout->addWidget(m_idCardEdit, 5, 1);
    formLayout->addWidget(roleLabel, 6, 0);        
    formLayout->addWidget(m_roleCombo, 6, 1);

    // 按钮布局
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_registerBtn);
    buttonLayout->addWidget(cancelBtn);

    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonLayout);

    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);

    // 连接信号槽
    connect(m_registerBtn, &QPushButton::clicked, this, &RegisterDialog::onRegisterClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &RegisterDialog::reject);

    // 实时验证输入
    connect(m_usernameEdit, &QLineEdit::textChanged, this, &RegisterDialog::validateInput);
    connect(m_passwordEdit, &QLineEdit::textChanged, this, &RegisterDialog::validateInput);
    connect(m_confirmPasswordEdit, &QLineEdit::textChanged, this, &RegisterDialog::validateInput);
    connect(m_displayNameEdit, &QLineEdit::textChanged, this, &RegisterDialog::validateInput);
    connect(m_phoneEdit, &QLineEdit::textChanged, this, &RegisterDialog::validateInput);
    connect(m_idCardEdit, &QLineEdit::textChanged, this, &RegisterDialog::validateInput);
    connect(m_roleCombo, &QComboBox::currentTextChanged, this, &RegisterDialog::validateInput);

    validateInput(); // 初始验证
}

RegisterDialog::~RegisterDialog() {}

void RegisterDialog::onRegisterClicked() {
    QString username = m_usernameEdit->text().trimmed();
    QString password = m_passwordEdit->text();
    QString confirmPassword = m_confirmPasswordEdit->text();
    QString displayName = m_displayNameEdit->text().trimmed();
    QString phone = m_phoneEdit->text().trimmed();
    QString idCard = m_idCardEdit->text().trimmed();
    QString role = m_roleCombo->currentText() == "管理员" ? "admin" : "user";

    // 按顺序验证每个字段，发现错误立即返回并提示
    if (username.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名不能为空");
        m_usernameEdit->setFocus();
        return;
    }

    QRegularExpression usernameRegex("^[a-zA-Z0-9_]+$");
    if (!usernameRegex.match(username).hasMatch()) {
        QMessageBox::warning(this, "输入错误", "用户名只能包含字母、数字和下划线");
        m_usernameEdit->setFocus();
        m_usernameEdit->selectAll();
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "密码不能为空");
        m_passwordEdit->setFocus();
        return;
    }

    if (password.length() < 6) {
        QMessageBox::warning(this, "输入错误", "密码长度至少为6位");
        m_passwordEdit->setFocus();
        m_passwordEdit->selectAll();
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "输入错误", "两次输入的密码不一致");
        m_confirmPasswordEdit->setFocus();
        m_confirmPasswordEdit->selectAll();
        return;
    }

    if (displayName.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "姓名不能为空");
        m_displayNameEdit->setFocus();
        return;
    }

    if (phone.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "手机号不能为空");
        m_phoneEdit->setFocus();
        return;
    }

    if (!StringHelper::isValidPhone(phone)) {
        QMessageBox::warning(this, "输入错误", "请输入有效的手机号码（11位数字）");
        m_phoneEdit->setFocus();
        m_phoneEdit->selectAll();
        return;
    }

    if (idCard.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "身份证号不能为空");
        m_idCardEdit->setFocus();
        return;
    }

    if (!StringHelper::isValidIdCard(idCard)) {
        QMessageBox::warning(this, "输入错误", "请输入有效的身份证号码（18位）");
        m_idCardEdit->setFocus();
        m_idCardEdit->selectAll();
        return;
    }

    // 检查用户名是否已存在（这是最后检查的，因为前面的格式验证更重要）
    if (!m_ticketSystem.isUsernameAvailable(username.toStdString())) {
        QMessageBox::warning(this, "注册失败", "用户名已存在，请选择其他用户名");
        m_usernameEdit->setFocus();
        m_usernameEdit->selectAll();
        return;
    }

    // 所有验证通过，执行注册
    bool success = m_ticketSystem.registerUser(
        username.toStdString(),
        password.toStdString(),
        displayName.toStdString(),
        phone.toStdString(),
        idCard.toStdString(),
        role.toStdString()
    );

    if (success) {
        QMessageBox::information(this, "注册成功", "用户注册成功，请登录");
        m_username = username;
        accept();
    }
    else {
        QMessageBox::warning(this, "注册失败", "注册失败，请稍后重试");
    }
}

void RegisterDialog::validateInput() {
    bool valid = !m_usernameEdit->text().trimmed().isEmpty() &&
        !m_passwordEdit->text().isEmpty() &&
        !m_confirmPasswordEdit->text().isEmpty() &&
        !m_displayNameEdit->text().trimmed().isEmpty() &&
        !m_phoneEdit->text().trimmed().isEmpty() &&
        !m_idCardEdit->text().trimmed().isEmpty();

    m_registerBtn->setEnabled(valid);
}
