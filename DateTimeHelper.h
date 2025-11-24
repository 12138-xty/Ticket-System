#ifndef DATETIMEHELPER_H
#define DATETIMEHELPER_H

#include <QString>
#include <QDateTime>
#include <QDate>

class DateTimeHelper {
public:
    // 解析字符串为QDateTime（支持"YYYY-MM-DD HH:MM:SS"格式）
    static QDateTime parseDateTime(const QString& datetimeStr);

    // 解析字符串为QDate（支持"YYYY-MM-DD"格式）
    static QDate parseDate(const QString& dateStr);

    // 将QDateTime格式化为"YYYY-MM-DD HH:MM:SS"字符串
    static QString formatDateTime(const QDateTime& datetime);

    // 将QDate格式化为"YYYY-MM-DD"字符串
    static QString formatDate(const QDate& date);

    // 验证时间字符串格式是否正确（"YYYY-MM-DD HH:MM:SS"）
    static bool isValidDateTime(const QString& datetimeStr);

    // 验证日期字符串格式是否正确（"YYYY-MM-DD"）
    static bool isValidDate(const QString& dateStr);

    // 计算两个日期之间的天数差
    static int daysBetween(const QDate& startDate, const QDate& endDate);

    // 比较两个时间字符串的大小（返回true表示dt1在dt2之前）
    static bool isBefore(const QString& dt1, const QString& dt2);
};

#endif // DATETIMEHELPER_H