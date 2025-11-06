#ifndef MENUSERVICE_H
#define MENUSERVICE_H

#include <string>
#include <vector>
#include <optional>

// Cấu trúc mô tả một món ăn / món gọi trong menu
struct Mon {
    int id;
    std::string tenMon;
    double gia;
    std::string moTa;
};

// Lớp quản lý menu món ăn
class MenuService {
private:
    std::vector<Mon> danhSachMon;
    int nextId; // Tự tăng ID

public:
    MenuService();

    // Thêm món mới vào menu
    bool themMon(const std::string& tenMon, double gia, const std::string& moTa = "");

    // Xóa món theo ID
    bool xoaMon(int id);

    // Cập nhật thông tin món
    bool capNhatMon(int id, const std::string& tenMoi, double giaMoi, const std::string& moTaMoi = "");

    // Lấy toàn bộ danh sách món
    std::vector<Mon> getDanhSachMon() const;

    // Lấy con trỏ tới món theo chỉ số trong danh sách (trả về nullptr nếu không hợp lệ)
    Mon* layMonTheoIndex(int index);

    // Tìm món theo ID
    std::optional<Mon> timMonTheoId(int id) const;

    // Tìm món theo tên (phục vụ tìm kiếm trên GUI)
    std::vector<Mon> timMonTheoTen(const std::string& keyword) const;

    // Xóa toàn bộ menu (nếu cần reset)
    void clear();
};

#endif // MENUSERVICE_H
