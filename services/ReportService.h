#ifndef REPORTSERVICE_H
#define REPORTSERVICE_H

#include <string>
#include <vector>
#include <map>
// DonHang is defined in ../models/DonHang.h
#include "../models/DonHang.h"

class ReportService {
public:
    ReportService();

    // Tính tổng doanh thu từ tất cả đơn hàng
    double tinhTongDoanhThu(const std::vector<DonHang>& danhSachDon) const;

    // Đếm tổng số đơn hàng theo trạng thái (VD: "Hoàn tất", "Đang xử lý", "Đã hủy")
    std::map<std::string, int> thongKeTheoTrangThai(const std::vector<DonHang>& danhSachDon) const;

    // Thống kê số lượng món bán ra (tenMon -> tổng số lượng)
    std::map<std::string, int> thongKeMonBanChay(const std::vector<DonHang>& danhSachDon) const;

    // Xuất báo cáo tổng hợp (chuỗi mô tả)
    std::string taoBaoCaoTongHop(const std::vector<DonHang>& danhSachDon) const;
};

#endif // REPORTSERVICE_H
