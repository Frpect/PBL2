#include "NhanVienBep.h"
#include "KitchenService.h"
#include <iostream>
#include <utility>

NhanVienBep::NhanVienBep(std::string ma, std::string ten, std::string sdt, std::string gt,
                         std::string khuVuc, double luong)
    : User(std::move(ten), std::move(sdt), std::move(gt)),
      maBep_(std::move(ma)), khuVucPhuTrach_(std::move(khuVuc)), luong_(luong) {
          this->role = Role::NHAN_VIEN; // Nhân viên bếp cũng là một NHAN_VIEN
      }

NhanVienBep::NhanVienBep(std::string username, std::string password, std::string hoTen, std::string sdt, std::string gt, std::string khuVuc, double luong)
    : User(username, password, hoTen, sdt, gt, Role::NHAN_VIEN),
      maBep_(username), khuVucPhuTrach_(std::move(khuVuc)), luong_(luong) {}

void NhanVienBep::capNhatTrangThaiDon(DonHang& don, const std::string& trangThai) {
    don.capNhatTrangThai(trangThai);
}

void NhanVienBep::xemDonHangCanChuanBi(KitchenService* kitchenService) const {
    if (!kitchenService) return;
    auto orders = kitchenService->getDonHangCanChuanBi();
    std::cout << "\n--- CAC DON HANG CAN CHUAN BI ---\n";
    if (orders.empty()) {
        std::cout << "Khong co don hang nao can chuan bi.\n";
        return;
    }
    for (const auto& don : orders) {
        std::cout << don.xemChiTiet() << "--------------------\n";
    }
}

void NhanVienBep::hoanThanhDon(int idDon, KitchenService* kitchenService) {
    if (!kitchenService) return;
    if (kitchenService->hoanThanhDon(idDon)) {
        std::cout << "Da cap nhat don hang #" << idDon << " thanh 'Da hoan thanh'.\n";
    } else {
        std::cout << "Khong tim thay hoac khong the cap nhat don hang #" << idDon << ".\n";
    }
}

void NhanVienBep::xemLichSuDon(KitchenService* kitchenService) const {
    if (!kitchenService) return;
    auto orders = kitchenService->getLichSuDonHoanThanh();
    std::cout << "\n--- LICH SU DON HANG DA HOAN THANH ---\n";
    if (orders.empty()) {
        std::cout << "Chua co don hang nao duoc hoan thanh.\n";
        return;
    }
    for (const auto& don : orders) {
        std::cout << don.xemChiTiet() << "--------------------\n";
    }
}

std::string NhanVienBep::xemDanhSachDon() const {
    std::ostringstream os;
    os << "Don hang phu trach (" << danhSachDon_.size() << "):\n";
    for (const auto& d : danhSachDon_) {
        os << "- " << d.getMaDonHang() << "\n";
        // Nếu lớp DonHang có phương thức lấy trạng thái (ví dụ: getTrangThaiDon() hoặc layTrangThai()),
        // thay dòng trên bằng: os << "- " << d.getMaDonHang() << " (" << d.getTrangThaiDon() << ")\n";
    }
    return os.str();
}

std::string NhanVienBep::toJSON() const {
    std::ostringstream os;
    os << "{"
       << "\"maBep\":\"" << maBep_ << "\","
       << "\"khuVuc\":\"" << khuVucPhuTrach_ << "\","
       << "\"luong\":" << luong_ << "}";
    return os.str();
}
