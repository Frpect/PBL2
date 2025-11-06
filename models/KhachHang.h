#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "User.h"
#include "DonHang.h"
#include <vector>
#include <string>

class KhachHang : public User {
private:
    std::string maKhachHang_;
    int diemTieuDung_;
    std::string hangThanhVien_;
    std::vector<DonHang> lichSuDon_;

    static int idCounter_; // biến static để sinh mã tự động

public:
    KhachHang() = default;

    // Constructor 3 tham số (mới) - tự động sinh mã khách hàng
    KhachHang(std::string ten, std::string sdt, std::string gt);

    // Constructor 4 tham số cho việc đăng ký
    KhachHang(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt);

    void datMon(const DonHang& don);
    void thanhToan(DonHang& don);
    virtual std::string xemThongTin() const override;

    // Getter
    std::string getMaKhachHang() const;
    const std::vector<DonHang>& getLichSuDon() const;
};

#endif
