#ifndef USER_H
#define USER_H

#include <string>
enum class Role { KHACH_HANG, NHAN_VIEN, QUAN_LY };
class User {
protected:
    std::string hoTen_;
    std::string sdt_;
    std::string gioiTinh_;
    std::string username_;
    std::string password_;
public:
    Role role;
    User() = default;
    User(std::string hoTen, std::string sdt, std::string gioiTinh);
    User(const std::string& u, const std::string& p, Role r);
    User(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gioiTinh, Role r);
    virtual ~User() = default;

    const std::string& getHoTen() const;
    const std::string& getSDT() const;
    const std::string& getGioiTinh() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;

    void setHoTen(const std::string& ten);
    void setSDT(const std::string& sdt);
    void setGioiTinh(const std::string& gt);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);

    virtual std::string xemThongTin() const;
};

#endif
