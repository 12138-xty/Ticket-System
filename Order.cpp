#include "Order.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// 默认构造函数
Order::Order()
    : orderId(0), userId(0), trainId(0), seatId(0),
    startStationId(0), endStationId(0),
    travelDate(""), orderTime(""), status("booked") {
}

// 带参数构造函数
Order::Order(int orderId, int userId, int trainId, int seatId,
    int startStationId, int endStationId,
    const std::string& travelDate, const std::string& orderTime,
    const std::string& status)
    : orderId(orderId), userId(userId), trainId(trainId), seatId(seatId),
    startStationId(startStationId), endStationId(endStationId),
    travelDate(travelDate), orderTime(orderTime), status(status) {
    // 简单的数据验证
    if (status != "booked" && status != "canceled" && status != "changed") {
        throw std::invalid_argument("Invalid order status");
    }
}

// Getter方法实现
int Order::getOrderId() const {
    return orderId;
}

int Order::getUserId() const {
    return userId;
}

int Order::getTrainId() const {
    return trainId;
}

int Order::getSeatId() const {
    return seatId;
}

int Order::getStartStationId() const {
    return startStationId;
}

int Order::getEndStationId() const {
    return endStationId;
}

std::string Order::getTravelDate() const {
    return travelDate;
}

std::string Order::getOrderTime() const {
    return orderTime;
}

std::string Order::getStatus() const {
    return status;
}

void Order::setTrainId(int trainId) {
    this->trainId = trainId;
}

void Order::setTravelDate(const std::string& travelDate) {
    this->travelDate = travelDate;
}

void Order::setStartStationId(int startStationId) {
    this->startStationId = startStationId;
}

void Order::setEndStationId(int endStationId) {
    this->endStationId = endStationId;
}

void Order::setOrderTime(const std::string& orderTime) {
    this->orderTime = orderTime;
}

void Order::setUserId(int userId) {
    this->userId = userId;
}

void Order::setSeatId(int seatId) {
    this->seatId = seatId;
}

void Order::setStatus(const std::string& status) {
    if (status != "booked" && status != "canceled" && status != "changed") {
        throw std::invalid_argument("Invalid order status");
    }
    this->status = status;
}