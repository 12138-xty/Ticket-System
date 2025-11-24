#ifndef CHANGEORDERDIALOG_H
#define CHANGEORDERDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "TicketSystem.h"

namespace Ui {
    class ChangeOrderDialog;
}

struct TrainInfo {
    QString number;
    QString startStation;
    QString endStation;
    QString departureTime;
    QString arrivalTime;
    int availableTickets;
};

class ChangeOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeOrderDialog(TicketSystem& ticketSystem, int orderId, QWidget* parent = nullptr);
    ~ChangeOrderDialog();

private slots:
    void onSearchClicked();   // 查询车次按钮槽函数（XML中的searchBtn）
    void onConfirmClicked();  // 确认改签按钮槽函数（XML中的confirmBtn）
    void onSelectionChanged();

private:
    Ui::ChangeOrderDialog* ui; // 关联XML UI
    TicketSystem& m_ticketSystem;
    int m_orderId;         // 待改签的订单ID
    int m_newTrainId;      // 新选择的列车ID

    // UI组件（与XML中的组件名对应）
    QComboBox* m_startStationCombo;
    QComboBox* m_endStationCombo;
    QDateEdit* m_dateEdit;
    QPushButton* m_searchBtn;
    QTableWidget* m_trainTable;
    QPushButton* m_confirmBtn;

    // 辅助方法
    void initUI();          // 初始化UI（填充车站、设置日期范围等）
    void refreshTrainList();// 刷新列车列表数据
    void connectSignals();
    void updateTrainTable();
};

#endif // CHANGEORDERDIALOG_H