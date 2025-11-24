#ifndef BOOKINGDIALOG_H
#define BOOKINGDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include "TicketSystem.h"

namespace Ui {
    class BookingDialog; // 对应XML中的BookingDialog UI类
}

class BookingDialog : public QDialog
{
    Q_OBJECT

public:
    BookingDialog(TicketSystem& ticketSystem, QWidget* parent = nullptr);
    ~BookingDialog() override;

private slots:
    void onSearchClicked();  // 查询按钮槽函数（对应XML中的searchBtn）
    void onBookClicked();    // 预订按钮槽函数（对应XML中的bookBtn）

private:
    Ui::BookingDialog* ui; // 关联XML UI
    TicketSystem& m_ticketSystem;

    // UI组件（与XML中的组件名完全对应）
    QComboBox* m_startStationCombo; // XML中的startStationCombo
    QComboBox* m_endStationCombo;   // XML中的endStationCombo
    QDateEdit* m_dateEdit;          // XML中的dateEdit
    QPushButton* m_searchBtn;       // XML中的searchBtn
    QTableWidget* m_trainTable;     // XML中的trainTable
    QPushButton* m_bookBtn;         // XML中的bookBtn

    // 辅助方法
    void initStations(); // 初始化车站列表（填充start/endStationCombo）
    QString getStationName(int stationId) const;
    std::string getDepartureTime(int trainId) const;
    std::string getArrivalTime(int trainId) const;
    int getAvailableSeats(int trainId) const;
};

#endif // BOOKINGDIALOG_H