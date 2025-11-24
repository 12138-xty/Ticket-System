#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <qmetatype.h>
#include <qdebug>
#include <StringHelper.h>

using namespace std;

// Constructor implementation
User::User() {}

User::User(const std::string& id, const std::string& uname, const std::string& dname,
    const std::string& pwd, const std::string& ph, const std::string& r,
    const std::string& idc)
    : user_id(id), username(uname), display_name(dname), password(pwd),
    phone(ph), role(r), id_card(idc) {
}

// Getter implementations
std::string User::getUserId() const { return user_id; }
std::string User::getUsername() const { return username; }
std::string User::getDisplayName() const { return display_name; }
std::string User::getPhone() const { return phone; }
std::string User::getRole() const { return role; }
std::string User::getIdCard() const { return id_card; }
std::string User::getPassword() const { return password; }

// Setter implementations

void User::setUsername(const std::string& uname) { username = uname; }
void User::setPassword(const std::string& pwd) { password = pwd; }
void User::setPhone(const std::string& ph) { phone = ph; }
void User::setRole(const std::string& r) { role = r; }
void User::setDisplayName(const std::string& dname) { display_name = dname; }
void User::setIdCard(const std::string& idc) { id_card = idc; }

bool User::isAdmin() const { return role == "admin"; }

void User::display() const {
    std::cout << "User ID: " << user_id << "\n"
        << "Username: " << username << "\n"
        << "Display Name: " << display_name << "\n"
        << "Phone: " << phone << "\n"
        << "Role: " << role << "\n"
        << "ID Card: " << id_card << "\n";
}

std::vector<User> User::loadFromTXT(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return users;
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        try {
            // 解析固定宽度格式 (每个字段宽度15)
            if (line.length() >= 105) {
                std::string user_id = line.substr(0, 15);
                std::string username = line.substr(15, 15);
                std::string display_name = line.substr(30, 15);
                std::string password = line.substr(45, 15);
                std::string phone = line.substr(60, 15);
                std::string role = line.substr(75, 15);
                std::string id_card = line.substr(90, 18); // 身份证号稍长

                // 去除空格
                auto trim = [](std::string str) {
                    size_t start = str.find_first_not_of(" ");
                    size_t end = str.find_last_not_of(" ");
                    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
                    };

                users.emplace_back(
                    trim(user_id), trim(username), trim(display_name),
                    trim(password), trim(phone), trim(role), trim(id_card)
                );
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing user data: " << e.what() << std::endl;
        }
    }

    file.close();
    return users;
}

void User::saveToTXT(const std::string& filename, const std::vector<User>& users) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << " for writing" << std::endl;
        return;
    }

    // 写入用户数据 (固定宽度格式)
    for (const auto& user : users) {
        file << std::left << std::setw(15) << user.user_id.substr(0, 15)
            << std::setw(15) << user.username.substr(0, 15)
            << std::setw(15) << user.display_name.substr(0, 15)
            << std::setw(15) << user.password.substr(0, 15)
            << std::setw(15) << user.phone.substr(0, 15)
            << std::setw(15) << user.role.substr(0, 15)
            << std::setw(18) << user.id_card.substr(0, 18) << "\n";
    }

    file.close();
}

bool User::checkPassword(const std::string& inputPassword) const {
    // 转换为QString并清理
    QString storedQStr = QString::fromStdString(password).trimmed();
    QString inputQStr = QString::fromStdString(inputPassword).trimmed();

    qDebug() << "密码比较详情:";
    qDebug() << "存储密码长度:" << storedQStr.length();
    qDebug() << "输入密码长度:" << inputQStr.length();
    qDebug() << "存储密码:" << storedQStr;
    qDebug() << "输入密码:" << inputQStr;

    // 如果长度不同，直接返回false
    if (storedQStr.length() != inputQStr.length()) {
        qDebug() << "密码长度不同，验证失败";
        return false;
    }

    // 逐字符比较
    for (int i = 0; i < storedQStr.length(); ++i) {
        if (storedQStr.at(i) != inputQStr.at(i)) {
            qDebug() << "第" << i << "个字符不匹配:"
                << "存储='" << storedQStr.at(i) << "'(" << storedQStr.at(i).unicode() << ")"
                << "输入='" << inputQStr.at(i) << "'(" << inputQStr.at(i).unicode() << ")";
            return false;
        }
    }

    qDebug() << "密码验证成功";
    return true;
}

bool User::isUsernameAvailable(const std::string& username) {
    // 检查用户名是否已存在
    // 需要访问DatabaseManager
    return true; // 暂时返回true
}

bool User::isLocked() const {
    return role.find("(lock)") != std::string::npos;
}

void User::setLocked(bool locked) {
    std::string baseRole = getBaseRole();
    if (locked) {
        role = baseRole + "(lock)";
    }
    else {
        role = baseRole;
    }
}

std::string User::getBaseRole() const {
    std::string base = role;
    size_t pos = base.find("(lock)");
    if (pos != std::string::npos) {
        base.erase(pos, 6); // 移除 "(lock)" 标记
    }
    return base;
}