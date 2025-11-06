#include "ReportService.h"
#include <sstream>
#include <iomanip>

ReportService::ReportService() {}

// ---------------------------------------------

double ReportService::tinhTongDoanhThu(const std::vector<DonHang>& danhSachDon) const {
    double tong = 0.0;
    for (const auto& don : danhSachDon) {
        tong += don.tinhTongTien(); // giả sử DonHang có hàm này
        // Nếu DonHang không có tinhTongTien(), thì có thể tính trực tiếp:
        // for (auto& mg : don.getDanhSachMon()) tong += mg.mon->gia * mg.soLuong;
    }
    return tong;
}

// ---------------------------------------------

std::map<std::string, int> ReportService::thongKeTheoTrangThai(const std::vector<DonHang>& danhSachDon) const {
    std::map<std::string, int> ketQua;
    for (const auto& don : danhSachDon) {
        ketQua[don.getTrangThai()]++;
    }
    return ketQua;
}

// ---------------------------------------------

std::map<std::string, int> ReportService::thongKeMonBanChay(const std::vector<DonHang>& danhSachDon) const {
    std::map<std::string, int> thongKe;
    for (const auto& don : danhSachDon) {
        for (const auto& mg : don.getDanhSachMon()) {
            // MonGoi::tenMon is a std::string (name). Aggregate by name.
            thongKe[mg.tenMon] += mg.soLuong;
        }
    }
    return thongKe;
}

// ---------------------------------------------

std::string ReportService::taoBaoCaoTongHop(const std::vector<DonHang>& danhSachDon) const {
    std::ostringstream oss;
    oss << "===== BÁO CÁO TỔNG HỢP =====\n";

    double tongDoanhThu = tinhTongDoanhThu(danhSachDon);
    auto thongKeTT = thongKeTheoTrangThai(danhSachDon);
    auto thongKeMon = thongKeMonBanChay(danhSachDon);

    oss << "\n--- Doanh thu ---\n";
    oss << "Tổng doanh thu: " << std::fixed << std::setprecision(2) << tongDoanhThu << " VND\n";

    oss << "\n--- Đơn hàng theo trạng thái ---\n";
    for (auto& [trangThai, soLuong] : thongKeTT) {
        oss << trangThai << ": " << soLuong << " đơn\n";
    }

    oss << "\n--- Món bán chạy ---\n";
    for (auto& [tenMon, tongSoLuong] : thongKeMon) {
        oss << tenMon << ": " << tongSoLuong << " phần\n";
    }

    oss << "===============================\n";
    return oss.str();
}
