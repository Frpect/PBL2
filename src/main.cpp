#include <iostream>
#include <string>
#include "services/AuthService.h"
#include "services/MenuService.h"
#include "services/OrderService.h"
#include "services/ReportService.h"

using namespace std;

// Menu cho Khách hàng
void menuKhachHang(MenuService& menu, OrderService& order) {
    while (true) {
        cout << "\n===== MENU KHACH HANG =====\n";
        cout << "1. Xem danh sach mon\n";
        cout << "2. Tao don hang moi\n";
        cout << "3. Xem danh sach don hang da dat\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        int choice; cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) {
            auto danhSach = menu.getDanhSachMon();
            cout << "\nDanh sach mon:\n";
            for (size_t i = 0; i < danhSach.size(); i++) {
                cout << i+1 << ". " << danhSach[i].tenMon 
                     << " - " << danhSach[i].gia << " VND\n";
            }
        }
        else if (choice == 2) {
            string tenKhach;
            cout << "Nhap ten cua ban: ";
            cin.ignore();
            getline(cin, tenKhach);

            int idDon = order.taoDonHang(tenKhach);
            int n;
            cout << "Nhap so mon muon goi: ";
            cin >> n;

            auto danhSach = menu.getDanhSachMon();
            for (int i = 0; i < n; i++) {
                int idx, sl;
                cout << "Nhap ID mon (1-" << danhSach.size() << "): ";
                cin >> idx;
                cout << "So luong: ";
                cin >> sl;
                if (idx >= 1 && idx <= (int)danhSach.size())
                    order.themMonVaoDon(idDon, &danhSach[idx-1], sl);
            }

            cout << "Don hang #" << idDon << " da tao.\n";
        }
        else if (choice == 3) {
            auto danhSachDon = order.getDanhSachDonHang();
            cout << "\nDanh sach don hang:\n";
            for (auto& d : danhSachDon) {
                cout << "Don #" << d.id << " - " << d.getTenKhachHang()
                     << " | Trang thai: " << d.getTrangThai()
                     << " | Tong tien: " << d.tinhTongTien() << " VND\n";
            }
        }
    }
}

// Menu cho Nhân viên / Quản lý
void menuNhanVien(OrderService& order, ReportService& report) {
    while (true) {
        cout << "\n===== MENU NHAN VIEN / QUAN LY =====\n";
        cout << "1. Xem danh sach don hang\n";
        cout << "2. Cap nhat trang thai don hang\n";
        cout << "3. Tao bao cao tong hop\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        int choice; cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) {
            auto danhSachDon = order.getDanhSachDonHang();
            cout << "\nDanh sach don hang:\n";
            for (auto& d : danhSachDon) {
                cout << "Don #" << d.id << " - " << d.getTenKhachHang()
                     << " | Trang thai: " << d.getTrangThai()
                     << " | Tong tien: " << d.tinhTongTien() << " VND\n";
            }
        }
        else if (choice == 2) {
            int id; string tt;
            cout << "Nhap ID don hang: "; cin >> id;
            cout << "Nhap trang thai moi: ";
            cin.ignore();
            getline(cin, tt);
            order.capNhatTrangThai(id, tt);
            cout << "Da cap nhat don #" << id << ".\n";
        }
        else if (choice == 3) {
            auto baoCao = report.taoBaoCaoTongHop(order.getDanhSachDonHang());
            cout << "\n===== BAO CAO TONG HOP =====\n" << baoCao << endl;
        }
    }
}

int main() {
    AuthService auth;
    MenuService menu;
    OrderService order;
    ReportService report;

    // Khoi tao menu mau
    menu.themMon("Com rang", 30000, "Com rang trung");
    menu.themMon("Pho bo", 40000, "Pho bo tai chin");
    menu.themMon("Bun cha", 35000, "Bun cha Ha Noi");

    // Tao tai khoan mau
    auth.registerUser("khach1", "1111", Role::KHACH_HANG);
    auth.registerUser("nv1", "2222", Role::NHAN_VIEN);
    auth.registerUser("ql1", "3333", Role::QUAN_LY);

    while (true) {
        cout << "\n===== HE THONG QUAN LY NHA HANG =====\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        int choice; cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) {
            string username, password;
            int r;
            cout << "Nhap ten dang nhap: "; cin >> username;
            cout << "Nhap mat khau: "; cin >> password;
            cout << "Chon vai tro (1=Khach hang, 2=Nhan vien, 3=Quan ly): ";
            cin >> r;
            Role role = (r==1) ? Role::KHACH_HANG : (r==2 ? Role::NHAN_VIEN : Role::QUAN_LY);
            auth.registerUser(username, password, role);
            cout << "Dang ky thanh cong!\n";
        }
        else if (choice == 2) {
            string username, password;
            cout << "Nhap ten dang nhap: "; cin >> username;
            cout << "Nhap mat khau: "; cin >> password;

            User* user = auth.login(username, password);
            if (!user) {
                cout << "Dang nhap that bai!\n";
                continue;
            }
            cout << "Dang nhap thanh cong!\n";

            // Tự động vào menu theo vai trò
            if (user->role == Role::KHACH_HANG)
                menuKhachHang(menu, order);
            else if (user->role == Role::NHAN_VIEN || user->role == Role::QUAN_LY)
                menuNhanVien(order, report);
        }
    }

    cout << "\n=== CHUONG TRINH KET THUC ===\n";
    return 0;
}
