#include "TicketSystem.h"
#include "DateTimeHelper.h"
#include "StringHelper.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <vector>
#include <QDir>
#include <QCoreApplication>
#include <algorithm>
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
#include <QTimer>
#include <QLabel>
#include <QTimeEdit>
#include <QHeaderView>

TicketSystem::TicketSystem(QObject* parent)
    : QObject(parent),
    dbManager("D:/TicketSystem/Ticketsystem/data"),
    undoManager(dbManager) {

    qDebug() << "数据库路径:" << QCoreApplication::applicationDirPath() + "/data";

    qDebug() << "应用程序目录:" << QCoreApplication::applicationDirPath();
    qDebug() << "数据目录:" << QCoreApplication::applicationDirPath() + "/data";

    QDir dataDir(QCoreApplication::applicationDirPath() + "/data");
    if (!dataDir.exists()) {
        qDebug() << "数据目录不存在，尝试创建...";
        if (dataDir.mkpath(".")) {
            qDebug() << "数据目录创建成功";
        }
        else {
            qDebug() << "数据目录创建失败";
        }
    }

    // 检查 users.txt 文件
    QFile userFile(QCoreApplication::applicationDirPath() + "/data/users.txt");
    if (!userFile.exists()) {
        qDebug() << "users.txt 文件不存在";
    }
    else {
        qDebug() << "users.txt 文件存在，大小:" << userFile.size() << "字节";
    }

    if (!dbManager.init()) {
        qCritical() << "数据库初始化失败！";
        // 尝试创建数据目录
        QDir dataDir(QCoreApplication::applicationDirPath() + "/data");
        if (!dataDir.exists()) {
            dataDir.mkpath(".");
        }
        // 重新尝试初始化
        if (!dbManager.init()) {
            qCritical() << "无法初始化数据库系统！";
        }
    }
}

TicketSystem::~TicketSystem() {
    
}

bool TicketSystem::validateLogin(const QString& userId, const QString& password) {
    qDebug() << "=== 开始登录验证 ===";
    qDebug() << "原始输入 - 用户ID:" << userId << "密码:" << password;

    QString cleanInput = userId;
    cleanInput.replace("\"", "");
    cleanInput = cleanInput.trimmed();

    QString cleanPassword = password;
    cleanPassword.replace("\"", "");
    cleanPassword = cleanPassword.trimmed();

    qDebug() << "清理后 - 用户ID:" << cleanInput << "密码:" << cleanPassword;

    // 获取所有用户进行调试
    auto allUsers = dbManager.getUsers();
    qDebug() << "数据库中的用户数量:" << allUsers.size();
    for (const auto& user : allUsers) {
        qDebug() << "数据库用户 - ID:" << QString::fromStdString(user.getUserId())
            << "用户名:" << QString::fromStdString(user.getUsername())
            << "密码:" << QString::fromStdString(user.getPassword());
    }
    User* user = dbManager.getUserById(cleanInput.toStdString());

    if (!user) {
        qDebug() << "未找到用户:" << cleanInput;
        return false;
    }

    if (user->isLocked()) {
        qDebug() << "用户已被锁定:" << cleanInput;
        QMessageBox::warning(nullptr, "登录失败", "该账号已被锁定，请联系管理员");
        return false;
    }


    qDebug() << "找到用户对象:";
    qDebug() << "  用户ID:" << QString::fromStdString(user->getUserId());
    qDebug() << "  用户名:" << QString::fromStdString(user->getUsername());
    qDebug() << "  存储密码:" << QString::fromStdString(user->getPassword());
    qDebug() << "  输入密码:" << cleanPassword;

    // 调试输出密码的每个字符
    QString storedPwd = QString::fromStdString(user->getPassword());
    qDebug() << "存储密码字符编码:";
    for (int i = 0; i < storedPwd.length(); ++i) {
        qDebug() << "  字符" << i << ":" << storedPwd.at(i).unicode() 
                 << "('" << storedPwd.at(i) << "')";
    }

    qDebug() << "输入密码字符编码:";
    for (int i = 0; i < cleanPassword.length(); ++i) {
        qDebug() << "  字符" << i << ":" << cleanPassword.at(i).unicode() 
                 << "('" << cleanPassword.at(i) << "')";
    }

    // 使用 User 类的 checkPassword 方法
    if (user->checkPassword(cleanPassword.toStdString())) {
        currentUser = user;
        emit userLoggedIn(user);
        qDebug() << "登录成功";
        return true;
    } else {
        qDebug() << "密码不匹配";
        return false;
    }
}

void TicketSystem::logout() {
    currentUser = nullptr;  // 先清空指针
    emit userLoggedOut();   // 然后发射信号
}

std::vector<Train> TicketSystem::queryTrains(int startStationId, int endStationId, const QString& date) {
    std::vector<Train> result;
    for (const auto& train : dbManager.getTrains()) {
        if (train.getStartStationId() == startStationId && train.getEndStationId() == endStationId) {
            result.push_back(train);
        }
    }
    return result;
}

std::vector<Train*> TicketSystem::searchTrains(const std::string& startStation,
    const std::string& endStation,
    const std::string& date) {
    std::vector<Train*> result;
    int startId = -1, endId = -1;

    // 获取车站ID
    for (const auto& station : dbManager.getStations()) {
        QString stationName = station.getName();
        if (stationName == QString::fromStdString(startStation))
            startId = station.getStationId();
        if (stationName == QString::fromStdString(endStation))
            endId = station.getStationId();
    }

    if (startId == -1 || endId == -1) {
        return result;
    }

    // 检查搜索日期
    QDate searchDate = QDate::fromString(QString::fromStdString(date), "yyyy-MM-dd");
    QDate currentDate = QDate::currentDate();

    // 不允许查询过去日期
    if (searchDate < currentDate) {
        QMessageBox::warning(nullptr, "错误", "不能查询过去日期的车票");
        return result;
    }

    // 使用列车时刻表来查找经过这两个站点的列车
    for (const auto& schedule1 : dbManager.getTrainSchedules()) {
        if (schedule1.getStationId() == startId) {
            for (const auto& schedule2 : dbManager.getTrainSchedules()) {
                if (schedule2.getTrainId() == schedule1.getTrainId() &&
                    schedule2.getStationId() == endId &&
                    schedule2.getStopOrder() > schedule1.getStopOrder()) {

                    // 找到匹配的列车
                    Train* train = dbManager.getTrainById(schedule1.getTrainId());
                    if (train) {
                        // 如果是当天，检查发车时间是否在当前时间之后
                        if (searchDate == currentDate) {
                            std::string departTimeStr = schedule1.getDepartTime();
                            QTime departTime = QTime::fromString(QString::fromStdString(departTimeStr), "HH:mm");
                            QTime currentTime = QTime::currentTime();

                            if (departTime > currentTime) {
                                result.push_back(train);
                            }
                        }
                        else {
                            // 未来日期，所有车次都显示
                            result.push_back(train);
                        }
                    }
                    break;
                }
            }
        }
    }

    return result;
}

int TicketSystem::getAvailableSeats(int trainId, const QString& date) {
    int totalSeats = 0;
    int bookedSeats = 0;

    for (const auto& seat : dbManager.getSeats()) {
        if (seat.getTrainId() == trainId) totalSeats++;
    }

    for (const auto& order : dbManager.getOrders()) {
        if (order.getTrainId() == trainId &&
            order.getTravelDate() == date.toStdString() &&
            order.getStatus() == "booked") {
            bookedSeats++;
        }
    }

    return totalSeats - bookedSeats;
}

bool TicketSystem::bookTicket(const std::string& userId, int trainId,
    const std::string& date, int startStationId, int endStationId)
{
    if (!currentUser) return false;

    // 使用QString进行转换
    QString qDate = QString::fromStdString(date);
    int available = getAvailableSeatsForTrain(trainId, date);
    if (available <= 0) return false;

    int maxOrderId = 0;
    for (const auto& order : dbManager.getOrders()) {
        if (order.getOrderId() > maxOrderId) {
            maxOrderId = order.getOrderId();
        }
    }
    int orderId = maxOrderId + 1;

    bool ok;
    int userIntId = StringHelper::toInt(QString::fromStdString(userId), &ok);
    if (!ok) return false;

    Order newOrder(
        orderId,
        userIntId,
        trainId,
        1,  // 默认座位ID，后续可以改进
        startStationId,  // 使用用户选择的出发站
        endStationId,    // 使用用户选择的到达站
        date,
        DateTimeHelper::formatDateTime(QDateTime::currentDateTime()).toStdString(),
        "booked"
    );

    dbManager.addOrder(newOrder);
    dbManager.saveOrders();
    undoManager.addAction(new AddOrderAction(newOrder));
    emit ordersUpdated();
    return true;
}

bool TicketSystem::cancelOrder(int orderId) {
    if (!currentUser) return false;

    Order* order = getOrderById(orderId);
    if (!order) return false;

    // 检查权限：用户只能取消自己的订单，管理员可以取消任何订单
    bool isAdmin = isAdminUser(currentUser->getUserId());
    bool isOwner = order->getUserId() == StringHelper::toInt(QString::fromStdString(currentUser->getUserId()));

    if (!isAdmin && !isOwner) {
        return false;
    }

    Order oldOrder = *order;
    order->setStatus("canceled");
    dbManager.saveOrders();
    undoManager.addAction(new ModifyOrderAction(oldOrder, *order));

    emit ordersUpdated();
    return true;
}

std::vector<Order> TicketSystem::getUserOrders(int userId) const {
    std::vector<Order> userOrders;
    for (const auto& order : dbManager.getOrders()) {
        if (order.getUserId() == userId) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}

std::vector<std::string> TicketSystem::getAllStations() const {
    std::vector<std::string> stationNames;
    for (const auto& station : dbManager.getStations()) {
        stationNames.push_back(station.getName().toStdString());
    }
    return stationNames;
}

std::vector<const Train*> TicketSystem::getAllTrains() const {
    std::vector<const Train*> trains;
    for (const auto& train : dbManager.getTrains()) {
        trains.push_back(&train);
    }
    return trains;
}

std::vector<User*> TicketSystem::getAllUsers() const {
    std::vector<User*> userPtrs;
    for (auto& user : dbManager.getUsers()) {
        userPtrs.push_back(const_cast<User*>(&user));
    }
    return userPtrs;
}

std::vector<TrainSchedule> TicketSystem::getTrainSchedules() const {
    return dbManager.getTrainSchedules();
}

bool TicketSystem::addTrain(const std::string& trainCode, const std::string& type,
    int startStationId, int endStationId) {
    if (!currentUser || !isAdminUser(currentUser->getUserId())) {
        QMessageBox::warning(nullptr, "权限不足", "需要管理员权限才能添加列车");
        return false;
    }

    // 生成新的列车ID
    int maxId = 0;
    for (const auto& train : dbManager.getTrains()) {
        if (train.getTrainId() > maxId) {
            maxId = train.getTrainId();
        }
    }
    int newTrainId = maxId + 1;

    // 创建新列车
    Train newTrain(newTrainId, trainCode, type, startStationId, endStationId);

    // 添加到数据库
    dbManager.addTrain(newTrain);

    // 保存到文件
    if (dbManager.saveTrains()) {
        QMessageBox::information(nullptr, "成功", "列车添加成功");
        emit trainsUpdated(); // 发送信号通知列车数据更新
        return true;
    }
    else {
        QMessageBox::warning(nullptr, "失败", "列车添加失败");
        return false;
    }
}

bool TicketSystem::addUser() {
    return true;
}

bool TicketSystem::editUser(const std::string& userId, const std::string& newUsername, const std::string& newPhone, const std::string& newPassword, const std::string& newRole) {
    User* user = dbManager.getUserById(userId);
    if (!user) return false;

    // 检查用户名是否已被其他人使用（如果修改了用户名）
    if (newUsername != user->getUsername()) {
        if (!isUsernameAvailable(newUsername)) {
            return false;
        }
    }

    // 保存旧状态
    User oldUser = *user;

    // 更新用户信息
    if (!newUsername.empty()) user->setUsername(newUsername);
    if (!newPhone.empty()) user->setPhone(newPhone);
    if (!newPassword.empty()) user->setPassword(newPassword);
    if (!newRole.empty()) user->setRole(newRole);

    // 保存到数据库
    if (dbManager.saveUsers()) {
        return true;
    }
    return false;
}

bool TicketSystem::deleteUser(const std::string& userId) {
    // 检查当前用户是否有权限删除该账号
    if (currentUser &&
        (currentUser->getUserId() == userId || isAdminUser(currentUser->getUserId()))) {

        auto& users = const_cast<std::vector<User>&>(dbManager.getUsers());
        auto it = std::find_if(users.begin(), users.end(),
            [&](const User& u) { return u.getUserId() == userId; });

        if (it == users.end()) return false;

        // 删除用户
        users.erase(it);

        // 如果是当前用户自己注销，则退出登录
        if (currentUser->getUserId() == userId) {
            logout();
        }

        // 保存到数据库
        return dbManager.saveUsers();
    }
    return false;
}

bool TicketSystem::undo() {
    bool result = undoManager.undo();
    if (result) emit ordersUpdated();
    return result;
}

bool TicketSystem::redo() {
    bool result = undoManager.redo();
    if (result) emit ordersUpdated();
    return result;
}

User* TicketSystem::getCurrentUser() const {
    return currentUser;
}

const std::vector<Station>& TicketSystem::getStations() const {
    return dbManager.getStations();
}

const std::vector<Seat>& TicketSystem::getSeats() const {
    return dbManager.getSeats();
}

const std::vector<Order>& TicketSystem::getOrders() const {
    return dbManager.getOrders();
}

// 获取车站名称
QString TicketSystem::getStationNameById(int stationId) const {
    for (const auto& station : dbManager.getStations()) {
        if (station.getStationId() == stationId) {
            return station.getName();
        }
    }
    return "未知车站 (" + QString::number(stationId) + ")";
}

// 获取列车出发时间
std::string TicketSystem::getDepartureTimeForTrain(int trainId) const {
    int minStopOrder = INT_MAX;
    std::string departureTime = "未知";

    for (const auto& schedule : dbManager.getTrainSchedules()) {
        if (schedule.getTrainId() == trainId &&
            schedule.getStopOrder() < minStopOrder) {
            minStopOrder = schedule.getStopOrder();
            departureTime = schedule.getDepartTime();
        }
    }
    return departureTime;
}

std::string TicketSystem::getArrivalTimeForTrain(int trainId) const {
    int maxStopOrder = 0;
    std::string arrivalTime = "未知";

    for (const auto& schedule : dbManager.getTrainSchedules()) {
        if (schedule.getTrainId() == trainId &&
            schedule.getStopOrder() > maxStopOrder) {
            maxStopOrder = schedule.getStopOrder();
            arrivalTime = schedule.getArriveTime();
        }
    }
    return arrivalTime;
}

int TicketSystem::getAvailableSeatsForTrain(int trainId, const std::string& date) const {
    int totalSeats = 0;
    int bookedSeats = 0;

    // 计算总座位数
    for (const auto& seat : dbManager.getSeats()) {
        if (seat.getTrainId() == trainId) {
            totalSeats++;
        }
    }

    // 计算已预订座位数
    for (const auto& order : dbManager.getOrders()) {
        if (order.getTrainId() == trainId &&
            order.getTravelDate() == date &&
            order.getStatus() == "booked") {
            bookedSeats++;
        }
    }

    return totalSeats - bookedSeats;
}

Train* TicketSystem::getTrainById(int trainId) {
    return dbManager.getTrainById(trainId);
}

std::vector<Order> TicketSystem::getUserOrdersWithDetails(const std::string& userId) {
    std::vector<Order> userOrders;

    // 检查是否是管理员 (user_id = 0)
    bool isAdmin = false;
    int targetUserId = -1;

    // 转换输入的用户ID为整数
    bool ok;
    targetUserId = StringHelper::toInt(QString::fromStdString(userId), &ok);

    if (ok && targetUserId == 0) {
        isAdmin = true;
        qDebug() << "管理员登录，显示所有订单";
    }

    // 获取所有订单
    auto allOrders = dbManager.getOrders();
    qDebug() << "数据库中的订单总数:" << allOrders.size();

    if (isAdmin) {
        // 管理员：返回所有订单
        userOrders = allOrders;
        qDebug() << "管理员获取所有订单，数量:" << userOrders.size();
    }
    else {
        // 普通用户：只返回自己的订单
        for (const auto& order : allOrders) {
            if (order.getUserId() == targetUserId) {
                userOrders.push_back(order);
            }
        }
        qDebug() << "用户" << targetUserId << "的订单数量:" << userOrders.size();
    }

    return userOrders;
}

std::string TicketSystem::getTrainCodeByOrder(const Order& order)  {
    Train* train = dbManager.getTrainById(order.getTrainId());
    return train ? train->getTrainCode() : "未知车次"; // 匹配trains.txt的train_code
}

std::pair<std::string, std::string> TicketSystem::getOrderTimeByOrder(const Order& order) {
    std::string departTime = "未知";
    std::string arriveTime = "未知";
    int minStop = INT_MAX;
    int maxStop = 0;

    // 遍历train_schedules.txt，匹配当前列车的最小/最大stop_order（对应出发/到达站）
    for (const auto& schedule : dbManager.getTrainSchedules()) {
        if (schedule.getTrainId() == order.getTrainId()) {
            // 出发时间：stop_order最小的站点的depart_time
            if (schedule.getStopOrder() < minStop) {
                minStop = schedule.getStopOrder();
                departTime = schedule.getDepartTime();
            }
            // 到达时间：stop_order最大的站点的arrive_time
            if (schedule.getStopOrder() > maxStop) {
                maxStop = schedule.getStopOrder();
                arriveTime = schedule.getArriveTime();
            }
        }
    }
    return { departTime, arriveTime };
}

Order* TicketSystem::getOrderById(int orderId) {
    auto& orders = const_cast<std::vector<Order>&>(dbManager.getOrders());
    for (auto& order : orders) {
        if (order.getOrderId() == orderId) {
            return &order;
        }
    }
    return nullptr;
}

bool TicketSystem::changeOrder(int orderId, int newTrainId, const std::string& newDate, int newSeatId) {
    if (!currentUser) return false;

    Order* order = getOrderById(orderId);
    if (!order) return false;

    // 检查权限：用户只能改签自己的订单，管理员可以改签任何订单
    bool isAdmin = isAdminUser(currentUser->getUserId());
    bool isOwner = order->getUserId() == StringHelper::toInt(QString::fromStdString(currentUser->getUserId()));

    if (!isAdmin && !isOwner) {
        QMessageBox::warning(nullptr, "权限不足", "无权改签此订单");
        return false;
    }

    // 检查新车次和日期是否有效
    Train* newTrain = getTrainById(newTrainId);
    if (!newTrain) {
        QMessageBox::warning(nullptr, "错误", "无效的车次");
        return false;
    }

    if (!DateTimeHelper::isValidDate(QString::fromStdString(newDate))) {
        QMessageBox::warning(nullptr, "错误", "无效的日期");
        return false;
    }

    // 检查是否改签到过去时间
    QDate newOrderDate = QDate::fromString(QString::fromStdString(newDate), "yyyy-MM-dd");
    QDate currentDate = QDate::currentDate();

    if (newOrderDate < currentDate) {
        QMessageBox::warning(nullptr, "错误", "不能改签到过去日期");
        return false;
    }

    // 如果是当天，检查发车时间是否已过
    if (newOrderDate == currentDate) {
        // 获取新车次在用户原出发站的发车时间
        std::string departTimeStr = getDepartureTimeAtStation(newTrainId, order->getStartStationId());
        if (departTimeStr != "未知") {
            QTime departTime = QTime::fromString(QString::fromStdString(departTimeStr), "HH:mm");
            QTime currentTime = QTime::currentTime();

            if (departTime < currentTime) {
                QMessageBox::warning(nullptr, "错误", "该车次今天已发车，不能改签");
                return false;
            }
        }
    }

    // 检查新车次是否经过用户选择的站点
    if (!isTrainPassThroughStations(newTrainId, order->getStartStationId(), order->getEndStationId())) {
        QMessageBox::warning(nullptr, "错误", "新车次不经过您选择的站点");
        return false;
    }

    // 检查新车次在用户选择站点区间是否有余票
    int availableSeats = getAvailableSeatsForTrainSection(newTrainId, newDate,
        order->getStartStationId(), order->getEndStationId());
    if (availableSeats <= 0) {
        QMessageBox::warning(nullptr, "错误", "该列车在您选择的区间已无余票");
        return false;
    }

    // 保存旧订单状态（用于撤销）
    Order oldOrder = *order;
    int oldTrainId = order->getTrainId();
    std::string oldDate = order->getTravelDate();
    int oldSeatId = order->getSeatId();

    // 分配新座位
    int assignedSeatId = findAvailableSeatForSection(newTrainId, newDate,
        order->getStartStationId(), order->getEndStationId());
    if (assignedSeatId == -1) {
        QMessageBox::warning(nullptr, "错误", "无法分配座位");
        return false;
    }

    // 更新订单信息 - 保持原出发站和到达站不变！
    order->setTrainId(newTrainId);
    order->setTravelDate(newDate);
    order->setSeatId(assignedSeatId);
    // 注意：不修改 startStationId 和 endStationId，保持用户原选择
    order->setStatus("changed");
    order->setOrderTime(DateTimeHelper::formatDateTime(QDateTime::currentDateTime()).toStdString());

    // 这里座位自动释放：原订单状态改为changed后，原座位自然可用
    // 因为查询余票时只考虑status为"booked"的订单

    // 保存更改
    dbManager.saveOrders();
    undoManager.addAction(new ModifyOrderAction(oldOrder, *order));
    emit ordersUpdated();

    // 显示改签详情
    QString message = QString("改签成功！\n"
        "原车次：%1，座位：%2，日期：%3\n"
        "新车次：%4，座位：%5，日期：%6\n"
        "出发站：%7，到达站：%8")
        .arg(oldTrainId)
        .arg(oldSeatId)
        .arg(QString::fromStdString(oldDate))
        .arg(newTrainId)
        .arg(assignedSeatId)
        .arg(QString::fromStdString(newDate))
        .arg(getStationNameById(order->getStartStationId()))
        .arg(getStationNameById(order->getEndStationId()));

    QMessageBox::information(nullptr, "成功", message);
    return true;
}
bool TicketSystem::registerUser(const std::string& username, const std::string& password,const std::string& displayName, const std::string& phone, const std::string& idCard, const std::string& role) {

    qDebug() << "开始注册用户:" << username.c_str();

    // 检查用户名是否已存在
    auto users = dbManager.getUsers();
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            qDebug() << "用户名已存在:" << username.c_str();
            return false;
        }
    }

    // 生成用户ID（自动递增）
    int maxId = 0;
    for (const auto& user : users) {
        bool ok;
        int userId = QString::fromStdString(user.getUserId()).toInt(&ok);
        if (ok && userId > maxId) {
            maxId = userId;
        }
    }
    int newUserId = maxId + 1;

    qDebug() << "生成新用户ID:" << newUserId;

    // 创建新用户
    User newUser(
        QString::number(newUserId).toStdString(),
        username,
        displayName,
        password,
        phone,
        role, // 使用传入的角色
        idCard
    );

    // 添加到数据库
    dbManager.addUser(newUser);

    // 保存到文件
    if (dbManager.saveUsers()) {
        qDebug() << "用户注册成功，ID:" << newUserId << "用户名:" << username.c_str() << "角色:" << role.c_str();

        // 调试输出所有用户确认数据已保存
        auto updatedUsers = dbManager.getUsers();
        qDebug() << "当前用户数量:" << updatedUsers.size();
        for (const auto& user : updatedUsers) {
            qDebug() << "用户:" << user.getUserId().c_str() << user.getUsername().c_str()
                << user.getRole().c_str();
        }

        return true;
    }

    qDebug() << "保存用户数据失败";
    return false;
}

bool TicketSystem::isUsernameAvailable(const std::string& username) {
    auto users = dbManager.getUsers();
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            return false; // 用户名已存在
        }
    }
    return true; // 用户名可用
}

int TicketSystem::generateNextUserId() {
    auto users = dbManager.getUsers();
    int maxId = 0;

    for (const auto& user : users) {
        bool ok;
        int userId = QString::fromStdString(user.getUserId()).toInt(&ok);
        if (ok && userId > maxId) {
            maxId = userId;
        }
    }

    return maxId + 1; // 返回下一个可用的ID
}

bool TicketSystem::isAdminUser(const std::string& userId) {
    User* user = dbManager.getUserById(userId);
    return user && user->getRole() == "admin";
}

User* TicketSystem::getUserById(const std::string& userId) {
    return dbManager.getUserById(userId);
}

bool TicketSystem::saveUsers() {
    return dbManager.saveUsers();
}

bool TicketSystem::updateUserInfo(const std::string& username, const std::string& phone, const std::string& password)
{
    if (!currentUser) {
        return false;
    }
    return editUser(currentUser->getUserId(), username, phone, password, currentUser->getRole());
}

bool TicketSystem::saveUsersToFile()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);

    for (const auto& user : m_users) {
        // 确保字段顺序正确：用户名,密码,用户类型,身份证,手机号
        out << QString::fromStdString(user.getUsername()) << ","
            << QString::fromStdString(user.getPassword()) << ","
            << QString::fromStdString(user.getRole()) << ","
            << QString::fromStdString(user.getUserId()) << ","
            << QString::fromStdString(user.getPhone()) << "\n";
    }

    file.close();
    return true;
}

bool TicketSystem::addTrainWithSchedulesAndSeats(
    const std::string& trainCode,
    const std::string& type,
    int startStationId,
    int endStationId,
    QTableWidget* scheduleTable,
    int businessSeats,
    int firstClassSeats,
    int secondClassSeats)
{
    if (!currentUser || !isAdminUser(currentUser->getUserId())) {
        QMessageBox::warning(nullptr, "权限不足", "需要管理员权限才能添加列车");
        return false;
    }

    // 生成列车ID
    int maxTrainId = 0;
    std::vector<Train> trains = dbManager.getTrains();
    for (const Train& train : trains) {
        if (train.getTrainId() > maxTrainId) maxTrainId = train.getTrainId();
    }
    int newTrainId = maxTrainId + 1;

    qDebug() << "添加新列车 - ID:" << newTrainId << "车次:" << trainCode.c_str() << "类型:" << type.c_str();

    // 1. 添加列车到 trains.txt
    Train newTrain(newTrainId, trainCode, type, startStationId, endStationId);
    if (!dbManager.addTrain(newTrain)) {
        QMessageBox::warning(nullptr, "错误", "添加列车到数据库失败");
        return false;
    }

    // 2. 添加经停站到 train_schedules.txt
    int maxScheduleId = 0;
    std::vector<TrainSchedule> schedules = dbManager.getTrainSchedules();
    for (const TrainSchedule& schedule : schedules) {
        if (schedule.getScheduleId() > maxScheduleId) maxScheduleId = schedule.getScheduleId();
    }

    // 确保包含起始站和终点站
    bool hasStartStation = false;
    bool hasEndStation = false;

    for (int row = 0; row < scheduleTable->rowCount(); ++row) {
        QComboBox* stationCombo = qobject_cast<QComboBox*>(scheduleTable->cellWidget(row, 0));
        QTimeEdit* arriveTime = qobject_cast<QTimeEdit*>(scheduleTable->cellWidget(row, 1));
        QTimeEdit* departTime = qobject_cast<QTimeEdit*>(scheduleTable->cellWidget(row, 2));

        if (!stationCombo || !arriveTime || !departTime) continue;

        QString stationName = stationCombo->currentText();
        int stationId = -1;
        std::vector<Station> stations = dbManager.getStations();
        for (const Station& station : stations) {
            if (station.getName() == stationName) {
                stationId = station.getStationId();
                break;
            }
        }
        if (stationId == -1) continue;

        // 检查是否为起始站或终点站
        if (stationId == startStationId) hasStartStation = true;
        if (stationId == endStationId) hasEndStation = true;

        TrainSchedule newSchedule(
            ++maxScheduleId,
            newTrainId,
            stationId,
            row + 1, // stopOrder
            arriveTime->time().toString("HH:mm").toStdString(),
            departTime->time().toString("HH:mm").toStdString()
        );
        dbManager.addTrainSchedule(newSchedule);
    }

    // 如果没有包含起始站或终点站，自动添加
    if (!hasStartStation) {
        TrainSchedule startSchedule(
            ++maxScheduleId,
            newTrainId,
            startStationId,
            1, // 第一个站
            "始发站",
            "08:00" // 默认发车时间
        );
        dbManager.addTrainSchedule(startSchedule);
    }

    if (!hasEndStation) {
        TrainSchedule endSchedule(
            ++maxScheduleId,
            newTrainId,
            endStationId,
            scheduleTable->rowCount() + 2, // 最后一个站
            "18:00", // 默认到达时间
            "终点站"
        );
        dbManager.addTrainSchedule(endSchedule);
    }

    // 3. 添加座位到 seats.txt
    int maxSeatId = 0;
    std::vector<Seat> seats = dbManager.getSeats();
    for (const Seat& seat : seats) {
        if (seat.getSeatId() > maxSeatId) maxSeatId = seat.getSeatId();
    }

    // 添加商务座 (A)
    for (int i = 1; i <= businessSeats; ++i) {
        Seat newSeat(++maxSeatId, newTrainId, (QString::number(i) + "A").toStdString(), "商务");
        dbManager.addSeat(newSeat);
    }

    // 添加一等座 (B)
    for (int i = 1; i <= firstClassSeats; ++i) {
        Seat newSeat(++maxSeatId, newTrainId, (QString::number(i) + "B").toStdString(), "一等");
        dbManager.addSeat(newSeat);
    }

    // 添加二等座 (C)
    for (int i = 1; i <= secondClassSeats; ++i) {
        Seat newSeat(++maxSeatId, newTrainId, (QString::number(i) + "C").toStdString(), "二等");
        dbManager.addSeat(newSeat);
    }

    // 保存所有文件
    bool success = dbManager.saveTrains() &&
        dbManager.saveTrainSchedules() &&
        dbManager.saveSeats();

    if (success) {
        QMessageBox::information(nullptr, "成功",
            QString("列车添加成功！\n车次: %1\nID: %2\n商务座: %3\n一等座: %4\n二等座: %5")
            .arg(QString::fromStdString(trainCode))
            .arg(newTrainId)
            .arg(businessSeats)
            .arg(firstClassSeats)
            .arg(secondClassSeats));
        emit trainsUpdated();
    }
    else {
        QMessageBox::warning(nullptr, "失败", "列车添加失败，请检查数据文件");
    }

    return success;
}

bool TicketSystem::deleteTrain(int trainId) {
    if (!currentUser || !isAdminUser(currentUser->getUserId())) {
        QMessageBox::warning(nullptr, "权限不足", "需要管理员权限才能删除列车");
        return false;
    }

    // 检查列车是否存在
    Train* train = dbManager.getTrainById(trainId);
    if (!train) {
        QMessageBox::warning(nullptr, "错误", "未找到指定的列车");
        return false;
    }

    // 检查是否有未完成的订单关联到此列车
    for (const auto& order : dbManager.getOrders()) {
        if (order.getTrainId() == trainId && order.getStatus() == "booked") {
            QMessageBox::warning(nullptr, "错误",
                "该列车有未完成的订单，无法删除");
            return false;
        }
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "确认删除",
        QString("确定要删除列车 %1 吗？此操作不可撤销！").arg(trainId),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 从内存中删除相关数据
        auto& trains = const_cast<std::vector<Train>&>(dbManager.getTrains());
        auto& seats = const_cast<std::vector<Seat>&>(dbManager.getSeats());
        auto& schedules = const_cast<std::vector<TrainSchedule>&>(dbManager.getTrainSchedules());

        // 删除列车
        trains.erase(std::remove_if(trains.begin(), trains.end(),
            [trainId](const Train& train) { return train.getTrainId() == trainId; }),
            trains.end());

        // 删除座位
        seats.erase(std::remove_if(seats.begin(), seats.end(),
            [trainId](const Seat& seat) { return seat.getTrainId() == trainId; }),
            seats.end());

        // 删除时刻表
        schedules.erase(std::remove_if(schedules.begin(), schedules.end(),
            [trainId](const TrainSchedule& schedule) { return schedule.getTrainId() == trainId; }),
            schedules.end());

        // 保存所有更改
        bool success = dbManager.saveTrains() &&
            dbManager.saveSeats() &&
            dbManager.saveTrainSchedules();

        if (success) {
            QMessageBox::information(nullptr, "成功", "列车及相关数据删除成功");
            emit trainsUpdated();
            return true;
        }
    }

    return false;
}


bool TicketSystem::editTrain(int trainId, const std::string& trainCode,
    const std::string& type, int startStationId,
    int endStationId,
    const std::vector<TrainSchedule>& newSchedules,
    const std::vector<Seat>& newSeats) {

    if (!currentUser || !isAdminUser(currentUser->getUserId())) {
        QMessageBox::warning(nullptr, "权限不足", "需要管理员权限才能编辑列车");
        return false;
    }

    // 1. 更新列车信息
    Train* train = dbManager.getTrainById(trainId);
    if (train) {
        
        Train oldTrain = *train;

        // 更新列车信息
        train->setTrainCode(trainCode);
        train->setType(type);
        train->setStartStationId(startStationId);
        train->setEndStationId(endStationId);
    }

    // 2. 更新座位信息 - 先删除旧的，再添加新的
    auto& seats = const_cast<std::vector<Seat>&>(dbManager.getSeats());
    // 移除该列车的所有座位
    seats.erase(std::remove_if(seats.begin(), seats.end(),
        [trainId](const Seat& seat) { return seat.getTrainId() == trainId; }),
        seats.end());

    // 添加新座位
    for (const auto& seat : newSeats) {
        seats.push_back(seat);
    }

    // 3. 更新时刻表信息 - 先删除旧的，再添加新的
    auto& schedules = const_cast<std::vector<TrainSchedule>&>(dbManager.getTrainSchedules());
    // 移除该列车的所有时刻表
    schedules.erase(std::remove_if(schedules.begin(), schedules.end(),
        [trainId](const TrainSchedule& schedule) { return schedule.getTrainId() == trainId; }),
        schedules.end());

    // 添加新时刻表
    for (const auto& schedule : newSchedules) {
        schedules.push_back(schedule);
    }

    // 4. 保存所有更改
    bool success = dbManager.saveTrains() &&
        dbManager.saveSeats() &&
        dbManager.saveTrainSchedules();

    if (success) {
        QMessageBox::information(nullptr, "成功", "列车信息更新成功");
        emit trainsUpdated();
    }
    else {
        QMessageBox::warning(nullptr, "失败", "列车信息更新失败");
    }

    return success;
}

bool TicketSystem::removeLinesWithId(const QString& filePath, int id, int idColumn) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return false;
    }

    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.trimmed().split(QRegularExpression("\\s+"));
        if (parts.size() > idColumn) {
            bool ok;
            int lineId = parts[idColumn].toInt(&ok);
            if (ok && lineId == id) {
                continue; // 跳过要删除的行
            }
        }
        lines.append(line);
    }

    file.resize(0);
    QTextStream out(&file);
    for (const QString& line : lines) {
        out << line << "\n";
    }

    file.close();
    return true;
}

bool TicketSystem::replaceInFile(const QString& filePath, const QString& oldContent, const QString& newContent) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return false;
    }

    QString content = file.readAll();
    content.replace(oldContent, newContent);

    file.resize(0); // 清空文件
    file.write(content.toUtf8());
    file.close();

    return true;
}

bool TicketSystem::isTrainAvailableToday(int trainId, int startStationId) const {
    // 获取当前时间
    QTime currentTime = QTime::currentTime();

    // 查找该列车在起始站的发车时间
    for (const auto& schedule : dbManager.getTrainSchedules()) {
        if (schedule.getTrainId() == trainId &&
            schedule.getStationId() == startStationId) {

            std::string departTimeStr = schedule.getDepartTime();
            QTime departTime = QTime::fromString(QString::fromStdString(departTimeStr), "HH:mm");

            if (departTime.isValid()) {
                return departTime > currentTime;
            }
        }
    }

    return false; // 找不到时刻表信息，默认不可用
}

QDateTime TicketSystem::getOrderDepartureDateTime(const Order& order) const
{
    // 获取出发时间字符串
    std::string departTimeStr = getDepartureTimeForTrain(order.getTrainId());

    // 组合日期和时间
    QString dateTimeStr = QString::fromStdString(order.getTravelDate()) + " " +
        QString::fromStdString(departTimeStr);

    return QDateTime::fromString(dateTimeStr, "yyyy-MM-dd HH:mm");
}

bool TicketSystem::addStation(const std::string& stationName)
{
    // 获取最大的车站ID
    int maxId = 0;
    for (const auto& station : dbManager.getStations()) {
        if (station.getStationId() > maxId) {
            maxId = station.getStationId();
        }
    }

    // 创建新车站
    Station newStation(maxId + 1, QString::fromStdString(stationName));
    dbManager.addStation(newStation);

    // 保存到文件
    return dbManager.saveStations();
}

bool TicketSystem::deleteStation(const std::string& stationName)
{
    // 检查是否有列车使用这个车站
    for (const auto& train : dbManager.getTrains()) {
        QString stationQName = QString::fromStdString(stationName);
        if (getStationNameById(train.getStartStationId()) == stationQName ||
            getStationNameById(train.getEndStationId()) == stationQName) {
            return false; // 有列车使用此车站，不能删除
        }
    }

    // 检查时刻表中是否使用这个车站
    for (const auto& schedule : dbManager.getTrainSchedules()) {
        if (getStationNameById(schedule.getStationId()) == QString::fromStdString(stationName)) {
            return false; // 有时刻表使用此车站，不能删除
        }
    }

    // 从数据库中删除车站
    auto& stations = const_cast<std::vector<Station>&>(dbManager.getStations());
    for (auto it = stations.begin(); it != stations.end(); ) {
        if (it->getName() == QString::fromStdString(stationName)) {
            it = stations.erase(it);
            break;
        }
        else {
            ++it;
        }
    }

    // 保存到文件
    return dbManager.saveStations();
}

int TicketSystem::findAvailableSeat(int trainId, const std::string& date) {
    const auto& allSeats = getSeats();
    for (const auto& seat : allSeats) {
        if (seat.getTrainId() == trainId) {
            // 检查座位是否被占用
            bool isOccupied = false;
            for (const auto& order : getOrders()) {
                if (order.getTrainId() == trainId &&
                    order.getSeatId() == seat.getSeatId() &&
                    order.getTravelDate() == date &&
                    order.getStatus() == "booked") {
                    isOccupied = true;
                    break;
                }
            }
            if (!isOccupied) {
                return seat.getSeatId();
            }
        }
    }
    return -1;
}

// 检查列车是否经过指定站点
bool TicketSystem::isTrainPassThroughStations(int trainId, int startStationId, int endStationId) {
    bool foundStart = false;
    bool foundEnd = false;
    int startOrder = -1;
    int endOrder = -1;

    const auto& schedules = dbManager.getTrainSchedules(); 
    for (const auto& schedule : schedules) {
        if (schedule.getTrainId() == trainId) {
            if (schedule.getStationId() == startStationId) {
                foundStart = true;
                startOrder = schedule.getStopOrder();
            }
            if (schedule.getStationId() == endStationId) {
                foundEnd = true;
                endOrder = schedule.getStopOrder();
            }
        }
    }

    return foundStart && foundEnd && startOrder < endOrder;
}

// 获取列车在指定站点的发车时间
std::string TicketSystem::getDepartureTimeAtStation(int trainId, int stationId) {
    const auto& schedules = dbManager.getTrainSchedules();  // 使用 dbManager
    for (const auto& schedule : schedules) {
        if (schedule.getTrainId() == trainId && schedule.getStationId() == stationId) {
            return schedule.getDepartTime();
        }
    }
    return "未知";
}
// 计算指定区间的余票
int TicketSystem::getAvailableSeatsForTrainSection(int trainId, const std::string& date,
    int startStationId, int endStationId) {
    int totalSeats = 0;
    int bookedSeats = 0;

    // 计算总座位数
    const auto& seats = dbManager.getSeats();  // 使用 dbManager
    for (const auto& seat : seats) {
        if (seat.getTrainId() == trainId) {
            totalSeats++;
        }
    }

    // 计算已预订座位数
    const auto& orders = dbManager.getOrders();  // 使用 dbManager
    for (const auto& order : orders) {
        if (order.getTrainId() == trainId &&
            order.getTravelDate() == date &&
            order.getStatus() == "booked") {

            if (isOrderAffectingSection(order, startStationId, endStationId)) {
                bookedSeats++;
            }
        }
    }

    return totalSeats - bookedSeats;
}

// 检查订单是否影响指定区间
int TicketSystem::findAvailableSeatForSection(int trainId, const std::string& date,
    int startStationId, int endStationId) {
    const auto& allSeats = dbManager.getSeats();  // 使用 dbManager

    for (const auto& seat : allSeats) {
        if (seat.getTrainId() == trainId) {
            bool isOccupied = false;
            const auto& orders = dbManager.getOrders();  // 使用 dbManager
            for (const auto& order : orders) {
                if (order.getTrainId() == trainId &&
                    order.getSeatId() == seat.getSeatId() &&
                    order.getTravelDate() == date &&
                    order.getStatus() == "booked" &&
                    isOrderAffectingSection(order, startStationId, endStationId)) {
                    isOccupied = true;
                    break;
                }
            }
            if (!isOccupied) {
                return seat.getSeatId();
            }
        }
    }
    return -1;
}

bool TicketSystem::isOrderAffectingSection(const Order& order, int targetStartId, int targetEndId) {
    int orderStartOrder = -1;
    int orderEndOrder = -1;
    int targetStartOrder = -1;
    int targetEndOrder = -1;

    const auto& schedules = dbManager.getTrainSchedules();  // 使用 dbManager
    for (const auto& schedule : schedules) {
        if (schedule.getTrainId() == order.getTrainId()) {
            if (schedule.getStationId() == order.getStartStationId()) {
                orderStartOrder = schedule.getStopOrder();
            }
            if (schedule.getStationId() == order.getEndStationId()) {
                orderEndOrder = schedule.getStopOrder();
            }
            if (schedule.getStationId() == targetStartId) {
                targetStartOrder = schedule.getStopOrder();
            }
            if (schedule.getStationId() == targetEndId) {
                targetEndOrder = schedule.getStopOrder();
            }
        }
    }

    return !(orderEndOrder <= targetStartOrder || orderStartOrder >= targetEndOrder);
}