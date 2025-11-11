#include "QuanLy.h"
#include "MenuService.h"
#include "TableService.h"
#include "ReportService.h"
#include "AuthService.h"
#include "OrderService.h"
#include "Input.h"
#include "PhucVu.h"
#include "NhanVienBep.h"
#include <algorithm>
#include <sstream>
using namespace std;
#include <iostream>

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

void QuanLy::themBan(const std::string& maBan, TableService* tableService) {
    if (tableService) {
        tableService->themBan(maBan);
    }
}

void QuanLy::capNhatTrangThaiBan(const std::string& maBan, const std::string& trangThaiMoi, TableService* tableService) {
    if (tableService) {
        tableService->capNhatTrangThaiBan(maBan, trangThaiMoi);
    }
}

void QuanLy::hienThiSoDoBan(TableService* tableService) const {
    if (tableService) {
        tableService->hienThiSoDoBan();
    }
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

void QuanLy::xemDoanhThuTheoThoiGian(ReportService* reportService, OrderService* orderService) const {
    if (!reportService || !orderService) return;

    cout << "Chon loai bao cao:\n1. Theo ngay\n2. Theo thang\n3. Theo nam\n";
    int choice = Input::readInt("Chon: ", 1, 3);

    time_t now = time(0);
    tm* ltm = localtime(&now);

    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    if (choice == 1) { // Theo ngày
        year = Input::readInt("Nhap nam: ", 2000, 2100);
        month = Input::readInt("Nhap thang: ", 1, 12);
        day = Input::readInt("Nhap ngay: ", 1, 31);
    } else if (choice == 2) { // Theo tháng
        year = Input::readInt("Nhap nam: ", 2000, 2100);
        month = Input::readInt("Nhap thang: ", 1, 12);
        day = 1; // Bắt đầu từ ngày 1
    } else { // Theo năm
        year = Input::readInt("Nhap nam: ", 2000, 2100);
        month = 1;
        day = 1;
    }

    tm startTimeInfo = {0};
    startTimeInfo.tm_year = year - 1900;
    startTimeInfo.tm_mon = month - 1;
    startTimeInfo.tm_mday = day;
    auto start = chrono::system_clock::from_time_t(mktime(&startTimeInfo));

    tm endTimeInfo = startTimeInfo;
    if (choice == 1) { // 1 ngày
        endTimeInfo.tm_mday += 1;
    } else if (choice == 2) { // 1 tháng
        endTimeInfo.tm_mon += 1;
    } else { // 1 năm
        endTimeInfo.tm_year += 1;
    }
    auto end = chrono::system_clock::from_time_t(mktime(&endTimeInfo));

    cout << reportService->taoBaoCaoDoanhThuTheoThoiGian(orderService->getDanhSachDonHang(), start, end);
}

void QuanLy::xemDanhSachNhanVien(AuthService* authService) const {
    if (!authService) return;
    cout << "\n--- DANH SACH NHAN SU ---\n";
    for (const auto* user : authService->getAllUsers()) {
        cout << user->xemThongTin() << "\n--------------------\n";
    }
}

void QuanLy::themNhanVien(AuthService* authService) {
    if (!authService) return;
    cout << "Chon loai nhan vien:\n1. Phuc Vu\n2. Nhan Vien Bep\n";
    int type = Input::readInt("Chon: ", 1, 2);
    string username = Input::readString("Nhap ten dang nhap: ");
    string password = Input::readString("Nhap mat khau: ");
    string ten = Input::readString("Nhap ho ten: ");
    string sdt = Input::readString("Nhap so dien thoai: ");
    string gt = Input::readString("Nhap gioi tinh: ");
    double luong = Input::readDouble("Nhap luong: ", 0, 1e9);

    if (type == 1) authService->registerUser(make_unique<PhucVu>(username, password, ten, sdt, gt, "Ca mac dinh", luong));
    else authService->registerUser(make_unique<NhanVienBep>(username, password, ten, sdt, gt, "Bep chinh", luong));
}

std::string QuanLy::xemThongTin() const {
    std::ostringstream os;
    os << NhanSu::xemThongTin() << "\nChuc vu: Quan ly";
    return os.str();
}
