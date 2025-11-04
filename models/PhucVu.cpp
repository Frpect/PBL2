#include "PhucVu.h"
#include <sstream>

PhucVu::PhucVu(std::string ma, std::string ten, std::string sdt, std::string gt,
               std::string ca, double luong)
    : NhanSu(std::move(ma), std::move(ten), std::move(sdt), std::move(gt),
             ma, "123", luong, std::move(ca)) {}

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