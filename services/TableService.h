#ifndef TABLESERVICE_H
#define TABLESERVICE_H

#include <vector>
#include <string>
#include <optional>
#include "Ban.h" // Đảm bảo đã có model Ban.h

class TableService {
private:
    std::vector<Ban> danhSachBan;

public:
    // Khởi tạo dịch vụ, có thể tạo sẵn một số bàn
    TableService();

    // Thêm một bàn mới vào danh sách
    void themBan(const std::string& maBan, const std::string& trangThai = "Trống");

    // Lấy danh sách tất cả các bàn
    const std::vector<Ban>& getDanhSachBan() const;

    // Cập nhật trạng thái của một bàn theo mã
    bool capNhatTrangThaiBan(const std::string& maBan, const std::string& trangThaiMoi);

    // Hiển thị sơ đồ trạng thái tất cả các bàn ra console
    void hienThiSoDoBan() const;
};

#endif // TABLESERVICE_H