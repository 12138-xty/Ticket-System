#ifndef STATION_H
#define STATION_H

#include <QString>

class Station {
private:
    int stationId;
    QString name;

public:
    // 构造函数
    Station(int id = 0, const QString& stationName = "");

    // Getter和Setter方法
    int getStationId() const;
    void setStationId(int id);

    QString getName() const;
    void setName(const QString& stationName);
};

#endif // STATION_H
