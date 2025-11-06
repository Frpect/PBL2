#include "MenuService.h"
#include <algorithm>

MenuService::MenuService() : nextId(1) {}

bool MenuService::themMon(const std::string& tenMon, double gia, const std::string& moTa) {
    // Không cho phép tên trống hoặc giá âm
    if (tenMon.empty() || gia < 0) return false;

    Mon mon = { nextId++, tenMon, gia, moTa };
    danhSachMon.push_back(mon);
    return true;
}

bool MenuService::xoaMon(int id) {
    auto it = std::remove_if(danhSachMon.begin(), danhSachMon.end(),
                             [id](const Mon& m) { return m.id == id; });
    if (it != danhSachMon.end()) {
        danhSachMon.erase(it, danhSachMon.end());
        return true;
    }
    return false;
}

bool MenuService::capNhatMon(int id, const std::string& tenMoi, double giaMoi, const std::string& moTaMoi) {
    for (auto& mon : danhSachMon) {
        if (mon.id == id) {
            mon.tenMon = tenMoi;
            mon.gia = giaMoi;
            mon.moTa = moTaMoi;
            return true;
        }
    }
    return false;
}

std::vector<Mon> MenuService::getDanhSachMon() const {
    return danhSachMon;
}

std::optional<Mon> MenuService::timMonTheoId(int id) const {
    for (const auto& mon : danhSachMon) {
        if (mon.id == id) return mon;
    }
    return std::nullopt;
}

std::vector<Mon> MenuService::timMonTheoTen(const std::string& keyword) const {
    std::vector<Mon> ketQua;
    for (const auto& mon : danhSachMon) {
        if (mon.tenMon.find(keyword) != std::string::npos) {
            ketQua.push_back(mon);
        }
    }
    return ketQua;
}

void MenuService::clear() {
    danhSachMon.clear();
    nextId = 1;
}
