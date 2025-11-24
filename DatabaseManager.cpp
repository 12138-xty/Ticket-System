#include "DatabaseManager.h"
#include <QCoreApplication>
#include <QDebug>
#include <sstream>
#include <algorithm>
#include <QDir>
#include <QTextStream>
#include <QStringConverter>

using namespace std;

// 构造函数
DatabaseManager::DatabaseManager(const QString& dataDir)
    : m_dataDir(dataDir) {
    if (dataDir.isEmpty()) {
        // 如果没有指定路径，使用应用程序目录下的data文件夹
        this->dataDir = "D:/TicketSystem/Ticketsystem/data";
    }
    else {
        this->dataDir = dataDir;
    }
    qDebug() << "Data directory set to:" << this->dataDir;
}

// 创建数据目录
bool DatabaseManager::createDataDir() {
    QDir dir(dataDir);
    qDebug() << "Creating data directory:" << dataDir;

    if (!dir.exists()) {
        bool success = dir.mkpath(".");
        if (success) {
            qDebug() << "Data directory created successfully";
        }
        else {
            qDebug() << "Failed to create data directory:" << dataDir;
            // 尝试创建相对路径的data目录作为备选
            QString relativePath = QCoreApplication::applicationDirPath() + "/data";
            if (relativePath != dataDir) {
                qDebug() << "Trying relative path:" << relativePath;
                dataDir = relativePath;
                QDir relDir(relativePath);
                if (!relDir.exists()) {
                    return relDir.mkpath(".");
                }
                return true;
            }
        }
        return success;
    }
    return true;
}

// 初始化数据库
bool DatabaseManager::init() {
    qDebug() << "Initializing database with directory:" << dataDir;

    if (!createDataDir()) {
        qDebug() << "Failed to create data directory:" << dataDir;
        return false;
    }

    // 检查并创建必要的文件
    checkAndCreateNecessaryFiles();

    // 依次加载所有数据
    bool success = true;
    success &= loadUsers();
    success &= loadTrains();
    success &= loadOrders();
    success &= loadSeats();
    success &= loadStations();
    success &= loadTrainSchedules();

    return true;
}

void DatabaseManager::setUTF8Encoding(QTextStream& stream) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    stream.setEncoding(QStringConverter::Utf8);
#else
    // Qt5中使用setCodec，如果可用的话
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    stream.setCodec("UTF-8");
#else
    stream.setAutoDetectUnicode(true);
#endif
#endif
}

bool DatabaseManager::loadUsers() {
    QString filePath = dataDir + "/users.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开用户文件:" << filePath;
        return true;
    }

    users.clear();
    QTextStream in(&file);
    setUTF8Encoding(in);

    // 跳过BOM头（如果有）
    QString firstLine = in.readLine();
    if (!firstLine.startsWith("\uFEFF")) {
        // 如果不是BOM开头，重新处理第一行
        in.seek(0);
    }
    else {
        // 如果是BOM开头，从第二行开始读取
        firstLine = firstLine.mid(1); // 移除BOM字符
        if (!firstLine.trimmed().isEmpty()) {
            processUserLine(firstLine);
        }
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty() || line.trimmed().isEmpty()) continue;
        processUserLine(line);
    }

    file.close();
    qDebug() << "从" << filePath << "加载了" << users.size() << "个用户";

    return true;
}

bool DatabaseManager::saveUsers() {
    QString filePath = dataDir + "/users.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open user file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    setUTF8Encoding(out);

    // 写入UTF-8 BOM头
    out << "\uFEFF";

    // 按照固定宽度格式写入，确保对齐
    for (const auto& user : users) {
        out << QString("%1").arg(QString::fromStdString(user.getUserId()), 10, QChar(' ')) << "\t"
            << QString("%1").arg(QString::fromStdString(user.getUsername()), 15, QChar(' ')) << "\t"
            << QString("%1").arg(QString::fromStdString(user.getDisplayName()), 15, QChar(' ')) << "\t"
            << QString("%1").arg(QString::fromStdString(user.getPassword()), 15, QChar(' ')) << "\t"
            << QString("%1").arg(QString::fromStdString(user.getPhone()), 15, QChar(' ')) << "\t"
            << QString("%1").arg(QString::fromStdString(user.getRole()), 10, QChar(' ')) << "\t"
            << QString("%1").arg(QString::fromStdString(user.getIdCard()), 18, QChar(' ')) << "\n";
    }

    file.close();
    qDebug() << "Saved" << users.size() << "users to" << filePath;

    // 读取文件内容进行验证
    QFile readFile(filePath);
    if (readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&readFile);
        qDebug() << "文件内容:";
        while (!in.atEnd()) {
            qDebug() << in.readLine();
        }
        readFile.close();
    }

    return true;
}

// 加载列车数据（固定宽度文本格式）
bool DatabaseManager::loadTrains() {
    QString filePath = dataDir + "/trains.txt"; // 修改文件路径
    trains.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开列车文件:" << filePath;
        return false;
    }

    QTextStream in(&file);
    setUTF8Encoding(in);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // 解析CSV格式的列车数据
        QStringList parts = line.split(',');
        if (parts.size() >= 5) {
            try {
                int trainId = parts[0].trimmed().toInt();
                std::string trainCode = parts[1].trimmed().toStdString();
                std::string type = parts[2].trimmed().toStdString();
                int startStationId = parts[3].trimmed().toInt();
                int endStationId = parts[4].trimmed().toInt();

                trains.emplace_back(trainId, trainCode, type, startStationId, endStationId);
            }
            catch (...) {
                qDebug() << "Invalid train data format:" << line;
            }
        }
    }

    file.close();
    qDebug() << "Loaded" << trains.size() << "trains from" << filePath;
    return true;
}


// 保存列车数据（固定宽度文本格式）
bool DatabaseManager::saveTrains() {
    QString filePath = dataDir + "/trains.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open train file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    setUTF8Encoding(out);

    for (const auto& train : trains) {
        out << train.getTrainId() << ","
            << QString::fromStdString(train.getTrainCode()) << ","
            << QString::fromStdString(train.getType()) << ","
            << train.getStartStationId() << ","
            << train.getEndStationId() << "\n";
    }

    file.close();
    qDebug() << "Saved" << trains.size() << "trains to" << filePath;
    return true;
}
// 加载订单数据
bool DatabaseManager::loadOrders() {
    QString filePath = dataDir + "/orders.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开订单文件:" << filePath;
        return false;
    }

    orders.clear();
    QTextStream in(&file);
    setUTF8Encoding(in);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        try {
            // 调试输出原始行内容
            qDebug() << "原始订单行:" << line;

            // 使用空格分割而不是固定宽度，因为orders.txt格式是空格分隔的
            QStringList parts = line.split(' ', Qt::SkipEmptyParts);
            qDebug() << "分割后的部分:" << parts;

            if (parts.size() >= 9) {
                int orderId = parts[0].toInt();
                int userId = parts[1].toInt();
                int trainId = parts[2].toInt();
                int seatId = parts[3].toInt();
                int startStationId = parts[4].toInt();
                int endStationId = parts[5].toInt();

                // 日期和时间字段
                QString travelDate = parts[6].trimmed();
                QString orderTime = parts[7].trimmed() + " " + parts[8].trimmed(); // 合并日期和时间
                QString status = parts.size() > 9 ? parts[9].trimmed() : "booked";

                orders.emplace_back(orderId, userId, trainId, seatId,
                    startStationId, endStationId,
                    travelDate.toStdString(),
                    orderTime.toStdString(),
                    status.toStdString());

                qDebug() << "成功加载订单:" << orderId << "用户:" << userId << "列车:" << trainId
                    << "日期:" << travelDate << "状态:" << status;
            }
            else {
                qDebug() << "订单数据字段不足，期望至少9个字段，实际:" << parts.size();
            }
        }
        catch (const std::exception& e) {
            qDebug() << "订单数据格式错误:" << line << "错误:" << e.what();
        }
    }

    file.close();
    qDebug() << "从" << filePath << "加载了" << orders.size() << "个订单";
    return true;
}

// 保存订单数据
bool DatabaseManager::saveOrders() {
    QString filePath = dataDir + "/orders.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open order file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    setUTF8Encoding(out);

    for (const auto& order : orders) {
        out << QString("%1 ").arg(order.getOrderId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(order.getUserId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(order.getTrainId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(order.getSeatId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(order.getStartStationId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(order.getEndStationId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(QString::fromStdString(order.getTravelDate()), 10, QChar(' '))
            << QString("%1 ").arg(QString::fromStdString(order.getOrderTime()), 19, QChar(' '))
            << QString("%1 ").arg(QString::fromStdString(order.getStatus()), 10, QChar(' '))
            << "\n";
    }

    file.close();
    qDebug() << "Saved" << orders.size() << "orders to" << filePath;
    return true;
}

// 加载座位数据
bool DatabaseManager::loadSeats() {
    QString filePath = dataDir + "/seats.txt";
    seats.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开座位文件:" << filePath;
        return false;
    }

    QTextStream in(&file);
    setUTF8Encoding(in);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // 解析固定宽度的座位数据
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 4) {
            try {
                int seatId = parts[0].toInt();
                int trainId = parts[1].toInt();
                std::string seatNo = parts[2].trimmed().toStdString();
                std::string seatType = parts[3].trimmed().toStdString();

                seats.emplace_back(seatId, trainId, seatNo, seatType);
            }
            catch (...) {
                qDebug() << "Invalid seat data format:" << line;
            }
        }
    }

    file.close();
    qDebug() << "Loaded" << seats.size() << "seats from" << filePath;
    return true;
}

// 保存座位数据
bool DatabaseManager::saveSeats() {
    QString filePath = dataDir + "/seats.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open seat file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    setUTF8Encoding(out);

    for (const auto& seat : seats) {
        out << seat.getSeatId() << " "
            << seat.getTrainId() << " "
            << QString::fromStdString(seat.getSeatNo()) << " "
            << QString::fromStdString(seat.getSeatType()) << "\n";
    }

    file.close();
    qDebug() << "Saved" << seats.size() << "seats to" << filePath;
    return true;
}
// 加载车站数据
bool DatabaseManager::loadStations() {
    QString filePath = dataDir + "/stations.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open station file:" << filePath;
        return false;
    }

    stations.clear();
    QTextStream in(&file);
    setUTF8Encoding(in); // 设置UTF-8编码

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // 正确解析 CSV 格式
        QStringList parts = line.split(',');
        if (parts.size() >= 2) {
            try {
                int stationId = parts[0].trimmed().toInt();
                QString name = parts[1].trimmed();
                stations.emplace_back(stationId, name);
                qDebug() << "Loaded station:" << stationId << name;
            }
            catch (...) {
                qDebug() << "Invalid station data format:" << line;
            }
        }
    }

    file.close();
    qDebug() << "Loaded" << stations.size() << "stations from" << filePath;
    return true;
}

// 保存车站数据
bool DatabaseManager::saveStations() {
    QString filePath = dataDir + "/stations.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open station file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    setUTF8Encoding(out); // 设置UTF-8编码

    for (const auto& station : stations) {
        out << station.getStationId() << ","
            << station.getName() << "\n";
    }

    file.close();
    qDebug() << "Saved" << stations.size() << "stations to" << filePath;
    return true;
}

// 加载列车时刻表数据
bool DatabaseManager::loadTrainSchedules() {
    QString filePath = dataDir + "/train_schedules.txt";
    trainSchedules.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开时刻表文件:" << filePath;
        return false;
    }

    QTextStream in(&file);
    setUTF8Encoding(in);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // 解析固定宽度的时刻表数据
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 6) {
            try {
                int scheduleId = parts[0].toInt();
                int trainId = parts[1].toInt();
                int stationId = parts[2].toInt();
                int stopOrder = parts[3].toInt();
                std::string arriveTime = parts[4].trimmed().toStdString();
                std::string departTime = parts[5].trimmed().toStdString();

                trainSchedules.emplace_back(scheduleId, trainId, stationId, stopOrder, arriveTime, departTime);
            }
            catch (...) {
                qDebug() << "Invalid schedule data format:" << line;
            }
        }
    }

    file.close();
    qDebug() << "Loaded" << trainSchedules.size() << "schedules from" << filePath;
    return true;
}
// 保存列车时刻表数据
bool DatabaseManager::saveTrainSchedules() {
    QString filePath = dataDir + "/train_schedules.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open train schedule file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    setUTF8Encoding(out); // 设置UTF-8编码

    for (const auto& schedule : trainSchedules) {
        out << QString("%1 ").arg(schedule.getScheduleId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(schedule.getTrainId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(schedule.getStationId(), 10, 10, QChar(' '))
            << QString("%1 ").arg(schedule.getStopOrder(), 10, 10, QChar(' '))
            << QString("%1 ").arg(QString::fromStdString(schedule.getArriveTime()), 10, QChar(' '))
            << QString("%1 ").arg(QString::fromStdString(schedule.getDepartTime()), 10, QChar(' '))
            << "\n";
    }

    file.close();
    qDebug() << "Saved" << trainSchedules.size() << "train schedules to" << filePath;
    return true;
}

// 数据获取方法实现
const std::vector<User>& DatabaseManager::getUsers() const { return users; }
const std::vector<Train>& DatabaseManager::getTrains() const { return trains; }
const std::vector<Order>& DatabaseManager::getOrders() const { return orders; }
const std::vector<Seat>& DatabaseManager::getSeats() const { return seats; }
const std::vector<Station>& DatabaseManager::getStations() const { return stations; }
const std::vector<TrainSchedule>& DatabaseManager::getTrainSchedules() const { return trainSchedules; }

// 数据添加方法实现
void DatabaseManager::addUser(const User& user) { users.push_back(user); }
bool DatabaseManager::addTrain(const Train& train) {
    trains.push_back(train);
    return saveTrains();
}
void DatabaseManager::addOrder(const Order& order) { orders.push_back(order); }
void DatabaseManager::addSeat(const Seat& seat) { seats.push_back(seat); }
void DatabaseManager::addStation(const Station& station) { stations.push_back(station); }
void DatabaseManager::addTrainSchedule(const TrainSchedule& schedule) { trainSchedules.push_back(schedule); }

User* DatabaseManager::getUserById(const std::string& userId) {
    qDebug() << "所有用户列表:";
    for (const auto& user : users) {
        qDebug() << "用户ID:" << QString::fromStdString(user.getUserId())
            << "用户名:" << QString::fromStdString(user.getUsername())
            << "角色:" << QString::fromStdString(user.getRole());
    }

    QString searchId = QString::fromStdString(userId);
    searchId = searchId.replace("\"", "").trimmed(); // 移除引号和空格
    qDebug() << "清理后的查找用户ID:" << searchId;

    // 首先尝试精确匹配用户ID
    for (auto& user : users) {
        QString currentId = QString::fromStdString(user.getUserId()).trimmed();
        qDebug() << "比较用户ID: 查找'" << searchId << "' vs 当前'" << currentId << "'";

        if (currentId == searchId) {
            qDebug() << "找到匹配的用户ID";
            return &user;
        }
    }

    // 如果没有找到，尝试通过用户名查找
    for (auto& user : users) {
        QString currentUsername = QString::fromStdString(user.getUsername()).trimmed();
        qDebug() << "通过用户名比较: 查找'" << searchId << "' vs 当前'" << currentUsername << "'";

        if (currentUsername == searchId) {
            qDebug() << "找到匹配的用户名";
            return &user;
        }
    }

    qDebug() << "未找到匹配的用户";
    return nullptr;
}

Train* DatabaseManager::getTrainById(int trainId) {
    for (auto& train : trains) {
        if (train.getTrainId() == trainId) {
            return &train;
        }
    }
    return nullptr;
}

Order* DatabaseManager::getOrderById(int orderId) {
    auto it = std::find_if(orders.begin(), orders.end(),
        [&](const Order& o) { return o.getOrderId() == orderId; });
    return it != orders.end() ? &(*it) : nullptr;
}

Station* DatabaseManager::getStationById(int stationId) {
    auto it = std::find_if(stations.begin(), stations.end(),
        [&](const Station& s) { return s.getStationId() == stationId; });
    return it != stations.end() ? &(*it) : nullptr;
}

void DatabaseManager::checkAndCreateNecessaryFiles() {
    QStringList necessaryFiles = {
        "/users.txt",
        "/trains.txt",
        "/orders.txt",
        "/seats.txt",
        "/stations.txt",
        "/train_schedules.txt"
    };

    for (const QString& file : necessaryFiles) {
        QString filePath = dataDir + file;
        QFile fileCheck(filePath);

        // 只有当文件不存在时才创建空文件
        if (!fileCheck.exists()) {
            qDebug() << "File does not exist, creating:" << filePath;

            // 创建空文件
            if (fileCheck.open(QIODevice::WriteOnly)) {
                // 写入UTF-8 BOM头以确保文件是UTF-8编码
                QTextStream out(&fileCheck);
                setUTF8Encoding(out);
                out << "\uFEFF"; // UTF-8 BOM
                fileCheck.close();
                qDebug() << "Created empty file:" << filePath;
            }
            else {
                qDebug() << "Failed to create file:" << filePath;
            }
        }
        else {
            qDebug() << "File already exists, skipping creation:" << filePath;
        }
    }
}

void DatabaseManager::processUserLine(const QString& line) {
    // 使用制表符分割
    QStringList parts = line.split('\t', Qt::SkipEmptyParts);
    if (parts.size() < 7) {
        qDebug() << "字段数量不足，跳过行:" << line;
        return;
    }

    try {
        QString userId = parts[0].trimmed();
        QString username = parts[1].trimmed();
        QString displayName = parts[2].trimmed();
        QString password = parts[3].trimmed();
        QString phone = parts[4].trimmed();
        QString role = parts[5].trimmed();
        QString idCard = parts[6].trimmed();

        users.emplace_back(
            userId.toStdString(),
            username.toStdString(),
            displayName.toStdString(),
            password.toStdString(),
            phone.toStdString(),
            role.toStdString(),
            idCard.toStdString()
        );

        qDebug() << "成功加载用户:" << username << "角色:" << role;
    }
    catch (const std::exception& e) {
        qDebug() << "解析用户数据异常:" << e.what();
    }
}