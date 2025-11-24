#include "BookingDialog.h"
#include "ui_BookingDialog.h"
#include "TicketSystem.h"
#include "Train.h"
#include "User.h"
#include <QMessageBox>

using namespace std;

BookingDialog::BookingDialog(TicketSystem& ticketSystem, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::BookingDialog)
    , m_ticketSystem(ticketSystem)
{
    ui->setupUi(this);

    // 初始化UI组件
    m_startStationCombo = ui->startStationCombo;
    m_endStationCombo = ui->endStationCombo;
    m_dateEdit = ui->dateEdit;
    m_searchBtn = ui->searchBtn;
    m_trainTable = ui->trainTable;
    m_bookBtn = ui->bookBtn;

    // 设置日期范围为当前日期到一年后
    QDate currentDate = QDate::currentDate();
    m_dateEdit->setDate(currentDate);
    m_dateEdit->setMinimumDate(currentDate);
    m_dateEdit->setMaximumDate(currentDate.addYears(1));

    // 初始化车站列表
    initStations();

    // 设置表格属性
    m_trainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_trainTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_trainTable->horizontalHeader()->setStretchLastSection(true);

    m_trainTable->verticalHeader()->setVisible(false); // 隐藏垂直表头（行号）
    m_trainTable->horizontalHeader()->setVisible(true); // 显示水平表头（列名）

    // 连接信号和槽
    connect(m_searchBtn, &QPushButton::clicked, this, &BookingDialog::onSearchClicked);
    connect(m_bookBtn, &QPushButton::clicked, this, &BookingDialog::onBookClicked);
    connect(m_trainTable, &QTableWidget::itemSelectionChanged, [this]() {
        m_bookBtn->setEnabled(!m_trainTable->selectedItems().isEmpty());
        });
}

BookingDialog::~BookingDialog()
{
    delete ui;
}

void BookingDialog::initStations()
{
    m_startStationCombo->clear();
    m_endStationCombo->clear();

    // 从TicketSystem获取所有车站
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
}

void BookingDialog::onSearchClicked()
{
    QString startStation = m_startStationCombo->currentText();
    QString endStation = m_endStationCombo->currentText();
    QDate selectedDate = m_dateEdit->date();
    QString date = selectedDate.toString("yyyy-MM-dd");

    if (startStation.isEmpty() || endStation.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请选择出发站和到达站");
        return;
    }

    if (startStation == endStation) {
        QMessageBox::warning(this, "输入错误", "出发站和到达站不能相同");
        return;
    }

    // 检查日期是否有效
    if (selectedDate < QDate::currentDate()) {
        QMessageBox::warning(this, "日期错误", "不能查询过去日期的车票");
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
        QString message;
        if (selectedDate == QDate::currentDate()) {
            message = "今天当前时间之后没有符合条件的列车，请选择其他日期";
        }
        else if (selectedDate > QDate::currentDate()) {
            message = "该日期没有符合条件的列车";
        }
        else {
            message = "不能查询过去日期的车票";
        }
        QMessageBox::information(this, "查询结果", message);
        return;
    }

    // 设置表格列
    m_trainTable->setColumnCount(7);
    m_trainTable->setHorizontalHeaderLabels({ "车次ID", "车次", "类型", "出发站", "到达站", "出发时间", "余票" });

    // 填充表格
    for (const auto* train : trains) {
        if (train) {
            int row = m_trainTable->rowCount();
            m_trainTable->insertRow(row);

            int trainId = train->getTrainId();
            int availableSeats = m_ticketSystem.getAvailableSeatsForTrain(trainId, date.toStdString());

            m_trainTable->setItem(row, 0, new QTableWidgetItem(QString::number(trainId)));
            m_trainTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(train->getTrainCode())));
            m_trainTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(train->getType())));
            m_trainTable->setItem(row, 3, new QTableWidgetItem(startStation));
            m_trainTable->setItem(row, 4, new QTableWidgetItem(endStation));
            m_trainTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(getDepartureTime(trainId))));
            m_trainTable->setItem(row, 6, new QTableWidgetItem(QString::number(availableSeats)));

            // 设置余票颜色提示
            if (availableSeats <= 0) {
                m_trainTable->item(row, 6)->setBackground(Qt::red);
                m_trainTable->item(row, 6)->setForeground(Qt::white);
            }
            else if (availableSeats < 10) {
                m_trainTable->item(row, 6)->setBackground(Qt::yellow);
            }
        }
    }

    // 调整列宽
    m_trainTable->resizeColumnsToContents();

    // 添加日期提示信息
    QString dateInfo;
    if (selectedDate == QDate::currentDate()) {
        dateInfo = "（显示今天当前时间之后的班次）";
    }

    QMessageBox::information(this, "查询完成", QString("找到 %1 趟列车%2").arg(trains.size()).arg(dateInfo));
}

void BookingDialog::onBookClicked()
{
    User* currentUser = m_ticketSystem.getCurrentUser();
    if (!currentUser) {
        QMessageBox::warning(this, "预订失败", "请先登录");
        return;
    }

    if (m_ticketSystem.isAdminUser(currentUser->getUserId())) {
        QMessageBox::warning(this, "预订失败", "管理员身份不能购票");
        return;
    }

    QList<QTableWidgetItem*> selectedItems = m_trainTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "预订失败", "请选择要预订的列车");
        return;
    }

    int row = selectedItems.first()->row();
    int trainId = m_trainTable->item(row, 0)->text().toInt();
    QString date = m_dateEdit->date().toString("yyyy-MM-dd");

    // 获取用户选择的站点ID
    QString startStation = m_startStationCombo->currentText();
    QString endStation = m_endStationCombo->currentText();

    int startStationId = -1, endStationId = -1;
    const auto& stations = m_ticketSystem.getStations();
    for (const auto& station : stations) {
        if (station.getName() == startStation) startStationId = station.getStationId();
        if (station.getName() == endStation) endStationId = station.getStationId();
    }

    if (startStationId == -1 || endStationId == -1) {
        QMessageBox::warning(this, "错误", "无效的车站选择");
        return;
    }

    // 检查余票
    int availableSeats = m_ticketSystem.getAvailableSeatsForTrain(trainId, date.toStdString());
    if (availableSeats <= 0) {
        QMessageBox::warning(this, "预订失败", "该列车已无余票");
        return;
    }

    // 预订车票，传递站点ID
    bool success = m_ticketSystem.bookTicket(
        currentUser->getUserId(),
        trainId,
        date.toStdString(),
        startStationId,
        endStationId
    );

    if (success) {
        QMessageBox::information(this, "预订成功", "车票预订成功！");
        onSearchClicked();
    }
    else {
        QMessageBox::warning(this, "预订失败", "车票预订失败，请重试");
    }
}
QString BookingDialog::getStationName(int stationId) const
{
    return m_ticketSystem.getStationNameById(stationId);
}

std::string BookingDialog::getDepartureTime(int trainId) const
{
    return m_ticketSystem.getDepartureTimeForTrain(trainId);
}

std::string BookingDialog::getArrivalTime(int trainId) const
{
    return m_ticketSystem.getArrivalTimeForTrain(trainId);
}

int BookingDialog::getAvailableSeats(int trainId) const
{
    QString date = m_dateEdit->date().toString("yyyy-MM-dd");
    return m_ticketSystem.getAvailableSeatsForTrain(trainId, date.toStdString());
}