#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LoginDialog.h"
#include "BookingDialog.h"
#include "AdminPanel.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"
#include "DatabaseManager.h"
#include "ChangeOrderDialog.h"
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
#include <QCoreApplication>
#include <QGridLayout>
#include "IdVerifyDialog.h"
#include "UserInfoDialog.h"

MainWindow::MainWindow(TicketSystem& ticketSystem, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ticketSystem(ticketSystem)
    , m_currentUser(nullptr)
{
    ui->setupUi(this);

    // 获取当前用户
    m_currentUser = m_ticketSystem.getCurrentUser();

    if (m_currentUser) {
        // 根据用户角色决定显示哪个页面
        if (m_ticketSystem.isAdminUser(m_currentUser->getUserId())) {
            // 管理员：显示管理员欢迎页面
            showAdminWelcomePage();
        }
        else {
            // 普通用户：显示用户欢迎页面
            showUserWelcomePage();
        }
    }

    // 初始化主界面
    initializeMainInterface();

    // 连接信号和槽
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::showSearchPage);
    connect(ui->bookingButton, &QPushButton::clicked, this, &MainWindow::showBookingPage);
    connect(ui->adminButton, &QPushButton::clicked, this, &MainWindow::showAdminPage);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
    connect(ui->deleteAccountButton, &QPushButton::clicked, this, &MainWindow::onDeleteAccountClicked);
    connect(ui->userInfoButton, &QPushButton::clicked, this, &MainWindow::onEditProfileClicked);

    // 菜单动作连接
    connect(ui->actionSearch, &QAction::triggered, this, &MainWindow::onSearchActionTriggered);
    connect(ui->actionBook, &QAction::triggered, this, &MainWindow::onBookActionTriggered);
    connect(ui->actionMyOrders, &QAction::triggered, this, &MainWindow::onOrderActionTriggered);
    connect(ui->actionAdmin, &QAction::triggered, this, &MainWindow::onAdminActionTriggered);
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::onLogoutClicked);
    connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);

    // 更新UI显示用户信息
    updateUIForUser();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMainInterface()
{

    // 创建各个页面
    createWelcomePage();
    createSearchPage();
    createBookingPage();
    createAdminPage();

    // 确保所有页面都有正确的背景色
    ui->welcomePage->setStyleSheet("background-color: #f8f9fa;");
    ui->searchPage->setStyleSheet("background-color: #f8f9fa;");
    ui->bookingPage->setStyleSheet("background-color: #f8f9fa;");
    ui->adminPage->setStyleSheet("background-color: #f8f9fa;");

    // 默认显示欢迎页面
    ui->contentStack->setCurrentIndex(0);

    // 强制刷新界面
    ui->contentStack->update();
    update();
}

void MainWindow::createWelcomePage(){}

void MainWindow::createSearchPage()
{
    QWidget* searchPage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(searchPage);

    // 创建搜索控件
    QWidget* searchWidget = new QWidget();
    QHBoxLayout* searchLayout = new QHBoxLayout(searchWidget);

    QComboBox* startStationCombo = new QComboBox();
    QComboBox* endStationCombo = new QComboBox();
    QDateEdit* dateEdit = new QDateEdit();
    dateEdit->setCalendarPopup(true);
    dateEdit->setDate(QDate::currentDate());

    QPushButton* searchBtn = new QPushButton("查询");

    // 填充车站列表
    auto stations = m_ticketSystem.getAllStations();
    for (const auto& station : stations) {
        startStationCombo->addItem(QString::fromStdString(station));
        endStationCombo->addItem(QString::fromStdString(station));
    }

    searchLayout->addWidget(new QLabel("出发站:"));
    searchLayout->addWidget(startStationCombo);
    searchLayout->addWidget(new QLabel("到达站:"));
    searchLayout->addWidget(endStationCombo);
    searchLayout->addWidget(new QLabel("日期:"));
    searchLayout->addWidget(dateEdit);
    searchLayout->addWidget(searchBtn);
    searchLayout->addStretch();

    // 创建结果表格
    QTableWidget* resultTable = new QTableWidget();
    resultTable->setColumnCount(6);
    resultTable->setHorizontalHeaderLabels({ "车次", "出发站", "到达站", "出发时间", "到达时间", "余票" });
    resultTable->horizontalHeader()->setStretchLastSection(true);
    resultTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    resultTable->verticalHeader()->setVisible(false); // 隐藏垂直表头
    resultTable->horizontalHeader()->setVisible(true); // 显示水平表头

    layout->addWidget(searchWidget);
    layout->addWidget(resultTable);

    // 连接查询按钮
    // 在 createSearchPage 方法中修改查询逻辑
    connect(searchBtn, &QPushButton::clicked, [this, startStationCombo, endStationCombo, dateEdit, resultTable]() {
        QString startStation = startStationCombo->currentText();
        QString endStation = endStationCombo->currentText();
        QString date = dateEdit->date().toString("yyyy-MM-dd");

        if (startStation.isEmpty() || endStation.isEmpty()) {
            QMessageBox::warning(this, "错误", "请选择出发站和到达站");
            return;
        }

        if (startStation == endStation) {
            QMessageBox::warning(this, "错误", "出发站和到达站不能相同");
            return;
        }

        // 查询列车
        auto trains = m_ticketSystem.searchTrains(
            startStation.toStdString(),
            endStation.toStdString(),
            date.toStdString()
        );

        resultTable->setRowCount(0);

        // 添加日期提示
        QString dateInfo;
        if (dateEdit->date() == QDate::currentDate()) {
            dateInfo = "（今天当前时间之后的班次）";
        }

        if (trains.empty()) {
            QMessageBox::information(this, "查询结果",
                QString("没有找到符合条件的列车%1").arg(dateInfo));
            return;
        }

        for (const auto* train : trains) {
            if (train) {
                int row = resultTable->rowCount();
                resultTable->insertRow(row);

                int trainId = train->getTrainId();
                int availableSeats = m_ticketSystem.getAvailableSeatsForTrain(trainId, date.toStdString());

                resultTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(train->getTrainCode())));
                resultTable->setItem(row, 1, new QTableWidgetItem(startStation));
                resultTable->setItem(row, 2, new QTableWidgetItem(endStation));
                resultTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(m_ticketSystem.getDepartureTimeForTrain(trainId))));
                resultTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(m_ticketSystem.getArrivalTimeForTrain(trainId))));
                resultTable->setItem(row, 5, new QTableWidgetItem(QString::number(availableSeats)));
            }
        }

        QMessageBox::information(this, "查询完成",
            QString("找到 %1 趟列车%2").arg(trains.size()).arg(dateInfo));
        });

    // 替换UI中的searchPage
    int index = ui->contentStack->indexOf(ui->searchPage);
    ui->contentStack->removeWidget(ui->searchPage);
    ui->contentStack->insertWidget(index, searchPage);
    ui->searchPage = searchPage;
}

void MainWindow::createBookingPage()
{
    QWidget* bookingPage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(bookingPage);

    // 创建订单列表
    QTableWidget* orderTable = new QTableWidget();
    orderTable->setColumnCount(7);
    orderTable->setHorizontalHeaderLabels({ "订单号", "车次", "出发站", "到达站", "日期", "状态", "操作" });
    orderTable->horizontalHeader()->setStretchLastSection(true);

    orderTable->verticalHeader()->setVisible(false); // 隐藏垂直表头
    orderTable->horizontalHeader()->setVisible(true); // 显示水平表头

    // 刷新按钮
    QPushButton* refreshBtn = new QPushButton("刷新订单");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshBtn);

    layout->addWidget(orderTable);
    layout->addLayout(buttonLayout);

    // 连接刷新按钮
    connect(refreshBtn, &QPushButton::clicked, [this, orderTable]() {
        refreshOrderList(orderTable);
        });

    // 初始刷新订单列表
    refreshOrderList(orderTable);

    // 替换UI中的bookingPage
    int index = ui->contentStack->indexOf(ui->bookingPage);
    ui->contentStack->removeWidget(ui->bookingPage);
    ui->contentStack->insertWidget(index, bookingPage);
    ui->bookingPage = bookingPage;
}

void MainWindow::createAdminPage()
{
    QWidget* adminPage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(adminPage);

    QLabel* adminLabel = new QLabel("管理员功能页面");
    adminLabel->setAlignment(Qt::AlignCenter);
    adminLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    layout->addWidget(adminLabel);

    // 替换UI中的adminPage
    int index = ui->contentStack->indexOf(ui->adminPage);
    ui->contentStack->removeWidget(ui->adminPage);
    ui->contentStack->insertWidget(index, adminPage);
    ui->adminPage = adminPage;
}

void MainWindow::updateUIForUser()
{
    if (m_currentUser) {
        // 更新用户信息显示
        ui->userNameLabel->setText(QString::fromStdString(m_currentUser->getDisplayName()));
        ui->userTypeLabel->setText(QString::fromStdString(m_currentUser->getRole()));

        // 如果是管理员，显示管理按钮
        if (m_ticketSystem.isAdminUser(m_currentUser->getUserId())) {
            ui->adminButton->setVisible(true);
            ui->actionAdmin->setEnabled(true);
        }
        else {
            ui->adminButton->setVisible(false);
            ui->actionAdmin->setEnabled(false);
        }

        // 启用功能按钮
        ui->searchButton->setEnabled(true);
        ui->bookingButton->setEnabled(true);
        ui->actionSearch->setEnabled(true);
        ui->actionBook->setEnabled(true);
        ui->actionMyOrders->setEnabled(true);

    }
    else {
        // 未登录状态
        ui->userNameLabel->setText("未登录");
        ui->userTypeLabel->setText("");

        // 禁用功能按钮
        ui->searchButton->setEnabled(false);
        ui->bookingButton->setEnabled(false);
        ui->adminButton->setEnabled(false);
        ui->actionSearch->setEnabled(false);
        ui->actionBook->setEnabled(false);
        ui->actionMyOrders->setEnabled(false);
        ui->actionAdmin->setEnabled(false);
    }
}

void MainWindow::onLoginClicked()
{
}

void MainWindow::onLogoutClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认退出", "确定要退出登录吗？",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_ticketSystem.logout();
        m_currentUser = nullptr;
        updateUIForUser();

        // 显示欢迎页面
        ui->contentStack->setCurrentIndex(0);

       
        QApplication::exit(QDialog::Accepted);
    }
}

void MainWindow::showSearchPage()
{
    if (!m_currentUser) {
        QMessageBox::warning(this, "错误", "请先登录");
        return;
    }
    ui->contentStack->setCurrentIndex(1);
}

void MainWindow::showBookingPage()
{
    if (!m_currentUser) {
        QMessageBox::warning(this, "错误", "请先登录");
        return;
    }
    ui->contentStack->setCurrentIndex(2);
}

void MainWindow::showAdminPage()
{
    if (!m_currentUser || !m_ticketSystem.isAdminUser(m_currentUser->getUserId())) {
        QMessageBox::warning(this, "错误", "无管理员权限");
        return;
    }

    // 显示管理员面板
    AdminPanel adminPanel(m_ticketSystem, this);
    adminPanel.exec();
}

void MainWindow::refreshOrderList(QTableWidget* orderTable)
{
    if (!m_currentUser) return;

    orderTable->setRowCount(0);

    // 根据用户角色决定显示的列标签
    bool isAdmin = m_ticketSystem.isAdminUser(m_currentUser->getUserId());

    // 设置表格列数
    orderTable->setColumnCount(isAdmin ? 9 : 8); // 增加一列用于显示出发时间

    if (isAdmin) {
        // 管理员显示所有信息
        orderTable->setHorizontalHeaderLabels({ "订单号", "用户ID", "姓名", "车次", "出发站", "到达站", "出发时间", "日期", "状态", "操作" });
    }
    else {
        // 普通用户显示简化信息
        orderTable->setHorizontalHeaderLabels({ "订单号", "车次", "出发站", "到达站", "出发时间", "日期", "状态", "操作" });
    }

    // 获取用户订单
    std::vector<Order> orders = m_ticketSystem.getUserOrdersWithDetails(m_currentUser->getUserId());

    // 分离历史订单和未出发订单
    std::vector<Order> historyOrders;
    std::vector<Order> upcomingOrders;
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    for (const auto& order : orders) {
        QString travelDate = QString::fromStdString(order.getTravelDate());
        QDate orderDate = QDate::fromString(travelDate, "yyyy-MM-dd");

        // 获取出发时间
        std::string departTimeStr = m_ticketSystem.getDepartureTimeForTrain(order.getTrainId());
        QTime departTime = QTime::fromString(QString::fromStdString(departTimeStr), "HH:mm");

        if (orderDate < currentDate ||
            (orderDate == currentDate && departTime < currentTime)) {
            historyOrders.push_back(order);
        }
        else {
            upcomingOrders.push_back(order);
        }
    }

    // 先显示未出发订单，再显示历史订单
    // 替换原来的 displayOrdersSection 调用
    if (!upcomingOrders.empty()) {
        // 添加分区标题行
        int titleRow = orderTable->rowCount();
        orderTable->insertRow(titleRow);

        QTableWidgetItem* titleItem = new QTableWidgetItem("未出发订单");
        titleItem->setBackground(QColor(240, 240, 240));
        titleItem->setForeground(QColor(0, 0, 0));
        titleItem->setFont(QFont("Arial", 10, QFont::Bold));

        int columnSpan = isAdmin ? 10 : 8;
        orderTable->setItem(titleRow, 0, titleItem);
        orderTable->setSpan(titleRow, 0, 1, columnSpan);

        // 添加订单行
        for (const auto& order : upcomingOrders) {
            addOrderToTable(orderTable, order, isAdmin, false);
        }
    }

    if (!historyOrders.empty()) {
        // 添加分区标题行
        int titleRow = orderTable->rowCount();
        orderTable->insertRow(titleRow);

        QTableWidgetItem* titleItem = new QTableWidgetItem("历史订单");
        titleItem->setBackground(QColor(240, 240, 240));
        titleItem->setForeground(QColor(0, 0, 0));
        titleItem->setFont(QFont("Arial", 10, QFont::Bold));

        int columnSpan = isAdmin ? 10 : 8;
        orderTable->setItem(titleRow, 0, titleItem);
        orderTable->setSpan(titleRow, 0, 1, columnSpan);

        // 添加订单行
        for (const auto& order : historyOrders) {
            addOrderToTable(orderTable, order, isAdmin, true);
        }
    }

    // 调整列宽
    orderTable->resizeColumnsToContents();
    orderTable->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::addOrderToTable(QTableWidget* orderTable, const Order& order, bool isAdmin, bool isHistory)
{
    int row = orderTable->rowCount();
    orderTable->insertRow(row);

    std::string trainCode = m_ticketSystem.getTrainCodeByOrder(order);

    QString startStation = m_ticketSystem.getStationNameById(order.getStartStationId());
    QString endStation = m_ticketSystem.getStationNameById(order.getEndStationId());

    std::string departTimeStr = m_ticketSystem.getDepartureTimeForTrain(order.getTrainId());

    QString displayName = "未知用户";
    if (isAdmin) {
        User* user = m_ticketSystem.getUserById(std::to_string(order.getUserId()));
        if (user) {
            displayName = QString::fromStdString(user->getDisplayName());
        }
    }

    int col = 0;
    orderTable->setItem(row, col++, new QTableWidgetItem(QString::number(order.getOrderId())));

    if (isAdmin) {
        orderTable->setItem(row, col++, new QTableWidgetItem(QString::number(order.getUserId())));
        orderTable->setItem(row, col++, new QTableWidgetItem(displayName));
    }

    orderTable->setItem(row, col++, new QTableWidgetItem(QString::fromStdString(trainCode)));
    orderTable->setItem(row, col++, new QTableWidgetItem(startStation));
    orderTable->setItem(row, col++, new QTableWidgetItem(endStation));  
    orderTable->setItem(row, col++, new QTableWidgetItem(QString::fromStdString(departTimeStr)));
    orderTable->setItem(row, col++, new QTableWidgetItem(QString::fromStdString(order.getTravelDate())));
    QTableWidgetItem* statusItem = new QTableWidgetItem(QString::fromStdString(order.getStatus()));
    if (order.getStatus() == "booked") {
        statusItem->setBackground(Qt::green);
        statusItem->setForeground(Qt::black);
    }
    else if (order.getStatus() == "canceled") {
        statusItem->setBackground(Qt::red);
        statusItem->setForeground(Qt::white);
    }
    else if (order.getStatus() == "changed") {
        statusItem->setBackground(Qt::yellow);
        statusItem->setForeground(Qt::black);
    }
    orderTable->setItem(row, col++, statusItem);

    QWidget* actionWidget = new QWidget();
    QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
    actionLayout->setContentsMargins(0, 0, 0, 0);

    bool canOperate = (order.getUserId() == StringHelper::toInt(QString::fromStdString(m_currentUser->getUserId()))) ||
        m_ticketSystem.isAdminUser(m_currentUser->getUserId());

    if (!isHistory && order.getStatus() == "booked" && canOperate) {
        QPushButton* cancelBtn = new QPushButton("取消");
        QPushButton* changeBtn = new QPushButton("改签");

        // 使用正确的连接方式
        connect(cancelBtn, &QPushButton::clicked, this, [this, orderId = order.getOrderId()]() {
            cancelOrder(orderId);
            });

        connect(changeBtn, &QPushButton::clicked, this, [this, orderId = order.getOrderId()]() {
            changeOrder(orderId);
            });

        actionLayout->addWidget(cancelBtn);
        actionLayout->addWidget(changeBtn);
    }
    else if (order.getStatus() == "canceled") {
        QLabel* statusLabel = new QLabel("已取消");
        statusLabel->setStyleSheet("color: gray;");
        actionLayout->addWidget(statusLabel);
    }
    else if (order.getStatus() == "changed") {
        QLabel* statusLabel = new QLabel("已改签");
        statusLabel->setStyleSheet("color: blue;");
        actionLayout->addWidget(statusLabel);
    }
    else if (isHistory) {
        QLabel* historyLabel = new QLabel("已出发");
        historyLabel->setStyleSheet("color: darkgray;");
        actionLayout->addWidget(historyLabel);
    }

    orderTable->setCellWidget(row, col, actionWidget);
}

void MainWindow::cancelOrder(int orderId)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认取消", "确定要取消这个订单吗？",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_ticketSystem.cancelOrder(orderId)) {
            QMessageBox::information(this, "成功", "订单取消成功");
            // 刷新订单列表
            QTableWidget* orderTable = findChild<QTableWidget*>();
            if (orderTable) {
                refreshOrderList(orderTable);
            }
        }
        else {
            QMessageBox::warning(this, "失败", "订单取消失败");
        }
    }
}

void MainWindow::changeOrder(int orderId)
{
    ChangeOrderDialog changeDialog(m_ticketSystem, orderId, this);
    if (changeDialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "成功", "车票改签成功");
        // 刷新订单列表 - 需要找到当前的订单表格并刷新
        QTableWidget* orderTable = findChild<QTableWidget*>();
        if (orderTable) {
            refreshOrderList(orderTable);
        }
    }
}

void MainWindow::onSearchActionTriggered()
{
    showSearchPage();
}

void MainWindow::onBookActionTriggered()
{
    if (!m_currentUser) {
        QMessageBox::warning(this, "错误", "请先登录");
        return;
    }

    // 检查是否为管理员
    if (m_ticketSystem.isAdminUser(m_currentUser->getUserId())) {
        QMessageBox::warning(this, "错误", "管理员身份不能购票");
        return;
    }

    BookingDialog bookingDialog(m_ticketSystem, this);
    bookingDialog.exec();
}

void MainWindow::onOrderActionTriggered()
{
    showBookingPage();
}

void MainWindow::onAdminActionTriggered()
{
    showAdminPage();
}

void MainWindow::showAdminWelcomePage() {
    ui->adminButton->setVisible(true);
    ui->actionAdmin->setEnabled(true);
}

void MainWindow::showUserWelcomePage() {
    ui->adminButton->setVisible(false);
    ui->actionAdmin->setEnabled(false);
}

void MainWindow::onDeleteAccountClicked() {
    if (!m_currentUser) return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认注销",
        "确定要注销当前账号吗？此操作不可恢复！",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_ticketSystem.deleteUser(m_currentUser->getUserId())) {
            QMessageBox::information(this, "成功", "账号已注销");
            onLogoutClicked(); // 自动退出登录
        }
        else {
            QMessageBox::warning(this, "失败", "注销账号失败");
        }
    }
}

void MainWindow::onEditProfileClicked()
{
    if (!m_currentUser) {
        QMessageBox::warning(this, "错误", "请先登录");
        return;
    }

    // 如果是管理员，直接进入编辑（或者也可以要求验证）
    if (m_ticketSystem.isAdminUser(m_currentUser->getUserId())) {
        QMessageBox::information(this, "提示", "管理员可直接修改用户信息");
        // 这里可以跳转到管理员编辑界面
        return;
    }

    // 普通用户需要实名认证
    IdVerifyDialog verifyDialog(m_ticketSystem, this);
    if (verifyDialog.exec() == QDialog::Accepted) {
        if (verifyDialog.isVerified()) {
            // 认证通过，打开个人信息修改对话框
            UserInfoDialog infoDialog(m_ticketSystem, this);
            infoDialog.exec();
        }
    }
}