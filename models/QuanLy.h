#ifndef QUANLY_H
#define QUANLY_H

#include "NhanSu.h"
#include "MonAn.h"
#include "DonHang.h"
#include <vector>

// Forward declarations
class MenuService;
class ReportService;
class OrderService;
class AuthService;
class TableService;

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
    
    // Sử dụng TableService nếu có
    void themBan(const std::string& maBan, TableService* tableService = nullptr);
    void capNhatTrangThaiBan(const std::string& maBan, const std::string& trangThaiMoi, TableService* tableService = nullptr);
    void hienThiSoDoBan(TableService* tableService = nullptr) const;

    // Sử dụng ReportService nếu có
    std::string baoCaoDoanhThu(ReportService* reportService = nullptr) const;
    void xemDoanhThuTheoThoiGian(ReportService* reportService, OrderService* orderService) const;

    // Sử dụng AuthService để quản lý nhân sự
    void xemDanhSachNhanVien(AuthService* authService) const;
    void themNhanVien(AuthService* authService);
    void xoaNhanVien(AuthService* authService);
    
    std::string xemThongTin() const override;
    void themDonHang(const DonHang& don) { danhSachDonHang_.push_back(don); }
};

#endif
