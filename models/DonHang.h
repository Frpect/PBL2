#ifndef DONHANG_H
#define DONHANG_H

#include <string>
#include <vector>
#include <sstream>

struct MonGoi {
    std::string tenMon;
    double gia;
    int soLuong;
    std::string trangThai;
};

class DonHang {
private:
    std::string maDon_;
    std::string maBan_;
    std::string maNhanVien_;
    std::string trangThai_;
    std::vector<MonGoi> danhSachMon_;

public:
    DonHang() = default;
    DonHang(std::string maDon, std::string maBan, std::string maNV);

    void themMon(const MonGoi& mon);
    double tinhTongTien() const;
    void capNhatTrangThai(const std::string& tt);
    const std::string& getTrangThai() const;
    std::string xemChiTiet() const;
    std::string danhSachDonHang() const;
    const std::string& getMaDonHang() const;
    const std::vector<MonGoi>& getDanhSachMon() const;
};

#endif
