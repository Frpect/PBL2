#ifndef BAN_H
#define BAN_H

#include <string>

class Ban {
private:
    std::string maBan;
    std::string trangThai; // Ví dụ: "Trống", "Đã đặt", "Có khách"

public:
    // Constructor để khởi tạo một bàn mới
    Ban(const std::string& maBan, const std::string& trangThai = "Trống");

    // Lấy mã bàn
    const std::string& getMaBan() const;

    // Lấy trạng thái hiện tại của bàn
    const std::string& getTrangThai() const;

    // Cập nhật trạng thái mới cho bàn
    void capNhatTrangThai(const std::string& trangThaiMoi);
};

#endif // BAN_H