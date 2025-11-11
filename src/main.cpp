#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm> // Thêm thư viện cho std::find_if
#include "Input.h"
#include "UserRepo.h"
#include "MenuRepo.h"
#include "OrderRepo.h"

// Thêm thư viện Windows để sửa lỗi font tiếng Việt trên console
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
        cout << "2. Xem danh sach mon\n"; // Lựa chọn 2
        cout << "3. Tao don hang moi\n";
        cout << "4. Yeu cau thanh toan\n";
        cout << "5. Xem lich su don hang\n";
        cout << "0. Quay lai\n";
        int choice = Input::readInt("Chon: ", 0, 5);

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

            // Tái cấu trúc quy trình đặt hàng giống giỏ hàng
            for (int i = 0; i < n; ++i) {
                 int idMon = Input::readInt("Nhap ID mon an: ", 1, 1000000);
                 int sl = Input::readInt("So luong: ", 1, 1000);
                 auto ds = menu.getDanhSachMon();
                 Mon* ptr = nullptr;
                 for (auto& m : ds) {
                     if (m.id == idMon) {
                         ptr = &m;
                         break;
                     }
                 }
                 if (ptr) {
                     order.themMonVaoDon(idDon, ptr, sl);
                 } else {
                     cout << "ID mon an khong hop le. Bo qua mon nay.\n";
                     --i; // Nhập lại cho món này
                 }
            }

            // Gửi đơn xuống bếp sau khi đã thêm tất cả các món
            order.capNhatTrangThai(idDon, "Đang chuẩn bị");
            cout << "Don hang #" << idDon << " da duoc tao va gui xuong bep.\n";
            if (khach) {
                khach->datMon(order.layDonHang(idDon));
            }
        }
        else if (choice == 4) {
            int idDon = Input::readInt("Nhap ID don hang can thanh toan: ", 1, 1000000);
            try {
                ::DonHang don = order.layDonHang(idDon);
                if (don.getTrangThai() == "Da thanh toan") {
                    cout << "Don hang nay da duoc thanh toan truoc do.\n";
                } else {
                    if (khach) khach->thanhToan(don);
                    order.capNhatTrangThai(idDon, "Da thanh toan");
                    cout << "Da yeu cau thanh toan thanh cong cho don hang #" << idDon << ".\n";
                }
            } catch (const std::runtime_error& e) {
                cout << "Loi: " << e.what() << "\n";
            }
        }
        else if (choice == 5) {
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

// Menu Nhân viên Bếp
void menuNhanVienBep(User* user, KitchenService& kitchenService) {
    NhanVienBep* bep = dynamic_cast<NhanVienBep*>(user);
    if (!bep) {
        cout << "Loi: Khong the truy cap menu bep.\n";
        return;
    }

    while (true) {
        cout << "\n===== MENU NHAN VIEN BEP =====\n";
        cout << "1. Xem danh sach don can chuan bi\n";
        cout << "2. Hoan thanh mot don hang\n";
        cout << "3. Xem lich su don da hoan thanh\n";
        cout << "4. Xem thong tin ca nhan\n";
        cout << "0. Dang xuat\n";
        int choice = Input::readInt("Chon: ", 0, 4);

        if (choice == 0) break;
        else if (choice == 1) {
            bep->xemDonHangCanChuanBi(&kitchenService);
        }
        else if (choice == 2) {
            int idDon = Input::readInt("Nhap ID don hang da hoan thanh: ", 1, 1000000);
            bep->hoanThanhDon(idDon, &kitchenService);
        }
        else if (choice == 3) {
            bep->xemLichSuDon(&kitchenService);
        }
        else if (choice == 4) {
            cout << "\n=== THONG TIN CA NHAN ===\n";
            cout << bep->xemThongTin() << "\n";
        }
    }
}

// Menu Nhân viên Phục Vụ
void menuNhanVien(User* user, MenuService& menu, OrderService& order, ReportService& report, TableService& tableService) {
    PhucVu* phucVu = dynamic_cast<PhucVu*>(user); // Dùng dynamic_cast để an toàn
    if (!phucVu) {
        cout << "Loi: Khong the truy cap menu phuc vu.\n";
        return;
    }

    while (true) {
        cout << "\n===== MENU NHAN VIEN PHUC VU =====\n";
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Tao don hang moi\n";
        cout << "3. Xem danh sach don hang\n";
        cout << "4. Cap nhat trang thai don hang\n";
        cout << "5. Xu ly thanh toan\n";
        cout << "6. In hoa don\n";
        cout << "7. Quan ly ban\n";
        cout << "8. Xem lich su giao dich\n";
        cout << "0. Dang xuat\n";
        int choice = Input::readInt("Chon: ", 0, 8);
        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n=== THONG TIN CA NHAN ===\n";
            cout << user->xemThongTin() << "\n";
        }
        else if (choice == 2) {
            string tenKhach = Input::readString("Nhap ten khach hang: ");
            int idDon = order.taoDonHang(tenKhach);
            cout << "Da tao don hang #" << idDon << " cho khach hang " << tenKhach << ".\n";
            
            while(true) {
                cout << "\n--- GIO HANG (Don #" << idDon << ") ---\n";
                cout << "1. Them mon\n2. Xoa mon\n3. Xem lai don hang\n4. Gui bep\n0. Huy don\n";
                int cartChoice = Input::readInt("Chon: ", 0, 4);

                if (cartChoice == 0) {
                    order.xoaDonHang(idDon);
                    cout << "Da huy don hang #" << idDon << ".\n";
                    break;
                } else if (cartChoice == 1) {
                    int idMon = Input::readInt("Nhap ID mon an: ", 1, 1000000);
                    int sl = Input::readInt("So luong: ", 1, 1000);
                    auto ds = menu.getDanhSachMon(); // Lấy danh sách món một lần
                    Mon* ptr = nullptr;
                    for (auto& m : ds) {
                        if (m.id == idMon) {
                            ptr = &m;
                            break;
                        }
                    }
                    if (ptr) {
                        if (order.themMonVaoDon(idDon, ptr, sl))
                            cout << "Da them mon '" << ptr->tenMon << "' vao don hang.\n";
                    } else {
                        cout << "ID mon an khong hop le.\n";
                    }
                } else if (cartChoice == 2) {
                    int idMonXoa = Input::readInt("Nhap ID mon an can xoa: ", 1, 1000000);
                    if (order.xoaMonKhoiDon(idDon, idMonXoa))
                        cout << "Da xoa mon khoi don hang.\n";
                    else
                        cout << "Xoa that bai. Mon khong co trong don.\n";
                } else if (cartChoice == 3) {
                    cout << order.layDonHang(idDon).xemChiTiet();
                } else if (cartChoice == 4) {
                    order.capNhatTrangThai(idDon, "Đang chuẩn bị");
                    cout << "Da gui don hang #" << idDon << " xuong bep.\n";
                    break;
                }
            }
        }
        else if (choice == 3) {
            auto danhSachDon = order.getDanhSachDonHang();
            if (danhSachDon.empty()) { cout << "Chua co don hang nao!\n"; continue; }
            for (auto& d : danhSachDon) {
                cout << d.xemChiTiet() << "--------------------\n";
            }
        }
        else if (choice == 4) {
            int id = Input::readInt("Nhap ID don hang: ", 1, 1000000);
            string tt = Input::readString("Nhap trang thai moi: ");
            if (order.capNhatTrangThai(id, tt))
                cout << "Da cap nhat don #" << id << " thanh " << tt << "\n";
            else
                cout << "Cap nhat that bai! Khong tim thay don hang hoac trang thai khong hop le.\n";
        }
        else if (choice == 5) {
            int idDon = Input::readInt("Nhap ID don hang can thanh toan: ", 1, 1000000);
            cout << "Chon phuong thuc thanh toan:\n1. Tien mat\n2. Chuyen khoan\n3. Quet the\n";
            int ptChoice = Input::readInt("Chon: ", 1, 3);
            string phuongThuc = "Tien mat";
            if (ptChoice == 2) phuongThuc = "Chuyen khoan";
            else if (ptChoice == 3) phuongThuc = "Quet the";

            phucVu->xuLyThanhToan(idDon, phuongThuc, &order);
        }
        else if (choice == 6) {
            int id = Input::readInt("Nhap ID don hang can in hoa don: ", 1, 1000000);
            try {
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
        else if (choice == 7) {
            while (true) {
                cout << "\n1. Xem so do ban\n2. Cap nhat trang thai ban\n0. Quay lai\n";
                int sub = Input::readInt("Chon: ", 0, 2);
                if (sub == 0) break;
                else if (sub == 1) {
                    phucVu->hienThiSoDoBan(&tableService);
                }
                else if (sub == 2) {
                    string maBan = Input::readString("Nhap ma ban can cap nhat: ");
                    string trangThai = Input::readString("Nhap trang thai moi (Trong, Co khach, Da dat): ");
                    if (tableService.capNhatTrangThaiBan(maBan, trangThai)) {
                        cout << "Da cap nhat trang thai ban " << maBan << ".\n";
                    } else {
                        cout << "Khong tim thay ban voi ma " << maBan << ".\n";
                    }
                }
            }
        }
        else if (choice == 8) {
            phucVu->xemLichSuGiaoDich(&report, &order);
        }
        else cout << "Lua chon khong hop le.\n";
    }
}

// Menu Quản lý
void menuQuanLy(User* user, AuthService& auth, MenuService& menu, OrderService& order, ReportService& report, TableService& tableService) {
    QuanLy* quanLy = static_cast<QuanLy*>(user);
    while (true) {
        cout << "\n===== MENU QUAN LY =====\n";
        cout << "1. Quan ly nhan su\n";
        cout << "2. Quan ly doanh thu\n";
        cout << "3. Quan ly menu\n";
        cout << "4. Quan ly ban\n";
        cout << "5. Tim mon nhanh (prefix)\n";
        cout << "6. Xem thong tin ca nhan\n";
        cout << "0. Dang xuat\n";
        int choice = Input::readInt("Chon: ", 0, 6);
        if (choice == 0) break;

        if (choice == 1) {
            while (true) {
                cout << "\n--- Quan Ly Nhan Su ---\n";
                cout << "1. Xem danh sach nhan su\n";
                cout << "2. Them nhan vien moi\n";
                cout << "3. Xoa nhan vien\n";
                cout << "0. Quay lai\n";
                int sub = Input::readInt("Chon: ", 0, 3);
                if (sub == 0) break;
                else if (sub == 1) {
                    quanLy->xemDanhSachNhanVien(&auth);
                }
                else if (sub == 2) {
                    quanLy->themNhanVien(&auth);
                }
                else if (sub == 3) {
                    string username = Input::readString("Nhap ten dang nhap cua nhan vien can xoa: ");
                    if (auth.deleteUser(username)) {
                        cout << "Da xoa nhan vien " << username << ".\n";
                    } else {
                        cout << "Xoa that bai. Nguoi dung khong ton tai hoac la chinh ban.\n";
                    }
                }
            }
        }
        else if (choice == 2) {
            while (true) {
                cout << "\n--- Quan Ly Doanh Thu ---\n";
                cout << "1. Xem bao cao tong hop\n";
                cout << "2. Xem doanh thu theo thoi gian (ngay/thang/nam)\n";
                cout << "0. Quay lai\n";
                int sub = Input::readInt("Chon: ", 0, 2);
                if (sub == 0) break;
                else if (sub == 1) {
                    auto baoCao = report.taoBaoCaoTongHop(order.getDanhSachDonHang());
                    cout << "\n===== BAO CAO TONG HOP =====\n" << baoCao << endl;
                }
                else if (sub == 2) {
                    quanLy->xemDoanhThuTheoThoiGian(&report, &order);
                }
            }
        }
        else if (choice == 3) {
            while (true) {
                cout << "\n1. Xem danh sach mon\n2. Them mon moi\n3. Sua mon theo ID\n4. Xoa mon theo ID\n0. Quay lai\n";
                int sub = Input::readInt("Chon: ", 0, 4);
                if (sub == 0) break;
                else if (sub == 1) {
                    auto danhSachMon = menu.getDanhSachMon();
                    for (const auto& m : danhSachMon)
                        cout << m.id << ". " << m.tenMon << " | " << m.gia << " VND | " << m.moTa << "\n";
                }
                else if (sub == 2) {
                    string ten = Input::readString("Nhap ten mon: ");
                    double gia = Input::readDouble("Nhap gia: ", 0, 1e9);
                    string moTa = Input::readString("Nhap mo ta: ", true);
                    menu.themMon(ten, gia, moTa);
                    cout << "Da them mon: " << ten << "\n";
                }
                else if (sub == 3) {
                    int id = Input::readInt("Nhap ID mon can sua: ", 1, 1000000000);
                    string ten = Input::readString("Nhap ten moi: ");
                    double gia = Input::readDouble("Nhap gia moi: ", 0, 1e9);
                    string moTa = Input::readString("Nhap mo ta moi: ", true);
                    if (menu.capNhatMon(id, ten, gia, moTa)) cout << "Da cap nhat.\n"; else cout << "Khong tim thay ID.\n";
                }
                else if (sub == 4) {
                    int id = Input::readInt("Nhap ID mon can xoa: ", 1, 1000000000);
                    if (menu.xoaMon(id)) cout << "Da xoa.\n"; else cout << "Khong tim thay ID.\n";
                }
            }
        }
        else if (choice == 4) {
            while (true) {
                cout << "\n1. Xem so do ban\n2. Them ban moi\n3. Cap nhat trang thai ban\n0. Quay lai\n";
                int sub = Input::readInt("Chon: ", 0, 3);
                if (sub == 0) break;
                else if (sub == 1) {
                    quanLy->hienThiSoDoBan(&tableService);
                }
                else if (sub == 2) {
                    string maBan = Input::readString("Nhap ma ban moi (vi du: B11): ");
                    quanLy->themBan(maBan, &tableService);
                    cout << "Da them ban " << maBan << ".\n";
                }
                else if (sub == 3) {
                    string maBan = Input::readString("Nhap ma ban can cap nhat: ");
                    string trangThai = Input::readString("Nhap trang thai moi (Trong, Co khach, Da dat): ");
                    if (tableService.capNhatTrangThaiBan(maBan, trangThai)) {
                        cout << "Da cap nhat trang thai ban " << maBan << ".\n";
                    } else {
                        cout << "Khong tim thay ban voi ma " << maBan << ".\n";
                    }
                }
            }
        }
        else if (choice == 5) {
            string q = Input::readString("Nhap chuoi tim: ");
            auto ds = menu.searchMonTheoPrefix(q, 10);
            if (ds.empty()) cout << "Khong co ket qua.\n";
            else {
                cout << "Goi y:\n";
                for (const auto& m : ds) cout << m.id << " | " << m.tenMon << " | " << m.gia << "\n";
            }
        }
        else if (choice == 6) {
            cout << "\n=== THONG TIN CA NHAN ===\n";
            cout << user->xemThongTin() << "\n";
        }
        else cout << "Lua chon khong hop le.\n";
    }
}

// Khai báo chuyển tiếp các hàm menu
void menuNhanVien(User* user, MenuService& menu, OrderService& order, ReportService& report, TableService& tableService);
void menuNhanVienBep(User* user, KitchenService& kitchenService);
void menuQuanLy(User* user, AuthService& auth, MenuService& menu, OrderService& order, ReportService& report, TableService& tableService);

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
            } else if (user->role == Role::QUAN_LY) { // Sửa lỗi gọi hàm
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
