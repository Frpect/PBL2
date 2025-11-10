#include "NhanSu.h"
#include "AuthService.h"
#include <sstream>
#include <iostream>

NhanSu::NhanSu(std::string ma, std::string ten, std::string sdt, std::string gt,
               std::string username, std::string password, double luong, std::string ca)
    : User(username, password, ten, sdt, gt, (ma.rfind("QL", 0) == 0) ? Role::QUAN_LY : Role::NHAN_VIEN),
      maNhanVien_(std::move(ma)), taiKhoan_(std::move(username)), matKhau_(std::move(password)),
      luong_(luong), caLam_(std::move(ca)) {}

const std::string& NhanSu::getMaNhanVien() const { return maNhanVien_; }
const std::string& NhanSu::getCaLam() const { return caLam_; }
double NhanSu::getLuong() const { return luong_; }

void NhanSu::setCaLam(const std::string& ca) { caLam_ = ca; }
void NhanSu::setLuong(double luong) { luong_ = luong; }

bool NhanSu::dangNhap(const std::string& tk, const std::string& mk, AuthService* authService) const {
    // Nếu có AuthService, sử dụng service để đăng nhập
    if (authService) {
        User* user = authService->login(tk, mk);
        return user != nullptr;
    }
    // Nếu không có service, kiểm tra trực tiếp (backward compatibility)
    return tk == taiKhoan_ && mk == matKhau_;
}

void NhanSu::dangXuat(AuthService* authService) const {
    // Nếu có AuthService, sử dụng service để đăng xuất
    if (authService) {
        authService->logout();
    }
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
