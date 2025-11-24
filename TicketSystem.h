#ifndef TICKETSYSTEM_H
#define TICKETSYSTEM_H

#include <QObject>
#include <string>
#include <vector>
#include "DatabaseManager.h"
#include "UndoRedoManager.h"
#include "StringHelper.h"
#include "User.h"
#include "Train.h"
#include "Order.h"
#include "Station.h"
#include "TrainSchedule.h"
#include "Seat.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QTimeEdit>
#include <QComboBox>

// 前向声明
class User;
class Train;
class Order;
class Station;
class Seat;
class TrainSchedule;
class QTableWidget;

class TicketSystem : public QObject {
    Q_OBJECT

private:
    DatabaseManager dbManager;
    UndoRedoManager undoManager;
    User* currentUser = nullptr;
    std::vector<User> m_users;                  

public:
    explicit TicketSystem(QObject* parent = nullptr);
    ~TicketSystem() override;

    // 用户管理
    bool validateLogin(const QString& userId, const QString& password);
    void logout();
    User* getCurrentUser() const;

    // 列车查询
    std::vector<Train> queryTrains(int startStationId, int endStationId, const QString& date);
    std::vector<Train*> searchTrains(const std::string& startStation, const std::string& endStation, const std::string& date);
    int getAvailableSeats(int trainId, const QString& date);

    // 订单管理
    bool bookTicket(const std::string& userId, int trainId, const std::string& date,
        int startStationId, int endStationId);
    bool cancelOrder(int orderId);
    std::vector<Order> getUserOrders(int userId) const;

    // 数据获取
    std::vector<std::string> getAllStations() const;
    std::vector<const Train*> getAllTrains() const;
    std::vector<User*> getAllUsers() const;
    const std::vector<Station>& getStations() const;
    std::vector<TrainSchedule> getTrainSchedules() const;
    const std::vector<Seat>& getSeats() const;
    const std::vector<Order>& getOrders() const;

    // 管理功能
    bool addTrain(const std::string& trainCode, const std::string& type,int startStationId, int endStationId);
    bool editTrain(int trainId, const std::string& trainCode,
        const std::string& type, int startStationId,
        int endStationId,
        const std::vector<TrainSchedule>& newSchedules = {},
        const std::vector<Seat>& newSeats = {});
    bool deleteTrain(int trainId);
    bool addUser();
    bool addTrainWithSchedulesAndSeats(const std::string& trainCode,const std::string& type,int startStationId,int endStationId,QTableWidget* scheduleTable,int businessSeats,int firstClassSeats,int secondClassSeats );

    // 撤销重做
    bool undo();
    bool redo();

    QString getStationNameById(int stationId) const;
    string getArrivalTimeForTrain(int trainId) const;
    string getDepartureTimeForTrain(int trainId) const;
    int getAvailableSeatsForTrain(int trainId, const std::string& date) const;

    Train* getTrainById(int trainId);

    string getTrainCodeByOrder(const Order& order);
    vector<Order> getUserOrdersWithDetails(const std::string& userId);
    pair<std::string, std::string> getOrderTimeByOrder(const Order& order);

    Order* getOrderById(int orderId);

    bool changeOrder(int orderId, int newTrainId, const std::string& newDate, int newSeatId = -1);

    bool registerUser(const std::string& username, const std::string& password,const std::string& displayName, const std::string& phone, const std::string& idCard, const std::string& role = "user");

    bool isUsernameAvailable(const std::string& username);

    bool editUser(const std::string& userId, const std::string& newUsername,
        const std::string& newPhone, const std::string& newPassword,
        const std::string& newRole);
    bool deleteUser(const std::string& userId);
    bool isAdminUser(const std::string& userId);

    User* getUserById(const std::string& userId);
    bool saveUsers();

    bool updateUserInfo(const std::string& name, const std::string& phone,const std::string& password);
    bool saveUsersToFile();
    bool replaceInFile(const QString& filePath, const QString& oldContent, const QString& newContent);
    bool isTrainAvailableToday(int trainId, int startStationId) const;
    bool removeLinesWithId(const QString& filePath, int id, int idColumn);
    QDateTime getOrderDepartureDateTime(const Order& order) const;
    bool addStation(const std::string& stationName);
    bool deleteStation(const std::string& stationName);
    int findAvailableSeat(int trainId, const std::string& date);
    bool isOrderAffectingSection(const Order& order, int targetStartId, int targetEndId);
    std::string getDepartureTimeAtStation(int trainId, int stationId);
    bool isTrainPassThroughStations(int trainId, int startStationId, int endStationId);
    int getAvailableSeatsForTrainSection(int trainId, const std::string& date, int startStationId, int endStationId);
    int findAvailableSeatForSection(int trainId, const std::string& date, int startStationId, int endStationId);
private:
    int generateNextUserId();

signals:
    void userLoggedIn(User* user);
    void userLoggedOut();
    void ordersUpdated();
    void trainsUpdated();
   
};
#endif // TICKETSYSTEM_H