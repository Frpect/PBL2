#include "QuanLy.h"
#include "MenuService.h"
#include "ReportService.h"
#include <algorithm>
#include <sstream>
using namespace std;

QuanLy::QuanLy(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string ca, double luong)
    : NhanSu(username, // Dùng username làm mã nhân viên
             hoTen,
             sdt,
             gt, username, password, luong, ca)
{
}

void QuanLy::themMon(const MonAn& mon, MenuService* menuService) {
    // Nếu có MenuService, sử dụng service để thêm món
    if (menuService) {
        menuService->themMon(mon.getTenMon(), mon.getGia(), "");
    }
    // Vẫn lưu vào danh sách local (backward compatibility)
    danhSachMon_.push_back(mon);
}

void QuanLy::xoaMon(const std::string& ten, MenuService* menuService) {
    // Nếu có MenuService, tìm món theo tên và xóa
    if (menuService) {
        auto danhSach = menuService->getDanhSachMon();
        for (const auto& mon : danhSach) {
            if (mon.tenMon.find(ten) != std::string::npos) {
                menuService->xoaMon(mon.id);
            }
        }
    }
    // Vẫn xóa trong danh sách local (backward compatibility)
    danhSachMon_.erase(std::remove_if(danhSachMon_.begin(), danhSachMon_.end(),
        [&](const MonAn& m){ return m.xemThongTin().find(ten) != std::string::npos; }),
        danhSachMon_.end());
}

std::string QuanLy::baoCaoDoanhThu(ReportService* reportService) const {
    // Nếu có ReportService, sử dụng service để tạo báo cáo
    if (reportService) {
        return reportService->taoBaoCaoTongHop(danhSachDonHang_);
    }
    // Nếu không có service, tính toán trực tiếp (backward compatibility)
    double tongDoanhThu = 0;
    for (const auto& don : danhSachDonHang_) {
        if (don.getTrangThai() == "da thanh toan") {
            tongDoanhThu += don.tinhTongTien();
        }
    }
    std::ostringstream os;
    os << "Tong doanh thu: " << tongDoanhThu << " VND\n";
    return os.str();
}
std::string QuanLy::xemThongTin() const {
    std::ostringstream os;
    os << NhanSu::xemThongTin() << "\nChuc vu: Quan ly";
    return os.str();
}
