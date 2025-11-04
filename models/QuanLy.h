#ifndef QUANLY_H
#define QUANLY_H

#include "NhanSu.h"
#include "MonAn.h"
#include "DonHang.h"
#include <vector>

class QuanLy : public NhanSu {
private:
    std::vector<MonAn> danhSachMon_;
    std::vector<DonHang> danhSachDonHang_;
public:
    QuanLy() = default;
    QuanLy(std::string ma, std::string ten, std::string sdt, std::string gt,
           std::string ca, double luong);

    void themMon(const MonAn& mon);
    void xoaMon(const std::string& ten);
    std::string baoCaoDoanhThu() const;
    std::string xemThongTin() const override;
     void themDonHang(const DonHang& don) { danhSachDonHang_.push_back(don); }
};

#endif
