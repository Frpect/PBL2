#include <iostream>
#include "../models/Ban.h"
#include "../models/KhachHang.h"
#include "../models/PhucVu.h"
#include "../models/NhanVienBep.h"
#include "../models/QuanLy.h"
#include "../models/MonAn.h"
#include "../models/DonHang.h"

using namespace std;

int main() {
    cout << "===== KHOI TAO DU LIEU MẪU =====\n\n";

    // Tạo vài món ăn
    MonAn mon1("M001", "Com chien","Chinh",40000,1);
    MonAn mon2("M002", "Pepsi","Nuoc uong",12000,2);
    MonAn mon3("M003", "Burger","An nhanh",45000,1);
    cout << mon1.xemThongTin() << "\n";
    cout << mon2.xemThongTin() << "\n";
    cout << mon3.xemThongTin() << "\n";

    // Tạo bàn
    Ban ban1("B01", "Trong");
    cout << "\nBan hien tai: ";
    ban1.capNhatTrangThai("Co khach");

    // Tạo khách hàng
    KhachHang kh("KH01", "Nguyen Van A", "0905123456", "Nam");
    cout << "\nThong tin khach hang:\n" << kh.xemThongTin() << "\n";
    cout << "\n" << kh.xemMenu() << "\n";

    // Tạo nhân sự
    PhucVu pv("NV01", "Le Thi B", "0904987654", "Nu", "Ca sang", 8000000);
    NhanVienBep nb("NV02", "Tran Van C", "0904777888", "Nam", "Ca chieu", 9000000);
    QuanLy ql("QL01", "Pham D", "0904111222", "Nam", "Ca ngay", 15000000);

    cout << "\nThong tin phuc vu:\n" << pv.xemThongTin() << "\n";
    cout << "\nThong tin nhan vien bep:\n" << nb.xemThongTin() << "\n";
    cout << "\nThong tin quan ly:\n" << ql.xemThongTin() << "\n";

    // Tạo đơn hàng
    DonHang don("D001", kh.getHoTen(), pv.getMaNhanVien());
    don.themMon({mon1.getTenMon(),mon1.getGia(),1});
    don.themMon({mon2.getTenMon(),mon2.getGia(),2});
    don.themMon({mon3.getTenMon(),mon3.getGia(),1});

    cout << "\n===== DON HANG =====\n";
    cout << don.xemChiTiet() << "\n";

    cout << "Tong tien don hang: " << don.tinhTongTien() << " VND\n";

    // Cập nhật trạng thái
    don.capNhatTrangThai("Dang che bien");

    cout << "\n===== KHACH HANG THANH TOAN =====\n";
    kh.thanhToan(don);

    // Phục vụ in hóa đơn
    pv.inHoaDon("D001");

    // Quản lý báo cáo
    cout << "\n===== QUAN LY BAO CAO =====\n";
    ql.baoCaoDoanhThu();

    cout << "\n===== KET THUC KIEM TRA =====\n";
    return 0;
}
