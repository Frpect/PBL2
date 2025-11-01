#include "KhachHang.h"
#include <sstream>
#include <iostream>

KhachHang::KhachHang(std::string ma, std::string ten, std::string sdt, std::string gt,
                     int diem, std::string hang)
    : User(std::move(ten), std::move(sdt), std::move(gt)),
      maKhachHang_(std::move(ma)), diemTieuDung_(diem), hangThanhVien_(std::move(hang)) {}

void KhachHang::datMon(const DonHang& don) {
    lichSuDon_.push_back(don);
    std::cout << "Khach hang " << hoTen_ << " da dat don hang: " << don.getMaDonHang() << "\n";
}

void KhachHang::thanhToan(DonHang& don) {
    double tong = don.tinhTongTien();
    std::cout << "Thanh toan don hang " << don.getMaDonHang() << " tong: " << tong << " VND\n";
    diemTieuDung_ += static_cast<int>(tong / 100000); // cứ 100k = 1 điểm
}

std::string KhachHang::xemMenu() const {
    std::ostringstream os;
    os << "Danh muc mon an hien co (goi mau): \n"
       << "- Burger: 45000 VND\n"
       << "- Pepsi: 12000 VND\n"
       << "- Com chien: 40000 VND\n";
    return os.str();
}

std::string KhachHang::xemThongTin() const {
    std::ostringstream os;
    os << User::xemThongTin() << "\n"
       << "Ma KH: " << maKhachHang_ << "\n"
       << "Diem tich luy: " << diemTieuDung_ << "\n"
       << "Hang thanh vien: " << hangThanhVien_;
    return os.str();
}
