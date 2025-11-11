#ifndef NHANVIENBEP_H
#define NHANVIENBEP_H

#include "User.h"
#include "DonHang.h"
#include <string>
#include <sstream>
#include <vector>

// Forward declaration
class KitchenService;

class NhanVienBep : public User {
private:
    std::string maBep_;
    std::string khuVucPhuTrach_;
    double luong_{};
    bool dangLamViec_{false};
    std::vector<DonHang> danhSachDon_;

public:
    NhanVienBep() = default;
    NhanVienBep(std::string ma, std::string ten, std::string sdt, std::string gt,
                std::string khuVuc, double luong);
    // Constructor cho việc đăng ký
    NhanVienBep(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt,
                std::string khuVuc, double luong);

    // Getter
    const std::string& getMaBep() const { return maBep_; }
    const std::string& getKhuVuc() const { return khuVucPhuTrach_; }
    double getLuong() const { return luong_; }

    // Setter
    void setLuong(double l) { luong_ = l; }

    // Nghiệp vụ
    void capNhatTrangThaiDon(DonHang& don, const std::string& trangThai);
    void capNhatTrangThaiMon(DonHang& don, const std::string& tenMon, std::string trangthaiMon);
    void batDauLam() { dangLamViec_ = true; }
    void ketThucLam() { dangLamViec_ = false; }

    // Ủy thác cho KitchenService
    void xemDonHangCanChuanBi(KitchenService* kitchenService) const;
    void hoanThanhDon(int idDon, KitchenService* kitchenService);
    void xemLichSuDon(KitchenService* kitchenService) const;

    std::string xemDanhSachDon() const;
    std::string toJSON() const;
};

#endif
