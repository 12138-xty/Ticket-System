#pragma once
#include <string>
class Order
{
public:
    // 构造函数
    Order();
    Order(int orderId, int userId, int trainId, int seatId,
        int startStationId, int endStationId,
        const std::string& travelDate, const std::string& orderTime,
        const std::string& status);

    // Getter方法
    int getOrderId() const;
    int getUserId() const;
    int getTrainId() const;
    int getSeatId() const;
    int getStartStationId() const;
    int getEndStationId() const;
    std::string getTravelDate() const;
    std::string getOrderTime() const;
    std::string getStatus() const; // "booked", "canceled", "changed"

    // Setter方法
    void setTrainId(int trainId);
    void setTravelDate(const std::string& travelDate);
    void setStartStationId(int startStationId);
    void setEndStationId(int endStationId);
    void setOrderTime(const std::string& orderTime);
    void setUserId(int userId);
    void setSeatId(int seatId);
    void setStatus(const std::string& status);

private:
    int orderId;          // 订单ID
    int userId;           // 用户ID
    int trainId;          // 列车ID
    int seatId;           // 座位ID
    int startStationId;   // 起始站ID
    int endStationId;     // 终点站ID
    std::string travelDate; // 乘车日期(格式:YYYY-MM-DD)
    std::string orderTime;  // 下单时间(格式:YYYY-MM-DD HH:MM:SS)
    std::string status;    // 订单状态("booked"-已预订,"canceled"-已取消,"changed"-已改签)
};

