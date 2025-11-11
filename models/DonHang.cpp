#include "DonHang.h"
#include <iomanip>
DonHang::DonHang(std::string maDon, std::string maBan, std::string maNV)
    : maDon_(std::move(maDon)), maBan_(std::move(maBan)), maNhanVien_(std::move(maNV)), trangThai_("Moi tao"), phuongThucThanhToan_("Chua thanh toan"), ngayTao_(std::chrono::system_clock::now()) {}

void DonHang::themMon(const MonGoi& mon) {
    danhSachMon_.push_back(mon);
}
double DonHang::tinhTongTien() const {
    double tong = 0.0;
    for (const auto& mg : danhSachMon_) {
        tong += mg.gia * mg.soLuong;
    }
    return tong;
}

void DonHang::capNhatTrangThai(const std::string& tt) {
    trangThai_ = tt;
}
const std::string& DonHang::getTrangThai() const {
    return trangThai_;
}
std::string DonHang::xemChiTiet() const {
    std::ostringstream os;
    auto thoiGianTao = std::chrono::system_clock::to_time_t(ngayTao_);
    os << "Don hang: " << maDon_ << " - Trang thai: " << trangThai_ << "\n";
    os << "Phuong thuc thanh toan: " << phuongThucThanhToan_ << "\n";
    os << "Thoi gian tao: " << std::put_time(std::localtime(&thoiGianTao), "%Y-%m-%d %H:%M:%S") << "\n";
    for (const auto& m : danhSachMon_)
        os << "- " << m.tenMon << " x" << m.soLuong << " = " << m.gia * m.soLuong << " VND\n";
    return os.str();
}

const std::string& DonHang::getMaDonHang() const { return maDon_; }

const std::chrono::system_clock::time_point& DonHang::getNgayTao() const {
    return ngayTao_;
}

void DonHang::setPhuongThucThanhToan(const std::string& phuongThuc) {
    phuongThucThanhToan_ = phuongThuc;
}

void DonHang::setNgayThanhToan(const std::chrono::system_clock::time_point& time) {
    ngayThanhToan_ = time;
}

const std::vector<MonGoi>& DonHang::getDanhSachMon() const { return danhSachMon_; }
std:: string DonHang::danhSachDonHang() const{
    std::ostringstream os;
    os<< "Don hang: " << maDon_ << " - Trang thai: " << trangThai_ << "\n";
    return os.str();
}
