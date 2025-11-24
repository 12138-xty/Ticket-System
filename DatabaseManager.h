#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <vector>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "User.h"
#include "Train.h"
#include "Order.h"
#include "Seat.h"
#include "Station.h"
#include "TrainSchedule.h"

class DatabaseManager {
private:
    QString dataDir; // 数据存储目录
    std::vector<User> users;
    std::vector<Train> trains;
    std::vector<Order> orders;
    std::vector<Seat> seats;
    std::vector<Station> stations;
    std::vector<TrainSchedule> trainSchedules;
    QString m_dataDir;  // 添加数据目录成员
    QMap<QString, Train> m_trains;  // 添加列车容器
    QMap<QString, Seat> m_seats;    // 添加座位容器
    QMap<QString, TrainSchedule> m_trainSchedules; // 添加列车时刻表容器


    // 辅助方法：检查并创建数据目录
    bool createDataDir();

public:
    // 构造函数：默认数据目录为"./data"
    DatabaseManager(const QString& dataDir = "");

    // 初始化数据库：创建目录并加载所有数据
    bool init();

    // 加载数据方法
    bool loadUsers();
    bool loadTrains();
    bool loadOrders();
    bool loadSeats();
    bool loadStations();
    bool loadTrainSchedules();

    // 保存数据方法
    bool saveUsers();
    bool saveTrains();
    bool saveOrders();
    bool saveSeats();
    bool saveStations();
    bool saveTrainSchedules();

    // 数据获取方法
    const std::vector<User>& getUsers() const;
    const std::vector<Train>& getTrains() const;
    const std::vector<Order>& getOrders() const;
    const std::vector<Seat>& getSeats() const;
    const std::vector<Station>& getStations() const;
    const std::vector<TrainSchedule>& getTrainSchedules() const;

    // 数据添加方法
    void addUser(const User& user);
    bool addTrain(const Train& train);
    void addOrder(const Order& order);
    void addSeat(const Seat& seat);
    void addStation(const Station& station);
    void addTrainSchedule(const TrainSchedule& schedule);

    // 数据查询方法
    User* getUserById(const std::string& userId);
    Train* getTrainById(int trainId);
    Order* getOrderById(int orderId);
    Station* getStationById(int stationId);

    void checkAndCreateNecessaryFiles();
    void processUserLine(const QString& line);

    void setUTF8Encoding(QTextStream& stream);
};

#endif // DATABASEMANAGER_H