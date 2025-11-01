#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string hoTen_;
    std::string sdt_;
    std::string gioiTinh_;

public:
    User() = default;
    User(std::string hoTen, std::string sdt, std::string gioiTinh);

    virtual ~User() = default;

    const std::string& getHoTen() const;
    const std::string& getSDT() const;
    const std::string& getGioiTinh() const;

    void setHoTen(const std::string& ten);
    void setSDT(const std::string& sdt);
    void setGioiTinh(const std::string& gt);

    virtual std::string xemThongTin() const;
};

#endif
