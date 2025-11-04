#include "NhanVienBep.h"
#include <utility>

NhanVienBep::NhanVienBep(std::string ma, std::string ten, std::string sdt, std::string gt,
                         std::string khuVuc, double luong)
    : User(std::move(ten), std::move(sdt), std::move(gt)),
      maBep_(std::move(ma)), khuVucPhuTrach_(std::move(khuVuc)), luong_(luong) {}

void NhanVienBep::capNhatTrangThaiDon(DonHang& don, const std::string& trangThai) {
    don.capNhatTrangThai(trangThai);
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
