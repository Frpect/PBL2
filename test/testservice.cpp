#include <iostream>
#include "../services/AuthService.h"
#include "../services/MenuService.h"
#include "../services/OrderService.h"
#include "../services/ReportService.h"

int main() {
    std::cout << "=== CHUONG TRINH KIEM THU HE THONG QUAN LY ===\n\n";

    // 1. Kiểm thử AuthService
    AuthService auth;
    std::cout << "[AuthService] Dang ky nguoi dung...\n";
    auth.registerUser("admin", "123456");
    auth.registerUser("user1", "1111");

    std::cout << "[AuthService] Dang nhap voi tai khoan admin...\n";
    if (auth.login("admin", "123456"))
        std::cout << "Dang nhap thanh cong!\n";
    else
        std::cout << "Dang nhap that bai!\n";

    // 2. Kiểm thử MenuService
    MenuService menu;
    std::cout << "\n[MenuService] Them mon an vao menu...\n";
    menu.themMon("Com rang", 30000, "Com rang trung");
    menu.themMon("Pho bo", 40000, "Pho bo tai chin");
    menu.themMon("Bun cha", 35000, "Bun cha Ha Noi");

    std::cout << "Danh sach mon trong menu:\n";
    for (auto& mon : menu.getDanhSachMon()) {
        std::cout << "- ID " << mon.id << ": " << mon.tenMon 
                  << " (" << mon.gia << " VND)\n";
    }

    // 3. Kiểm thử OrderService
    OrderService order;
    std::cout << "\n[OrderService] Tao don hang moi...\n";
    int idDon1 = order.taoDonHang("Nguyen Van A");
    int idDon2 = order.taoDonHang("Tran Thi B");

    // Lấy danh sách món từ menu để thêm vào đơn hàng
    auto danhSachMon = menu.getDanhSachMon();

    order.themMonVaoDon(idDon1, &danhSachMon[0], 2); // 2 phần cơm rang
    order.themMonVaoDon(idDon1, &danhSachMon[2], 1); // 1 phần bún chả
    order.capNhatTrangThai(idDon1, "Hoan tat");

    order.themMonVaoDon(idDon2, &danhSachMon[1], 3); // 3 tô phở bò
    order.capNhatTrangThai(idDon2, "Dang xu ly");

    std::cout << "\nDanh sach don hang:\n";
    for (const auto& thongTinDon : order.getDanhSachThongTinDonHang()) {
        std::cout << thongTinDon << "\n";
    }

    // 4. Kiểm thử ReportService
    ReportService report;
    std::cout << "\n[ReportService] Tao bao cao tong hop...\n";
    std::string baoCao = report.taoBaoCaoTongHop(order.getDanhSachDonHang());
    std::cout << baoCao << "\n";

    std::cout << "=== KET THUC KIEM THU ===\n";
    return 0;
}