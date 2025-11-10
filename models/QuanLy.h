#ifndef QUANLY_H
#define QUANLY_H

#include "NhanSu.h"
#include "MonAn.h"
#include "DonHang.h"
#include <vector>

// Forward declarations
class MenuService;
class ReportService;

class QuanLy : public NhanSu {
private:
    std::vector<MonAn> danhSachMon_;
    std::vector<DonHang> danhSachDonHang_;
public:
    QuanLy() = default;
    // Constructor tiện lợi để tạo QuanLy từ thông tin đăng ký
    QuanLy(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string ca, double luong);

    // Sử dụng MenuService nếu có
    void themMon(const MonAn& mon, MenuService* menuService = nullptr);
    void xoaMon(const std::string& ten, MenuService* menuService = nullptr);
    
    // Sử dụng ReportService nếu có
    std::string baoCaoDoanhThu(ReportService* reportService = nullptr) const;
    
    std::string xemThongTin() const override;
    void themDonHang(const DonHang& don) { danhSachDonHang_.push_back(don); }
};

#endif
