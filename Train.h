#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

class Train {
public:
    // 构造函数
    Train();
    Train(int trainId, const std::string& trainCode, const std::string& type,
        int startStationId, int endStationId);

    // 析构函数
    virtual ~Train();

    // Setter方法
    void setTrainId(int trainId);
    void setTrainCode(const std::string& trainCode);
    void setType(const std::string& type);
    void setStartStationId(int startStationId);
    void setEndStationId(int endStationId);

    // Getter方法
    int getTrainId() const;
    std::string getTrainCode() const;
    std::string getType() const;
    int getStartStationId() const;
    int getEndStationId() const;

    // 文件操作
    bool WriteToTrain(const std::string& filename) const;
    // bool ReadFromTrain(const std::string& filename);

private:
    int trainId;            // 列车唯一标识ID
    std::string trainCode;  // 列车编号（如G1234）
    std::string type;       // 列车类型（如"G"高铁、"D"动车等）
    int startStationId;     // 始发站ID
    int endStationId;       // 终点站ID
};