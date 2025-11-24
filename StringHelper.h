#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <QString>
#include <vector>
#include <string>

class StringHelper {
public:
    // 修剪字符串前后空格（包括全角空格）
    static QString trim(const QString& str);

    // 分割字符串（支持自定义分隔符）
    static std::vector<QString> split(const QString& str, char delimiter);

    // 安全转换字符串为整数（失败返回0，通过ok返回结果状态）
    static int toInt(const QString& str, bool* ok = nullptr);

    // 验证手机号格式（中国大陆11位数字）
    static bool isValidPhone(const QString& phone);

    // 验证身份证号格式（18位，最后一位支持X）
    static bool isValidIdCard(const QString& idCard);

    // 生成唯一ID（基于时间戳+随机数）
    static QString generateUniqueId();

    // 左填充字符串至指定长度
    static QString padLeft(const QString& str, int length, QChar padChar = ' ');
};

#endif // STRINGHELPER_H