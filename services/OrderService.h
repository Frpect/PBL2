#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include "../models/DonHang.h"  // Thêm include để chuyển đổi

// Forward declare Mon (được định nghĩa trong MenuService.h)
struct Mon;

class OrderService {
private:
    // Local order item uses pointer to Menu's Mon for lightweight reference
    struct OrderItem {
        Mon* mon; // pointer to MenuService::Mon (not owned)
        int soLuong;
    };

    // Local DonHang for OrderService (distinct from models::DonHang)
    struct DonHang {
        int id;
        std::string tenKhachHang;
        std::vector<OrderItem> danhSachMon;
        double tongTien;
        std::string trangThai;
    };

    std::vector<DonHang> danhSachDonHang;
    int nextId;

    double tinhTongTien(const DonHang& donHang) const;
    
    // Helper để chuyển đổi sang models::DonHang
    ::DonHang chuyenDoi(const DonHang& don) const;

public:
    OrderService();

    int taoDonHang(const std::string& tenKhachHang);
    bool themMonVaoDon(int idDonHang, Mon* mon, int soLuong);
    bool xoaMonKhoiDon(int idDonHang, int idMon);
    bool capNhatSoLuong(int idDonHang, int idMon, int soLuongMoi);
    bool capNhatTrangThai(int idDonHang, const std::string& trangThaiMoi);
    std::vector<std::string> getDanhSachThongTinDonHang() const;
    std::optional<int> timDonHangTheoId(const std::string& tenKhach) const;
    bool xoaDonHang(int idDonHang);
    ::DonHang layDonHang(int id) const;
    void clear();

    // Giải phóng bộ nhớ cache
    void clearCache();

    // Thêm getter trả về vector của models::DonHang
    std::vector<::DonHang> getDanhSachDonHang() const;
};

#endif // ORDERSERVICE_H
