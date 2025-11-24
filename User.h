#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
private:
    std::string user_id;
    std::string username;
    std::string display_name;
    std::string password;
    std::string phone;
    std::string role;
    std::string id_card;

public:
    // Constructor
    User();
    User(const std::string& id, const std::string& uname, const std::string& dname,
        const std::string& pwd, const std::string& ph, const std::string& r,
        const std::string& idc);

    // Getters
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getDisplayName() const;
    std::string getPhone() const;
    std::string getRole() const;
    std::string getIdCard() const;
    std::string getPassword() const;
    // Setters
    void setUsername(const std::string& n);
    void setPassword(const std::string& pwd);
    void setPhone(const std::string& ph);
    void setRole(const std::string& r);
    void setDisplayName(const std::string& dname);
    void setIdCard(const std::string& idc);

    bool isAdmin() const;


    // Display user information
    void display() const;
    
    static std::vector<User> loadFromTXT(const std::string& filename);
    static void saveToTXT(const std::string& filename, const std::vector<User>& users);

    bool checkPassword(const std::string& inputPassword) const;

    static bool isUsernameAvailable(const std::string& username);

    bool isLocked() const;
    void setLocked(bool locked);
    std::string getBaseRole() const;
};

#endif // USER_H