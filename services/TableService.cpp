#include "TableService.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

TableService::TableService() {
    // Khởi tạo sẵn 10 bàn khi dịch vụ được tạo
    for (int i = 1; i <= 10; ++i) {
        // Dùng to_string để tạo mã bàn B1, B2, ...
        themBan("B" + std::to_string(i));
    }
}

void TableService::themBan(const std::string& maBan, const std::string& trangThai) {
    // Kiểm tra xem bàn đã tồn tại chưa để tránh trùng lặp
    auto it = std::find_if(danhSachBan.begin(), danhSachBan.end(), [&](const Ban& ban) {
        return ban.getMaBan() == maBan;
    });

    if (it == danhSachBan.end()) {
        danhSachBan.emplace_back(maBan, trangThai);
    }
}

const std::vector<Ban>& TableService::getDanhSachBan() const {
    return danhSachBan;
}

bool TableService::capNhatTrangThaiBan(const std::string& maBan, const std::string& trangThaiMoi) {
    auto it = std::find_if(danhSachBan.begin(), danhSachBan.end(), [&](Ban& ban) {
        return ban.getMaBan() == maBan;
    });

    if (it != danhSachBan.end()) {
        it->capNhatTrangThai(trangThaiMoi);
        return true;
    }
    return false; // Không tìm thấy bàn
}

void TableService::hienThiSoDoBan() const {
    std::cout << "\n===== SO DO BAN AN =====\n";
    for (const auto& ban : danhSachBan) {
        // std::left và std::setw(15) để căn chỉnh cho đẹp
        std::cout << "Ban " << std::left << std::setw(5) << ban.getMaBan()
                  << "| Trang thai: " << ban.getTrangThai() << "\n";
    }
    std::cout << "========================\n";
}