#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm> // Thêm thư viện cho std::find_if

// Thêm thư viện Windows để sửa lỗi font tiếng Việt trên console
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Services
#include "services/AuthService.h"
#include "services/MenuService.h"
#include "services/OrderService.h"
#include "services/ReportService.h"

// Models
#include "models/User.h"
#include "models/KhachHang.h"
#include "models/DonHang.h"
#include "models/NhanSu.h"
#include "models/NhanVienBep.h"
#include "models/PhucVu.h"
#include "models/QuanLy.h"
#include "models/MonAn.h"
#include "models/Ban.h"

// Menu Khách hàng
void menuKhachHang(MenuService& menu, OrderService& order) {
    string tenKhach, sdt, gioiTinh;
    cout << "Nhap ten khach hang: ";
    getline(cin, tenKhach);
    cout << "Nhap so dien thoai: ";
    getline(cin, sdt);
    cout << "Nhap gioi tinh: ";
    getline(cin, gioiTinh);

    // Tạo Khách hàng mới (mã tự động)
    KhachHang khach(tenKhach, sdt, gioiTinh);
    cout << "Ma khach hang cua ban la: " << khach.getMaKhachHang() << "\n";

    while (true) {
        cout << "\n===== MENU KHACH HANG =====\n";
        cout << "1. Xem thong tin khach hang\n";
        cout << "2. Xem danh sach mon\n";
        cout << "3. Tao don hang moi\n";
        cout << "4. Xem lich su don hang\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) break;
        else if (choice == 1) {
            cout << "\n=== THONG TIN KHACH HANG ===\n";
            cout << khach.xemThongTin() << "\n";
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
            int idDon = order.taoDonHang(khach.getHoTen());
            int n;
            cout << "Nhap so mon muon goi: ";
            cin >> n;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            auto danhSach = menu.getDanhSachMon();
            for (int i = 0; i < n; i++) {
                int idMon, sl;
                cout << "Nhap ID mon an: ";
                cin >> idMon;
                cout << "So luong: ";
                cin >> sl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Tìm món ăn theo ID thật sự thay vì vị trí
                auto it = std::find_if(danhSach.begin(), danhSach.end(), [idMon](const Mon& m){ return m.id == idMon; });

                if (it != danhSach.end()) {
                    order.themMonVaoDon(idDon, &(*it), sl);
                } else {
                    cout << "ID mon an khong hop le. Bo qua.\n";
                }
            }

            ::DonHang don = order.layDonHang(idDon);
            khach.datMon(don);

            cout << "Don hang #" << idDon << " da tao.\n";
            cout << "Ban co muon thanh toan don hang nay luon khong? (y/n): ";
            string c; getline(cin, c);
            if (c == "y" || c == "Y") {
                khach.thanhToan(don);
                cout << "Da thanh toan don hang #" << idDon 
                     << " | Tong tien: " << don.tinhTongTien() << " VND\n";
            } else {
                cout << "Don hang #" << idDon << " da luu vao lich su.\n";
            }
        }
        else if (choice == 4) {
            auto lichSu = khach.getLichSuDon();
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

// Menu Nhân viên
void menuNhanVien(User* user, OrderService& order, ReportService& report) {
    while (true) {
        cout << "\n===== MENU NHAN VIEN =====\n";
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Xem danh sach don hang\n";
        cout << "3. Cap nhat trang thai don hang\n";
        cout << "4. Tao bao cao tong hop\n";
        cout << "5. In hoa don\n"; // Chức năng này đã có
        cout << "0. Dang xuat\n"; // Đổi "Quay lai" thành "Dang xuat"
        cout << "Chon: ";

        int choice; cin >> choice; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 0) {
            // Không cần gọi auth.logout() ở đây vì vòng lặp chính sẽ xử lý
            break;
        }
        if (choice == 1) {
            auto danhSachDon = order.getDanhSachDonHang();
            cout << "\n=== THONG TIN CA NHAN ===\n";
            cout << user->xemThongTin() << "\n";
        }
        else if (choice == 2) {
            auto danhSachDon = order.getDanhSachDonHang();
            if (danhSachDon.empty()) { cout << "Chua co don hang nao!\n"; continue; }
            for (auto& d : danhSachDon) {
                cout << "Don #" << d.getMaDonHang() << "\n";
                cout << d.xemChiTiet() << "\n";
                cout << "Tong tien: " << d.tinhTongTien() << " VND\n";
            }
        }
        else if (choice == 3) {
            int id; string tt;
            cout << "Nhap ID don hang: "; cin >> id; 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            auto danhSachDon = order.getDanhSachDonHang();
            bool tonTai = false;
            for (auto& d : danhSachDon)
                if (d.getMaDonHang() == "DH" + to_string(id)) { tonTai = true; break; }
            if (!tonTai) { cout << "Khong tim thay don hang!\n"; continue; }
            cout << "Nhap trang thai moi: "; getline(cin, tt);
            if (order.capNhatTrangThai(id, tt))
                cout << "Da cap nhat don #" << id << " thanh " << tt << "\n";
            else
                cout << "Cap nhat that bai!\n";
        }
        else if (choice == 4) {
            auto baoCao = report.taoBaoCaoTongHop(order.getDanhSachDonHang());
            cout << "\n===== BAO CAO TONG HOP =====\n" << baoCao << endl;
        }
        else if (choice == 5) {
            int id;
            cout << "Nhap ID don hang can in hoa don: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            try {
                // Lấy thông tin đơn hàng từ OrderService
                ::DonHang don = order.layDonHang(id);
                cout << "\n===== HOA DON THANH TOAN =====\n";
                cout << don.xemChiTiet();
                cout << "--------------------------------\n";
                cout << "Tong tien: " << don.tinhTongTien() << " VND\n";
                cout << "==============================\n";
            } catch (const std::runtime_error& e) {
                cout << e.what() << "\n";
            }
        }
        else cout << "Lua chon khong hop le.\n";
    }
}

// Menu Quản lý
void menuQuanLy(User* user, MenuService& menu, OrderService& order, ReportService& report) {
    while (true) {
        cout << "\n===== MENU QUAN LY =====\n";
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Chuc nang nhan vien\n";
        cout << "3. Quan ly menu\n";
        cout << "4. Tao bao cao tong hop\n";
        cout << "0. Dang xuat\n"; // Đổi "Quay lai" thành "Dang xuat"
        cout << "Chon: ";

        int choice; cin >> choice; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 0) {
            // Không cần gọi auth.logout() ở đây vì vòng lặp chính sẽ xử lý
            break;
        }
        if (choice == 1) {
            cout << "\n=== THONG TIN CA NHAN ===\n";
            cout << user->xemThongTin() << "\n";
        }
        else if (choice == 2) menuNhanVien(user, order, report);
        else if (choice == 3) {
            while (true) {
                cout << "\n1. Xem danh sach mon\n2. Them mon moi\n0. Quay lai\nChon: ";
                int sub; cin >> sub; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (sub == 0) break;
                else if (sub == 1) {
                    auto danhSachMon = menu.getDanhSachMon();
                    for (size_t i = 0; i < danhSachMon.size(); i++)
                        cout << i+1 << ". " << danhSachMon[i].tenMon
                             << " | " << danhSachMon[i].gia << " VND"
                             << " | " << danhSachMon[i].moTa << "\n";
                }
                else if (sub == 2) {
                    string ten, moTa; double gia;
                    cout << "Nhap ten mon: "; getline(cin, ten);
                    cout << "Nhap gia: "; cin >> gia; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nhap mo ta: "; getline(cin, moTa);
                    menu.themMon(ten, gia, moTa);
                    cout << "Da them mon: " << ten << "\n";
                }
            }
        }
        else if (choice == 4) {
            auto baoCao = report.taoBaoCaoTongHop(order.getDanhSachDonHang());
            cout << "\n===== BAO CAO TONG HOP =====\n" << baoCao << endl;
        }
        else cout << "Lua chon khong hop le.\n";
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

    // Khởi tạo menu mẫu
    menu.themMon("Hamburger", 50000, "Hamburger bo pho mai");
    menu.themMon("Pizza", 120000, "Pizza hai san");
    menu.themMon("Khoai tay chien", 25000, "Khoai tay chien gion");

    // Tạo tài khoản mẫu
    auth.registerUser(make_unique<KhachHang>("khach1", "1111", "Le Van Tien", "0901112222", "Nam"));
    auth.registerUser(make_unique<PhucVu>("nv1", "2222", "Nguyen Tat Hoang", "0903334444", "Nam", "Ca sang", 8000000));
    auth.registerUser(make_unique<QuanLy>("QL1", "3333", "Vo Minh Triet", "0905556666", "Nam", "Ca ngay", 15000000));

    while (true) {
        cout << "\n===== HE THONG QUAN LY NHA HANG =====\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "3. Vao menu khach (khong can dang nhap)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) break;

        else if (choice == 1) {
            string username, password;
            int r; string ten, sdt, gt;
            cout << "Nhap ten dang nhap: "; getline(cin, username);
            cout << "Nhap mat khau: "; getline(cin, password);
            cout << "Nhap ho ten: "; getline(cin, ten);
            cout << "Nhap so dien thoai: "; getline(cin, sdt);
            cout << "Nhap gioi tinh: "; getline(cin, gt);
            cout << "Chon vai tro (1: Khach hang, 2: Nhan vien, 3: Quan ly): ";
            cin >> r; cin.ignore(numeric_limits<streamsize>::max(), '\n');

            bool success = false;
            if (r == 1) {
                success = auth.registerUser(make_unique<KhachHang>(username, password, ten, sdt, gt));
            } else if (r == 2) {
                success = auth.registerUser(make_unique<PhucVu>(username, password, ten, sdt, gt, "Ca mac dinh", 7000000));
            } else if (r == 3) {
                success = auth.registerUser(make_unique<QuanLy>(username, password, ten, sdt, gt, "Ca mac dinh", 12000000));
            }
            if (success) cout << "Dang ky thanh cong!\n";
            else
                cout << "Ten dang nhap da ton tai. Vui long chon ten khac.\n";
        }

        else if (choice == 2) {
            string username, password;
            cout << "Nhap ten dang nhap: "; getline(cin, username);
            cout << "Nhap mat khau: "; getline(cin, password);

            User* user = auth.login(username, password);
            if (!user) {
                cout << "Dang nhap that bai!\n";
                continue;
            }
            cout << "Dang nhap thanh cong!\n";

            // Menu theo vai trò
            if (user->role == Role::KHACH_HANG) {
                menuKhachHang(menu, order);
            } else if (user->role == Role::NHAN_VIEN) {
                menuNhanVien(user, order, report);
            } else if (user->role == Role::QUAN_LY) {
                menuQuanLy(user, menu, order, report);
            }
            auth.logout(); // Đăng xuất khi người dùng thoát khỏi menu của họ
        }

        else if (choice == 3) {
            // Truy cập nhanh cho khách
            menuKhachHang(menu, order);
        }

        else {
            cout << "Lua chon khong hop le. Vui long thu lai!\n";
        }
    }

    cout << "\n=== CHUONG TRINH KET THUC ===\n";
    return 0;
}
