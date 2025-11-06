#include "OrderService.h"
#include "MenuService.h" // định nghĩa struct Mon
#include <algorithm>
#include <sstream>

OrderService::OrderService() : nextId(1) {}

int OrderService::taoDonHang(const std::string& tenKhachHang) {
    DonHang donHang;
    donHang.id = nextId++;
    donHang.tenKhachHang = tenKhachHang;
    donHang.tongTien = 0.0;
    donHang.trangThai = "Chờ xử lý";
    danhSachDonHang.push_back(donHang);
    return donHang.id;
}

bool OrderService::themMonVaoDon(int idDonHang, Mon* mon, int soLuong) {
    auto it = std::find_if(danhSachDonHang.begin(), danhSachDonHang.end(),
                           [idDonHang](const DonHang& d) { return d.id == idDonHang; });
    if (it == danhSachDonHang.end() || !mon || soLuong <= 0)
        return false;

    for (auto& mg : it->danhSachMon) {
        if (mg.mon && mg.mon->id == mon->id) {
            mg.soLuong += soLuong;
            it->tongTien = tinhTongTien(*it);
            return true;
        }
    }

    it->danhSachMon.push_back({mon, soLuong});
    it->tongTien = tinhTongTien(*it);
    return true;
}

bool OrderService::xoaMonKhoiDon(int idDonHang, int idMon) {
    auto it = std::find_if(danhSachDonHang.begin(), danhSachDonHang.end(),
                           [idDonHang](const DonHang& d) { return d.id == idDonHang; });
    if (it == danhSachDonHang.end())
        return false;

    auto& dsMon = it->danhSachMon;
    dsMon.erase(std::remove_if(dsMon.begin(), dsMon.end(),
                               [idMon](const OrderItem& mg) { return mg.mon && mg.mon->id == idMon; }),
                dsMon.end());

    it->tongTien = tinhTongTien(*it);
    return true;
}

bool OrderService::capNhatSoLuong(int idDonHang, int idMon, int soLuongMoi) {
    auto it = std::find_if(danhSachDonHang.begin(), danhSachDonHang.end(),
                           [idDonHang](const DonHang& d) { return d.id == idDonHang; });
    if (it == danhSachDonHang.end())
        return false;

    for (auto& mg : it->danhSachMon) {
        if (mg.mon && mg.mon->id == idMon) {
            mg.soLuong = soLuongMoi;
            it->tongTien = tinhTongTien(*it);
            return true;
        }
    }
    return false;
}

bool OrderService::capNhatTrangThai(int idDonHang, const std::string& trangThaiMoi) {
    auto it = std::find_if(danhSachDonHang.begin(), danhSachDonHang.end(),
                           [idDonHang](const DonHang& d) { return d.id == idDonHang; });
    if (it == danhSachDonHang.end())
        return false;

    it->trangThai = trangThaiMoi;
    return true;
}

std::vector<std::string> OrderService::getDanhSachThongTinDonHang() const {
    std::vector<std::string> dsThongTin;
    for (const auto& d : danhSachDonHang) {
        std::ostringstream oss;
        oss << "Đơn #" << d.id << " - Khách: " << d.tenKhachHang
            << " | Tổng: " << d.tongTien
            << " | Trạng thái: " << d.trangThai;
        dsThongTin.push_back(oss.str());
    }
    return dsThongTin;
}

std::optional<int> OrderService::timDonHangTheoId(const std::string& tenKhach) const {
    for (const auto& d : danhSachDonHang)
        if (d.tenKhachHang == tenKhach)
            return d.id;
    return std::nullopt;
}

bool OrderService::xoaDonHang(int idDonHang) {
    auto sizeTruoc = danhSachDonHang.size();
    danhSachDonHang.erase(std::remove_if(danhSachDonHang.begin(), danhSachDonHang.end(),
                                         [idDonHang](const DonHang& d) { return d.id == idDonHang; }),
                          danhSachDonHang.end());
    return sizeTruoc != danhSachDonHang.size();
}

void OrderService::clear() {
    danhSachDonHang.clear();
    nextId = 1;
}

double OrderService::tinhTongTien(const DonHang& donHang) const {
    double tong = 0.0;
    for (const auto& mg : donHang.danhSachMon) {
        if (mg.mon)
            tong += mg.mon->gia * mg.soLuong;
    }
    return tong;
}
::DonHang OrderService::chuyenDoi(const DonHang& don) const {
    std::ostringstream oss;
    oss << "DH" << don.id;  // Chuyển id thành string, thêm prefix "DH"
    ::DonHang ketQua(oss.str(), std::to_string(don.id), "");
    ketQua.capNhatTrangThai(don.trangThai);
    
    for (const auto& item : don.danhSachMon) {
        if (item.mon) {
            MonGoi mg;
            mg.tenMon = item.mon->tenMon;
            mg.gia = item.mon->gia;
            mg.soLuong = item.soLuong;
            ketQua.themMon(mg);
        }
    }
    
    return ketQua;
}

std::vector<::DonHang> OrderService::getDanhSachDonHang() const {
    std::vector<::DonHang> ketQua;
    for (const auto& don : danhSachDonHang) {
        ketQua.push_back(chuyenDoi(don));
    }
    return ketQua;
}