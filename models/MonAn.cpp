#include "MonAn.h"
#include <utility>

MonAn::MonAn(std::string ma, std::string ten, std::string loai, double gia, int sl)
    : maMon_(std::move(ma)), tenMon_(std::move(ten)), loai_(std::move(loai)), gia_(gia), soLuong_(sl) {}

void MonAn::capNhatSoLuong(int delta) {
    soLuong_ += delta;
    if (soLuong_ < 0) soLuong_ = 0;
}

std::string MonAn::xemThongTin() const {
    std::ostringstream os;
    os << "Mon: " << tenMon_ << " (" << loai_ << ")\n"
       << "Gia: " << gia_ << " | So luong: " << soLuong_;
    return os.str();
}
