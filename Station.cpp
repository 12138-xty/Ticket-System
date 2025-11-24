#include "Station.h"
#include <vector>

using namespace std;

// 构造函数实现
Station::Station(int id, const QString& stationName)
    : stationId(id), name(stationName) {
}

// Getter和Setter方法实现
int Station::getStationId() const {
    return stationId;
}

void Station::setStationId(int id) {
    stationId = id;
}

QString Station::getName() const {
    return name;
}

void Station::setName(const QString& stationName) {
    name = stationName;
}
