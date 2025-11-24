#pragma once
#include <string>
#include <QString> 

class Seat
{
public:
    // 构造函数
    Seat();
    Seat(int seatId, int trainId, const std::string& seatNo,
        const std::string& seatType);

    // Getter方法
    int getSeatId() const;
    int getTrainId() const;
    std::string getSeatNo() const;
    std::string getSeatType() const;
   

    // Setter方法
    void setSeatNo(const std::string& seatNo);
    void setSeatType(const std::string& seatType);

private:
    int seatId;          // 座位ID
    int trainId;         // 所属列车ID
    std::string seatNo;  // 座位号(如"1A"、"2B"等)
    std::string seatType; // 座位类型("商务"、"一等"、"二等")
};