#include "IdVerifyDialog.h"
#include "ui_IdVerifyDialog.h"
#include <QMessageBox>

IdVerifyDialog::IdVerifyDialog(TicketSystem& ticketSystem, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::IdVerifyDialog),
    m_ticketSystem(ticketSystem)
{
    ui->setupUi(this);
    setWindowTitle("实名认证");

    // 连接信号槽
    //connect(ui->verifyButton, &QPushButton::clicked, this, &IdVerifyDialog::on_verifyButton_clicked);
    //connect(ui->cancelButton, &QPushButton::clicked, this, &IdVerifyDialog::on_cancelButton_clicked);
    connect(ui->verifyButton, &QPushButton::clicked, this, &IdVerifyDialog::handleVerify);
    connect(ui->cancelButton, &QPushButton::clicked, this, &IdVerifyDialog::handleCancel);
}

IdVerifyDialog::~IdVerifyDialog()
{
    delete ui;
}

void IdVerifyDialog::handleVerify()
{
    QString inputIdCard = ui->idLineEdit->text().trimmed();

    if (inputIdCard.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入身份证号码");
        return;
    }

    // 获取当前用户
    User* currentUser = m_ticketSystem.getCurrentUser();
    if (!currentUser) {
        QMessageBox::warning(this, "错误", "用户未登录");
        reject();
        return;
    }

    // 验证身份证号
    if (inputIdCard == QString::fromStdString(currentUser->getIdCard())) {
        m_verified = true;
        QMessageBox::information(this, "验证成功", "实名认证通过");
        accept();
    }
    else {
        QMessageBox::warning(this, "验证失败", "身份证号码不正确");
        ui->idLineEdit->clear();
        ui->idLineEdit->setFocus();
    }
}

void IdVerifyDialog::handleCancel()
{
    reject();
}