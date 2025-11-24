#include "ChangeOrderDialog.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QDateTime>
#include "DateTimeHelper.h"
#include "StringHelper.h"
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
#include <QDate>
#include "ui_ChangeOrderDialog.h"


ChangeOrderDialog::ChangeOrderDialog(TicketSystem& ticketSystem, int orderId, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ChangeOrderDialog)
    , m_ticketSystem(ticketSystem)
    , m_orderId(orderId)
    , m_newTrainId(-1)
{
    ui->setupUi(this);

    // 初始化UI组件
    m_startStationCombo = ui->startStationCombo;
    m_endStationCombo = ui->endStationCombo;
    m_dateEdit = ui->dateEdit;
    m_searchBtn = ui->searchBtn;
    m_trainTable = ui->trainTable;
    m_confirmBtn = ui->confirmBtn;

    // 初始化UI
    initUI();

    // 连接信号和槽
    connect(m_searchBtn, &QPushButton::clicked, this, &ChangeOrderDialog::onSearchClicked);
    connect(m_confirmBtn, &QPushButton::clicked, this, &ChangeOrderDialog::onConfirmClicked);
    connect(m_trainTable, &QTableWidget::itemSelectionChanged, [this]() {
        m_confirmBtn->setEnabled(!m_trainTable->selectedItems().isEmpty());
        });
}

ChangeOrderDialog::~ChangeOrderDialog()
{
    delete ui;
}

void ChangeOrderDialog::initUI()
{
    // 设置日期范围为当前日期到一年后
    QDate currentDate = QDate::currentDate();
    m_dateEdit->setDate(currentDate);
    m_dateEdit->setMinimumDate(currentDate);
    m_dateEdit->setMaximumDate(currentDate.addYears(1));

    // 初始化车站列表
    m_startStationCombo->clear();
    m_endStationCombo->clear();

    auto stations = m_ticketSystem.getAllStations();
    for (const auto& station : stations) {
        m_startStationCombo->addItem(QString::fromStdString(station));
        m_endStationCombo->addItem(QString::fromStdString(station));
    }

    // 设置默认选择
    if (m_startStationCombo->count() > 0) {
        m_startStationCombo->setCurrentIndex(0);
    }
    if (m_endStationCombo->count() > 1) {
        m_endStationCombo->setCurrentIndex(1);
    }

    // 设置表格属性
    m_trainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_trainTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_trainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_trainTable->horizontalHeader()->setStretchLastSection(true);

    m_trainTable->verticalHeader()->setVisible(false); // 隐藏垂直表头
    m_trainTable->horizontalHeader()->setVisible(true); // 显示水平表头

    // 获取原始订单信息并设置默认值
    Order* order = m_ticketSystem.getOrderById(m_orderId);
    if (order) {
        // 设置出发站和到达站
        QString startStation = m_ticketSystem.getStationNameById(order->getStartStationId());
        QString endStation = m_ticketSystem.getStationNameById(order->getEndStationId());

        int startIndex = m_startStationCombo->findText(startStation);
        if (startIndex != -1) {
            m_startStationCombo->setCurrentIndex(startIndex);
        }

        int endIndex = m_endStationCombo->findText(endStation);
        if (endIndex != -1) {
            m_endStationCombo->setCurrentIndex(endIndex);
        }

        // 设置日期
        QDate orderDate = QDate::fromString(QString::fromStdString(order->getTravelDate()), "yyyy-MM-dd");
        if (orderDate.isValid()) {
            m_dateEdit->setDate(orderDate);
        }
    }
}

void ChangeOrderDialog::onSearchClicked()
{
    QString startStation = m_startStationCombo->currentText();
    QString endStation = m_endStationCombo->currentText();
    QString date = m_dateEdit->date().toString("yyyy-MM-dd");

    if (startStation.isEmpty() || endStation.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请选择出发站和到达站");
        return;
    }

    if (startStation == endStation) {
        QMessageBox::warning(this, "输入错误", "出发站和到达站不能相同");
        return;
    }

    // 查询列车
    std::vector<Train*> trains = m_ticketSystem.searchTrains(
        startStation.toStdString(),
        endStation.toStdString(),
        date.toStdString()
    );

    // 清空表格
    m_trainTable->setRowCount(0);

    if (trains.empty()) {
        QMessageBox::information(this, "查询结果", "没有找到符合条件的列车");
        m_confirmBtn->setEnabled(false);
        return;
    }

    // 填充表格
    for (const auto* train : trains) {
        if (train) {
            int row = m_trainTable->rowCount();
            m_trainTable->insertRow(row);

            int trainId = train->getTrainId();
            int availableSeats = m_ticketSystem.getAvailableSeatsForTrain(trainId, date.toStdString());

            m_trainTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(train->getTrainCode())));
            m_trainTable->setItem(row, 1, new QTableWidgetItem(startStation));
            m_trainTable->setItem(row, 2, new QTableWidgetItem(endStation));
            m_trainTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(m_ticketSystem.getDepartureTimeForTrain(trainId))));
            m_trainTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(m_ticketSystem.getArrivalTimeForTrain(trainId))));
            m_trainTable->setItem(row, 5, new QTableWidgetItem(QString::number(availableSeats)));

            // 设置余票颜色提示
            if (availableSeats <= 0) {
                m_trainTable->item(row, 5)->setBackground(Qt::red);
                m_trainTable->item(row, 5)->setForeground(Qt::white);
            }
            else if (availableSeats < 10) {
                m_trainTable->item(row, 5)->setBackground(Qt::yellow);
            }
        }
    }

    QMessageBox::information(this, "查询完成", QString("找到 %1 趟列车").arg(trains.size()));
}

void ChangeOrderDialog::onConfirmClicked()
{
    QList<QTableWidgetItem*> selectedItems = m_trainTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "改签失败", "请选择要改签的列车");
        return;
    }

    int row = selectedItems.first()->row();
    QString trainCode = m_trainTable->item(row, 0)->text();
    QString date = m_dateEdit->date().toString("yyyy-MM-dd");

    // 获取列车ID
    int newTrainId = -1;
    auto trains = m_ticketSystem.getAllTrains();
    for (const auto* train : trains) {
        if (train && QString::fromStdString(train->getTrainCode()) == trainCode) {
            newTrainId = train->getTrainId();
            break;
        }
    }

    if (newTrainId == -1) {
        QMessageBox::warning(this, "改签失败", "无法找到对应的列车信息");
        return;
    }

    // 检查余票
    int availableSeats = m_ticketSystem.getAvailableSeatsForTrain(newTrainId, date.toStdString());
    if (availableSeats <= 0) {
        QMessageBox::warning(this, "改签失败", "该列车已无余票");
        return;
    }

    // 确认改签
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认改签",
        QString("确定要将订单 %1 改签到 %2 列车吗？").arg(m_orderId).arg(trainCode),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 执行改签操作
        bool success = m_ticketSystem.changeOrder(m_orderId, newTrainId, date.toStdString());

        if (success) {
            QMessageBox::information(this, "改签成功", "车票改签成功！");
            accept();
        }
        else {
            QMessageBox::warning(this, "改签失败", "车票改签失败，请重试");
        }
    }
}

void ChangeOrderDialog::refreshTrainList()
{
    // 刷新列车列表（可以用于后续的自动刷新功能）
    onSearchClicked();
}
void ChangeOrderDialog::onSelectionChanged()
{    
    qDebug() << "Selection changed";

}