#include "DonHang.h"
DonHang::DonHang(std::string maDon, std::string maBan, std::string maNV)
    : maDon_(std::move(maDon)), maBan_(std::move(maBan)), maNhanVien_(std::move(maNV)), trangThai_("Moi tao") {}

void DonHang::themMon(const MonGoi& mon) {
    danhSachMon_.push_back(mon);
}
double DonHang::tinhTongTien() const {
   double tong = 0.0;
for (const auto& mg : donHang.danhSachMon) {
    if (mg.mon)
        tong += mg.mon->gia * mg.soLuong;
}
return tong;
}

void DonHang::capNhatTrangThai(const std::string& tt) {
    trangThai_ = tt;
}
const std::string& DonHang::getTrangThai() const {
    return trangThai_;}
 std::string DonHang::xemChiTiet() const {
    std::ostringstream os;
    os << "Don hang: " << maDon_ << " - Trang thai: " << trangThai_ << "\n";
    for (const auto& m : danhSachMon_)
        os << "- " << m.tenMon << " x" << m.soLuong << " = " << m.gia * m.soLuong << " VND\n";
    return os.str();
}

const std::string& DonHang::getMaDonHang() const { return maDon_; }
const std::vector<MonGoi>& DonHang::getDanhSachMon() const { return danhSachMon_; }
std:: string DonHang::danhSachDonHang() const{
    std::ostringstream os;
    os<< "Don hang: " << maDon_ << " - Trang thai: " << trangThai_ << "\n";
    return os.str();
}
