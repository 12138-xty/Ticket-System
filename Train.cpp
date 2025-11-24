#include "Train.h"
#include <fstream>
#include <QDebug>
#include <QString>
#include<iomanip>
#include <vector>
#include <string>

using namespace std;

// 默认构造函数
Train::Train()
    : trainId(0), trainCode(""), type(""),
    startStationId(0), endStationId(0)
{
}

// 带参数构造函数
Train::Train(int trainId, const std::string& trainCode, const std::string& type,
    int startStationId, int endStationId)
    : trainId(trainId), trainCode(trainCode), type(type),
    startStationId(startStationId), endStationId(endStationId)
{
}

// 析构函数
Train::~Train()
{
    qDebug() << "Train object destroyed";
}

// Setter 方法实现
void Train::setTrainId(int trainId) {
    this->trainId = trainId;
}

void Train::setTrainCode(const std::string& trainCode) {
    this->trainCode = trainCode;
}

void Train::setType(const std::string& type) {
    this->type = type;
}

void Train::setStartStationId(int startStationId) {
    this->startStationId = startStationId;
}

void Train::setEndStationId(int endStationId) {
    this->endStationId = endStationId;
}

// Getter 方法实现
int Train::getTrainId() const {
    return trainId;
}

string Train::getTrainCode() const {
    return trainCode;
}

string Train::getType() const {
    return type;
}

int Train::getStartStationId() const {
    return startStationId;
}

int Train::getEndStationId() const {
    return endStationId;
}


bool Train::WriteToTrain(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::app);  // 追加模式写入

    if (!outFile.is_open()) {
        qDebug() << "Error: Unable to open file" << QString::fromStdString(filename);
        return false;
    }

    try {
        // 写入.txt文件格式的数据
        outFile << std::left;
        outFile << std::setw(10) << trainId << " ";
        outFile << std::setw(10) << trainCode << " ";
        outFile << std::setw(10) << type << " ";
        outFile << std::setw(10) << startStationId << " ";
        outFile << std::setw(10) << endStationId << "\n";

    }
    catch (const std::exception& e) {
        qDebug() << "Error writing to file:" << e.what();
        outFile.close();
        return false;
    }

    outFile.close();
    return true;
}