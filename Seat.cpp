#include "Seat.h"
#include <vector>


using namespace std;

// 默认构造函数
Seat::Seat() : seatId(0), trainId(0), seatNo(""), seatType("二等") {}

// 带参数构造函数
Seat::Seat(int seatId, int trainId, const std::string& seatNo,
    const std::string& seatType)
    : seatId(seatId), trainId(trainId), seatNo(seatNo), seatType(seatType) {
}

// Getter方法实现
int Seat::getSeatId() const {
    return seatId;
}

int Seat::getTrainId() const {
    return trainId;
}

std::string Seat::getSeatNo() const {
    return seatNo;
}

std::string Seat::getSeatType() const {
    return seatType;
}

// Setter方法实现
void Seat::setSeatNo(const std::string& seatNo) {
    this->seatNo = seatNo;
}

void Seat::setSeatType(const std::string& seatType) {
    this->seatType = seatType;
}
