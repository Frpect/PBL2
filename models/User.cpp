#include "User.h"
#include <sstream>

User::User(std::string hoTen, std::string sdt, std::string gioiTinh)
    : hoTen_(std::move(hoTen)), sdt_(std::move(sdt)), gioiTinh_(std::move(gioiTinh)) {}

User::User(const std::string& u, const std::string& p, Role r)
    : username_(u), password_(p), role(r) {}

User::User(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gioiTinh, Role r)
    : hoTen_(hoTen), sdt_(sdt), gioiTinh_(gioiTinh), username_(username), password_(password), role(r) {}

const std::string& User::getHoTen() const { return hoTen_; }
const std::string& User::getSDT() const { return sdt_; }
const std::string& User::getGioiTinh() const { return gioiTinh_; }
const std::string& User::getUsername() const { return username_; }
const std::string& User::getPassword() const { return password_; }

void User::setHoTen(const std::string& ten) { hoTen_ = ten; }
void User::setSDT(const std::string& sdt) { sdt_ = sdt; }
void User::setGioiTinh(const std::string& gt) { gioiTinh_ = gt; }
void User::setUsername(const std::string& username) { username_ = username; }
void User::setPassword(const std::string& password) { password_ = password; }

std::string User::xemThongTin() const {
    std::ostringstream os;
    os << "Ho ten: " << hoTen_ << "\n"
       << "SDT: " << sdt_ << "\n"
       << "Gioi tinh: " << gioiTinh_;
    return os.str();
}
