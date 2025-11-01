#include "User.h"
#include <sstream>

User::User(std::string hoTen, std::string sdt, std::string gioiTinh)
    : hoTen_(std::move(hoTen)), sdt_(std::move(sdt)), gioiTinh_(std::move(gioiTinh)) {}

const std::string& User::getHoTen() const { return hoTen_; }
const std::string& User::getSDT() const { return sdt_; }
const std::string& User::getGioiTinh() const { return gioiTinh_; }

void User::setHoTen(const std::string& ten) { hoTen_ = ten; }
void User::setSDT(const std::string& sdt) { sdt_ = sdt; }
void User::setGioiTinh(const std::string& gt) { gioiTinh_ = gt; }

std::string User::xemThongTin() const {
    std::ostringstream os;
    os << "Ho ten: " << hoTen_ << "\n"
       << "SDT: " << sdt_ << "\n"
       << "Gioi tinh: " << gioiTinh_;
    return os.str();
}
