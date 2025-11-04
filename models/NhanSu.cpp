#include "NhanSu.h"
#include <sstream>
#include <iostream>

NhanSu::NhanSu(std::string ma, std::string ten, std::string sdt, std::string gt,
               std::string tk, std::string mk, double luong, std::string ca)
    : User(std::move(ten), std::move(sdt), std::move(gt)),
      maNhanVien_(std::move(ma)), taiKhoan_(std::move(tk)), matKhau_(std::move(mk)),
      luong_(luong), caLam_(std::move(ca)) {}

const std::string& NhanSu::getMaNhanVien() const { return maNhanVien_; }
const std::string& NhanSu::getCaLam() const { return caLam_; }
double NhanSu::getLuong() const { return luong_; }

void NhanSu::setCaLam(const std::string& ca) { caLam_ = ca; }
void NhanSu::setLuong(double luong) { luong_ = luong; }

bool NhanSu::dangNhap(const std::string& tk, const std::string& mk) const {
    return tk == taiKhoan_ && mk == matKhau_;
}

void NhanSu::dangXuat() const {
    std::cout << hoTen_ << " da dang xuat.\n";
}

std::string NhanSu::xemThongTin() const {
    std::ostringstream os;
    os << User::xemThongTin() << "\n"
       << "Ma nhan vien: " << maNhanVien_ << "\n"
       << "Ca lam: " << caLam_ << "\n"
       << "Luong: " << luong_;
    return os.str();
}
