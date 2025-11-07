#ifndef PHUCVU_H
#define PHUCVU_H

#include "NhanSu.h"
#include "DonHang.h"
#include <vector>

class PhucVu : public NhanSu {
private:
    std::vector<DonHang> danhSachDon_;

public:
    PhucVu() = default;
    // Constructor tiện lợi để tạo PhucVu từ thông tin đăng ký
    PhucVu(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string ca, double luong);

    void taoDonHang(const DonHang& dh);
    void guiOrderXuongBep(const std::string& maDon);
    std::string xemThongTin() const override;
    std::string inHoaDon(const std::string& maDon) const;
};

#endif
