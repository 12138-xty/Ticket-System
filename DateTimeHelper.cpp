#include "DateTimeHelper.h"

using namespace std;

QDateTime DateTimeHelper::parseDateTime(const QString& datetimeStr) {
    return QDateTime::fromString(datetimeStr, "yyyy-MM-dd HH:mm:ss");
}

QDate DateTimeHelper::parseDate(const QString& dateStr) {
    return QDate::fromString(dateStr, "yyyy-MM-dd");
}

QString DateTimeHelper::formatDateTime(const QDateTime& datetime) {
    return datetime.toString("yyyy-MM-dd HH:mm:ss");
}

QString DateTimeHelper::formatDate(const QDate& date) {
    return date.toString("yyyy-MM-dd");
}

bool DateTimeHelper::isValidDateTime(const QString& datetimeStr) {
    return parseDateTime(datetimeStr).isValid();
}

bool DateTimeHelper::isValidDate(const QString& dateStr) {
    return parseDate(dateStr).isValid();
}

int DateTimeHelper::daysBetween(const QDate& startDate, const QDate& endDate) {
    return startDate.daysTo(endDate);
}

bool DateTimeHelper::isBefore(const QString& dt1, const QString& dt2) {
    QDateTime d1 = parseDateTime(dt1);
    QDateTime d2 = parseDateTime(dt2);
    return d1.isValid() && d2.isValid() && d1 < d2;
}