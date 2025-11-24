#include "TrainSchedule.h"
#include <fstream>
#include <stdexcept>
#include<iomanip>
#include <vector>


using namespace std;
// 默认构造函数
TrainSchedule::TrainSchedule() :
    scheduleId(0),
    trainId(0),
    stationId(0),
    stopOrder(0),
    arriveTime(""),
    departTime("")
{
}

// 带参数构造函数
TrainSchedule::TrainSchedule(int scheduleId, int trainId, int stationId,
    int stopOrder, const std::string& arriveTime,
    const std::string& departTime) :
    scheduleId(scheduleId),
    trainId(trainId),
    stationId(stationId),
    stopOrder(stopOrder),
    arriveTime(arriveTime),
    departTime(departTime)
{
}

// Getter 方法实现
int TrainSchedule::getScheduleId() const {
    return scheduleId;
}

int TrainSchedule::getTrainId() const {
    return trainId;
}

int TrainSchedule::getStationId() const {
    return stationId;
}

int TrainSchedule::getStopOrder() const {
    return stopOrder;
}

std::string TrainSchedule::getArriveTime() const {
    return arriveTime;
}

std::string TrainSchedule::getDepartTime() const {
    return departTime;
}

// Setter 方法实现
void TrainSchedule::setScheduleId(int scheduleId) {
    this->scheduleId = scheduleId;
}

void TrainSchedule::setTrainId(int trainId) {
    this->trainId = trainId;
}

void TrainSchedule::setStationId(int stationId) {
    this->stationId = stationId;
}

void TrainSchedule::setStopOrder(int stopOrder) {
    this->stopOrder = stopOrder;
}

void TrainSchedule::setArriveTime(const std::string& arriveTime) {
    this->arriveTime = arriveTime;
}

void TrainSchedule::setDepartTime(const std::string& departTime) {
    this->departTime = departTime;
}


bool TrainSchedule::WriteToTrainSchedule(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::app); // 以追加模式打开文件

    if (!outFile.is_open()) {
        return false; // 文件打开失败
    }

    try {
        // 写入.txt文件格式的数据，每个字段占固定宽度（例如 10 个字符）
        outFile << std::left; // 左对齐
        outFile << std::setw(10) << scheduleId;
        outFile << std::setw(10) << trainId;
        outFile << std::setw(10) << stationId;
        outFile << std::setw(10) << stopOrder;
        outFile << std::setw(10) << arriveTime;
        outFile << std::setw(10) << departTime << "\n";
    }
    catch (const std::exception& e) {
        outFile.close();
        return false; // 写入过程中发生错误
    }

    outFile.close();
    return true; // 写入成功
}