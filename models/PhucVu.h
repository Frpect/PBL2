#ifndef PHUCVU_H
#define PHUCVU_H

#include "NhanSu.h"
#include "DonHang.h"
#include <vector>

// Forward declaration
class OrderService;
class ReportService;
class TableService;

class PhucVu : public NhanSu {
private:
    std::vector<DonHang> danhSachDon_;

public:
    PhucVu() = default;
    // Constructor tiện lợi để tạo PhucVu từ thông tin đăng ký
    PhucVu(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string ca, double luong);

    void taoDonHang(const DonHang& dh);
    // Sử dụng OrderService nếu có
    void guiOrderXuongBep(const std::string& maDon, OrderService* orderService = nullptr);
    std::string xemThongTin() const override;

    // Ủy thác cho các service khác
    void hienThiSoDoBan(TableService* tableService) const;
    void capNhatTrangThaiBan(const std::string& maBan, const std::string& trangThaiMoi, TableService* tableService);
    void xemLichSuGiaoDich(ReportService* reportService, OrderService* orderService) const;
    void xuLyThanhToan(int idDon, const std::string& phuongThuc, OrderService* orderService);

    std::string inHoaDon(const std::string& maDon) const;
};

#endif
