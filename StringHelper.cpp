#include "StringHelper.h"
#include  <QRegularExpression>
#include <QDateTime>
#include <QRandomGenerator>

using namespace Qt;
using namespace std;

QString StringHelper::trim(const QString& str) {
    QString trimmed = str.trimmed(); // 修剪半角空格
    // 修剪全角空格
    while (trimmed.startsWith("　")) trimmed.remove(0, 1);
    while (trimmed.endsWith("　")) trimmed.chop(1);
    return trimmed;
}

std::vector<QString> StringHelper::split(const QString& str, char delimiter) {
    std::vector<QString> result;
    QString current;
    for (const QChar& c : str) {
        if (c == delimiter) {
            result.push_back(current);
            current.clear();
        }
        else {
            current += c;
        }
    }
    result.push_back(current); // 添加最后一段
    return result;
}

int StringHelper::toInt(const QString& str, bool* ok) {
    QString trimmed = trim(str);
    bool internalOk;
    int value = trimmed.toInt(&internalOk);
    if (ok) *ok = internalOk;
    return value;
}

bool StringHelper::isValidPhone(const QString& phone) {
    QRegularExpression regex("^1\\d{10}$");
    QRegularExpressionMatch match = regex.match(trim(phone));
    return match.hasMatch();
}

bool StringHelper::isValidIdCard(const QString& idCard) {
    // 中国大陆身份证号规则：18位，最后一位可能为X/x
    QRegularExpression regex("^[1-9]\\d{5}(18|19|20)\\d{2}(0[1-9]|1[0-2])(0[1-9]|[12]\\d|3[01])\\d{3}[0-9Xx]$");
    QRegularExpressionMatch match = regex.match(trim(idCard));
    return match.hasMatch();
}


QString StringHelper::generateUniqueId() {
    // 格式：时间戳（13位）+ 3位随机数
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    int random = QRandomGenerator::global()->bounded(1000);
    return QString("%1%2").arg(timestamp).arg(random, 3, 10, QChar('0'));
}

QString StringHelper::padLeft(const QString& str, int length, QChar padChar) {
    if (str.length() >= length) return str;
    return QString(length - str.length(), padChar) + str;
}