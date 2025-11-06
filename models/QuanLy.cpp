#include "QuanLy.h"
#include <algorithm>
#include <sstream>
using namespace std;

QuanLy::QuanLy(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string ca, double luong)
    : NhanSu(username, // Dùng username làm mã nhân viên
             hoTen,
             sdt,
             gt, username, password, luong, ca)
{
}

void QuanLy::themMon(const MonAn& mon) {
    danhSachMon_.push_back(mon);
}

void QuanLy::xoaMon(const std::string& ten) {
    danhSachMon_.erase(std::remove_if(danhSachMon_.begin(), danhSachMon_.end(),
        [&](const MonAn& m){ return m.xemThongTin().find(ten) != std::string::npos; }),
        danhSachMon_.end());
}

std::string QuanLy::baoCaoDoanhThu() const {
    double tongDoanhThu = 0;
    for (const auto& don : danhSachDonHang_) {
        if (don.getTrangThai() == "da thanh toan") {
            tongDoanhThu += don.tinhTongTien();
        }
    }
    std::ostringstream os;
    os << "Tong doanh thu: " << tongDoanhThu << " VND\n";
    return os.str();
}
std::string QuanLy::xemThongTin() const {
    std::ostringstream os;
    os << NhanSu::xemThongTin() << "\nChuc vu: Quan ly";
    return os.str();
}
