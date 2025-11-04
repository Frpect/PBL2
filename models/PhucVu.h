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
    PhucVu(std::string ma, std::string ten, std::string sdt, std::string gt,
           std::string ca, double luong);

    void taoDonHang(const DonHang& dh);
    void guiOrderXuongBep(const std::string& maDon);
    std::string xemThongTin() const override;
    std::string inHoaDon(const std::string& maDon) const;
};

#endif
