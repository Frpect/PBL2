#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <vector>
#include <algorithm> // Thêm thư viện cho std::find_if
#include "Input.h"
#include "UserRepo.h"
#include "MenuRepo.h"
#include "OrderRepo.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Services
#include "AuthService.h"
#include "MenuService.h"
#include "OrderService.h"
#include "ReportService.h"
#include "KitchenService.h"
#include "TableService.h"

// Models
#include "User.h"
#include "KhachHang.h"
#include "DonHang.h"
#include "NhanSu.h"
#include "NhanVienBep.h"
#include "PhucVu.h"
#include "QuanLy.h"
#include "MonAn.h"
#include "Ban.h"

// Menu Khách hàng (dành cho khách vãng lai hoặc đã đăng nhập)
void menuKhachHang(User* user, MenuService& menu, OrderService& order) {
    KhachHang* khach = dynamic_cast<KhachHang*>(user);
    
    while (true) {
        cout << "\n===== MENU KHACH HANG =====\n";
        cout << "1. Xem thong tin khach hang\n";
        cout << "2. Xem danh sach mon\n";
        cout << "3. Tao don hang moi\n";
        cout << "4. Xem lich su don hang\n";
        cout << "0. Quay lai\n";
        int choice = Input::readInt("Chon: ", 0, 4);

        if (choice == 0) break;
        else if (choice == 1) {
            cout << "\n=== THONG TIN KHACH HANG ===\n";
            if (khach) {
                cout << khach->xemThongTin() << "\n";
            } else {
                cout << "Ban la khach vang lai.\n";
            }
        }
        else if (choice == 2) {
            cout << "\n=== DANH SACH MON ===\n";
            auto danhSachMon = menu.getDanhSachMon();
            if (danhSachMon.empty()) {
                cout << "Menu hien tai chua co mon nao.\n";
            } else {
                for (const auto& mon : danhSachMon) {
                    cout << mon.id << ". " << mon.tenMon << " - " << mon.gia << " VND\n";
                }
            }
        }
        else if (choice == 3) {
            int idDon = order.taoDonHang(khach ? khach->getHoTen() : "Khach vang lai");
            int n = Input::readInt("Nhap so mon muon goi: ", 1, 1000);

            for (int i = 0; i < n; i++) {
                if (Input::confirm("Ban co muon tim nhanh theo ten truoc khong?")) {
                    string q = Input::readString("Nhap chuoi tim: ");
                    auto ds = menu.searchMonTheoPrefix(q, 10);
                    if (ds.empty()) cout << "Khong co ket qua.\n";
                    else {
                        cout << "Goi y:\n";
                        for (const auto& m : ds) cout << m.id << " | " << m.tenMon << " | " << m.gia << "\n";
                    }
                }
                int idMon = Input::readInt("Nhap ID mon an: ", 1, 1000000);
                int sl = Input::readInt("So luong: ", 1, 1000);

                auto opt = menu.timMonTheoId(idMon);
                if (opt.has_value()) {
                    // Need a pointer for OrderService; getDanhSachMon() to find address
                    auto ds = menu.getDanhSachMon();
                    Mon* ptr = nullptr;
                    for (auto& m : ds) if (m.id == idMon) { ptr = &m; break; }
                    if (ptr) order.themMonVaoDon(idDon, ptr, sl);
                    else cout << "Khong the tham chieu mon trong danh sach.\n";
                } else {
                    cout << "ID mon an khong hop le. Bo qua.\n";
                }
            }

            ::DonHang don = order.layDonHang(idDon);
            if (khach) khach->datMon(don);

            cout << "Don hang #" << idDon << " da tao.\n";
            if (Input::confirm("Ban co muon thanh toan don hang nay luon khong?")) {
                if (khach) khach->thanhToan(don);
                cout << "Da thanh toan don hang #" << idDon 
                     << " | Tong tien: " << don.tinhTongTien() << " VND\n";
            } else {
                cout << "Don hang #" << idDon << " da luu vao lich su.\n";
            }
        }
        else if (choice == 4) {
            if (!khach) { cout << "Chuc nang nay chi danh cho khach hang da dang nhap.\n"; continue; }
            auto lichSu = khach->getLichSuDon();
            if (lichSu.empty()) cout << "Chua co don hang nao!\n";
            else {
                cout << "\n=== LICH SU DON HANG ===\n";
                for (auto& d : lichSu) {
                    cout << "Don #" << d.getMaDonHang()
                         << " | Trang thai: " << d.getTrangThai()
                         << " | Tong tien: " << d.tinhTongTien() << " VND\n";
                }
            }
        }
        else cout << "Lua chon khong hop le. Vui long thu lai!\n";
    }
}

int main() {
    // Sửa lỗi font tiếng Việt trên console Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    AuthService auth;
    MenuService menu;
    OrderService order;
    ReportService report;
    TableService tableService;
    KitchenService kitchenService(&order);

    // Storage wiring
    Repo::UserRepo userRepo(auth);
    Repo::MenuRepo menuRepo(menu);
    Repo::OrderRepo orderRepo(order);
    // Load persisted data (if any). If missing, keep sample defaults.
    bool loadedUsers = userRepo.load();
    bool loadedMenu = menuRepo.load();
    bool loadedOrders = orderRepo.load();

    // Nếu không có dữ liệu, khởi tạo mẫu
    if (!loadedMenu) {
        menu.themMon("Hamburger", 50000, "Hamburger bo pho mai");
        menu.themMon("Pizza", 120000, "Pizza hai san");
        menu.themMon("Khoai tay chien", 25000, "Khoai tay chien gion");
    }

    // Tạo tài khoản mẫu
    if (!loadedUsers) {
        auth.registerUser(make_unique<KhachHang>("khach1", "1111", "Le Van Tien", "0901112222", "Nam"));
        auth.registerUser(make_unique<PhucVu>("nv1", "2222", "Nguyen Tat Hoang", "0903334444", "Nam", "Ca sang", 8000000));
        auth.registerUser(make_unique<NhanVienBep>("bep1", "4444", "Tran Van An", "0904445555", "Nam", "Bep Chinh", 9000000));
        auth.registerUser(make_unique<QuanLy>("ql1", "3333", "Vo Minh Triet", "0905556666", "Nam", "Ca ngay", 15000000));
    }

    while (true) {
        cout << "\n===== HE THONG QUAN LY NHA HANG =====\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "3. Vao menu khach (khong can dang nhap)\n";
        cout << "0. Thoat\n";
        int choice = Input::readInt("Chon: ", 0, 3);

        if (choice == 0) break;

        else if (choice == 1) {
            string username = Input::readString("Nhap ten dang nhap: ");
            string password = Input::readString("Nhap mat khau: ");
            string ten = Input::readString("Nhap ho ten: ");
            string sdt = Input::readString("Nhap so dien thoai: ");
            string gt = Input::readString("Nhap gioi tinh: ");
            int r = Input::readInt("Chon vai tro (1: Khach hang, 2: Phuc Vu, 3: Bep, 4: Quan ly): ", 1, 4);

            bool success = false;
            if (r == 1) {
                success = auth.registerUser(make_unique<KhachHang>(username, password, ten, sdt, gt));
            } else if (r == 2) {
                success = auth.registerUser(make_unique<PhucVu>(username, password, ten, sdt, gt, "Ca mac dinh", 7000000));
            } else if (r == 3) {
                success = auth.registerUser(make_unique<NhanVienBep>(username, password, ten, sdt, gt, "Bep Chinh", 8000000));
            } else if (r == 4) {
                success = auth.registerUser(make_unique<QuanLy>(username, password, ten, sdt, gt, "Ca mac dinh", 12000000));
            }
            if (success) cout << "Dang ky thanh cong!\n";
            else
                cout << "Ten dang nhap da ton tai. Vui long chon ten khac.\n";
        }

        else if (choice == 2) {
            string username = Input::readString("Nhap ten dang nhap: ");
            string password = Input::readString("Nhap mat khau: ");

            User* user = auth.login(username, password);
            if (!user) {
                cout << "Dang nhap that bai!\n";
                continue;
            }
            cout << "Dang nhap thanh cong!\n";

            // Menu theo vai trò
            if (user->role == Role::KHACH_HANG) {
                menuKhachHang(user, menu, order);
            } else if (user->role == Role::NHAN_VIEN) {
                // Phân biệt giữa PhucVu và NhanVienBep
                if (dynamic_cast<PhucVu*>(user)) {
                    menuNhanVien(user, menu, order, report, tableService);
                } else if (dynamic_cast<NhanVienBep*>(user)) {
                    menuNhanVienBep(user, kitchenService);
                }
            } else if (user->role == Role::QUAN_LY) {
                menuQuanLy(user, auth, menu, order, report, tableService);
            }
            auth.logout(); // Đăng xuất khi người dùng thoát khỏi menu của họ
        }

        else if (choice == 3) {
            // Truy cập nhanh cho khách vãng lai
            menuKhachHang(nullptr, menu, order);
        }

        else {
            cout << "Lua chon khong hop le. Vui long thu lai!\n";
        }
    }

    // Save data on exit
    userRepo.save();
    menuRepo.save();
    orderRepo.save();

    cout << "\n=== CHUONG TRINH KET THUC ===\n";
    return 0;
}
