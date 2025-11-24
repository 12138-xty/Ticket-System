#pragma once
#include <iostream>
#include <string>

class TrainSchedule {
public:
    // 构造函数
    TrainSchedule();
    TrainSchedule(int scheduleId, int trainId, int stationId,
        int stopOrder, const std::string& arriveTime,
        const std::string& departTime);

    // Getter方法
    int getScheduleId() const;
    int getTrainId() const;
    int getStationId() const;
    int getStopOrder() const;
    std::string getArriveTime() const;
    std::string getDepartTime() const;

    // Setter方法
    void setScheduleId(int scheduleId);
    void setTrainId(int trainId);
    void setStationId(int stationId);
    void setStopOrder(int stopOrder);
    void setArriveTime(const std::string& arriveTime);
    void setDepartTime(const std::string& departTime);


    // 文件操作
    bool WriteToTrainSchedule(const std::string& filename) const;

private:
    int scheduleId;      // 时刻表ID
    int trainId;         // 列车ID
    int stationId;       // 车站ID
    int stopOrder;       // 停靠顺序
    std::string arriveTime;  // 到达时间
    std::string departTime;  // 发车时间
};