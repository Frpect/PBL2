#ifndef NHANVIENBEP_H
#define NHANVIENBEP_H

#include "User.h"
#include "DonHang.h"
#include <string>
#include <sstream>
#include <vector>

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

    std::string xemDanhSachDon() const;
    std::string toJSON() const;
};

#endif
