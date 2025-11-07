#include "PhucVu.h"
#include <sstream>

PhucVu::PhucVu(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string ca, double luong)
    : NhanSu(username, // Dùng username làm mã nhân viên
             hoTen,
             sdt,
             gt, username, password, luong, ca)
{
}

void PhucVu::taoDonHang(const DonHang& dh) {
    danhSachDon_.push_back(dh);
}

void PhucVu::guiOrderXuongBep(const std::string& maDon) {
    for (auto& d : danhSachDon_) {
        if (d.getMaDonHang() == maDon)
            d.capNhatTrangThai("Đang chuẩn bị");
    }
}

std::string PhucVu::xemThongTin() const {
    std::ostringstream os;
    os << NhanSu::xemThongTin() << "\nSo don dang phu trach: " << danhSachDon_.size();
    return os.str();
}
std::string PhucVu::inHoaDon(const std::string& maDon) const {
    for (const auto& d : danhSachDon_) {
        if (d.getMaDonHang() == maDon) {
            std::ostringstream os;
            os << "===== HOA DON =====\n";
            os << d.xemChiTiet();
            os << "Tong tien: " << d.tinhTongTien() << " VND\n";
            os << "===================\n";
            return os.str();
        }
    }
    return "Khong tim thay don hang.\n";
}