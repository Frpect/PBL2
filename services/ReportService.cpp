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
    oss << "===== BAO CAO TONG HOP =====\n";

    double tongDoanhThu = tinhTongDoanhThu(danhSachDon);
    auto thongKeTT = thongKeTheoTrangThai(danhSachDon);
    auto thongKeMon = thongKeMonBanChay(danhSachDon);

    oss << "\n--- Doanh thu ---\n";
    oss << "Tong doanh thu: " << std::fixed << std::setprecision(2) << tongDoanhThu << " VND\n";

    oss << "\n--- Don hang theo trang thai ---\n";
    for (auto& [trangThai, soLuong] : thongKeTT) {
        oss << trangThai << ": " << soLuong << " đơn\n";
    }

    oss << "\n--- Mon ban chay ---\n";
    for (auto& [tenMon, tongSoLuong] : thongKeMon) {
        oss << tenMon << ": " << tongSoLuong << " phần\n";
    }

    oss << "===============================\n";
    return oss.str();
}

std::string ReportService::taoBaoCaoDoanhThuTheoThoiGian(const std::vector<DonHang>& danhSachDon, const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end) const {
    std::ostringstream oss;
    double tongDoanhThu = 0.0;
    int soDon = 0;

    for (const auto& don : danhSachDon) {
        // Chỉ tính các đơn đã thanh toán và nằm trong khoảng thời gian
        if (don.getTrangThai() == "Da thanh toan" && don.getNgayTao() >= start && don.getNgayTao() <= end) {
            tongDoanhThu += don.tinhTongTien();
            soDon++;
        }
    }

    oss << "\n--- BAO CAO DOANH THU ---\n";
    auto startTime_t = std::chrono::system_clock::to_time_t(start);
    auto endTime_t = std::chrono::system_clock::to_time_t(end);
    oss << "Tu: " << std::put_time(std::localtime(&startTime_t), "%Y-%m-%d") << "\n";
    oss << "Den: " << std::put_time(std::localtime(&endTime_t), "%Y-%m-%d") << "\n";
    oss << "-------------------------\n";
    oss << "Tong so don da thanh toan: " << soDon << "\n";
    oss << "Tong doanh thu: " << std::fixed << std::setprecision(2) << tongDoanhThu << " VND\n";
    oss << "=========================\n";
    return oss.str();
}
