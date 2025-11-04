#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "User.h"
#include "DonHang.h"
#include <vector>

class KhachHang : public User {
private:
    std::string maKhachHang_;
    int diemTieuDung_;
    std::string hangThanhVien_;
    std::vector<DonHang> lichSuDon_;

public:
    KhachHang() = default;
    KhachHang(std::string ma, std::string ten, std::string sdt, std::string gt,
              int diem = 0, std::string hang = "Thuong");

    void datMon(const DonHang& don);
    void thanhToan(DonHang& don);
    std::string xemMenu() const;
    std::string xemThongTin() const override;
};

#endif
