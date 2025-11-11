#include "PhucVu.h"
#include "OrderService.h"
#include "TableService.h"
#include <sstream>
#include "ReportService.h"
#include <iostream>
#include <algorithm>

PhucVu::PhucVu(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string ca, double luong)
    : NhanSu(username, // Dùng username làm mã nhân viên
             hoTen,
             sdt,
             gt, username, password, luong, ca)
{
}

void PhucVu::taoDonHang(const DonHang& dh) {
    danhSachDon_.push_back(dh);
}

void PhucVu::guiOrderXuongBep(const std::string& maDon, OrderService* orderService) {
    // Nếu có OrderService, sử dụng service để cập nhật trạng thái
    if (orderService) {
        // Tìm ID đơn hàng từ mã đơn (format: "DH123" -> 123)
        std::string idStr = maDon;
        if (maDon.length() > 2 && maDon.substr(0, 2) == "DH") {
            idStr = maDon.substr(2);
        }
        try {
            int id = std::stoi(idStr);
            orderService->capNhatTrangThai(id, "Đang chuẩn bị");
        } catch (...) {
            // Nếu không parse được, fallback về cách cũ
        }
    }
    // Vẫn cập nhật trong danh sách local (backward compatibility)
    for (auto& d : danhSachDon_) {
        if (d.getMaDonHang() == maDon)
            d.capNhatTrangThai("Đang chuẩn bị");
    }
}

void PhucVu::hienThiSoDoBan(TableService* tableService) const {
    if (tableService) {
        tableService->hienThiSoDoBan();
    }
}

void PhucVu::capNhatTrangThaiBan(const std::string& maBan, const std::string& trangThaiMoi, TableService* tableService) {
    if (tableService) {
        tableService->capNhatTrangThaiBan(maBan, trangThaiMoi);
    }
}

void PhucVu::xemLichSuGiaoDich(ReportService* reportService, OrderService* orderService) const {
    if (reportService && orderService) {
        auto danhSachDon = orderService->getDanhSachDonHang();
        std::string baoCao = reportService->taoBaoCaoTongHop(danhSachDon);
        std::cout << baoCao;
    }
}

void PhucVu::xuLyThanhToan(int idDon, const std::string& phuongThuc, OrderService* orderService) {
    if (orderService) {
        if (orderService->capNhatTrangThai(idDon, "Da thanh toan")) {
            orderService->capNhatPhuongThucThanhToan(idDon, phuongThuc);
            std::cout << "Da xu ly thanh toan cho don hang #" << idDon << ".\n";
        } else {
            std::cout << "Xu ly thanh toan that bai. Don hang khong ton tai hoac trang thai khong hop le.\n";
        }
    }
}

std::string PhucVu::xemThongTin() const {
    std::ostringstream os;
    os << NhanSu::xemThongTin() << "\nSo don dang phu trach: " << danhSachDon_.size();
    return os.str();
}
std::string PhucVu::inHoaDon(const std::string& maDon) const {
    for (const auto& d : danhSachDon_) {
        if (d.getMaDonHang() == maDon) {
            std::ostringstream os;
            os << "===== HOA DON =====\n";
            os << d.xemChiTiet();
            os << "Tong tien: " << d.tinhTongTien() << " VND\n";
            os << "===================\n";
            return os.str();
        }
    }
    return "Khong tim thay don hang.\n";
}