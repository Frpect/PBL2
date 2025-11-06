#include "KhachHang.h"
#include <sstream>
#include <iostream>

void KhachHang::datMon(const DonHang& don) {
    lichSuDon_.push_back(don);
    std::cout << "Khach hang " << hoTen_ << " da dat don hang: " << don.getMaDonHang() << "\n";
}

void KhachHang::thanhToan(DonHang& don) {
    double tong = don.tinhTongTien();
    std::cout << "Thanh toan don hang " << don.getMaDonHang() << " tong: " << tong << " VND\n";
    diemTieuDung_ += static_cast<int>(tong / 100000); // cứ 100k = 1 điểm
}

std::string KhachHang::xemThongTin() const {
    std::ostringstream os;
    os << User::xemThongTin() << "\n"
       << "Ma KH: " << maKhachHang_ << "\n"
       << "Diem tich luy: " << diemTieuDung_ << "\n"
       << "Hang thanh vien: " << hangThanhVien_;
    return os.str();
}
std::string KhachHang::getMaKhachHang() const {
    return maKhachHang_;
}
int KhachHang::idCounter_ = 0;
KhachHang::KhachHang(std::string ten, std::string sdt, std::string gt)
    : User(ten, sdt, gt), diemTieuDung_(0), hangThanhVien_("Thuong")
{
    idCounter_++;
    maKhachHang_ = "KH" + std::to_string(idCounter_);
}

KhachHang::KhachHang(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt)
    : User(username, password, hoTen, sdt, gt, Role::KHACH_HANG),
      diemTieuDung_(0), hangThanhVien_("Thuong")
{
    idCounter_++;
    maKhachHang_ = "KH" + std::to_string(idCounter_);
}

const std::vector<DonHang>& KhachHang::getLichSuDon() const
{
    return lichSuDon_;
}
