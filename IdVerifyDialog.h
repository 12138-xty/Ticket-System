#ifndef IDVERIFYDIALOG_H
#define IDVERIFYDIALOG_H

#include <QDialog>
#include "TicketSystem.h"

namespace Ui {
    class IdVerifyDialog;
}

class IdVerifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IdVerifyDialog(TicketSystem& ticketSystem, QWidget* parent = nullptr);
    ~IdVerifyDialog();

    bool isVerified() const { return m_verified; }

private slots:
    //void on_verifyButton_clicked();
    //void on_cancelButton_clicked();
    void handleVerify();
    void handleCancel();

private:
    Ui::IdVerifyDialog* ui;
    TicketSystem& m_ticketSystem;
    bool m_verified = false;
};

#endif // IDVERIFYDIALOG_H