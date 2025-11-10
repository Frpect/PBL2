#include "MenuService.h"
#include <algorithm>

MenuService::MenuService() : nextId(1) {}

bool MenuService::themMon(const std::string& tenMon, double gia, const std::string& moTa) {
    // Không cho phép tên trống hoặc giá âm
    if (tenMon.empty() || gia < 0) return false;

    Mon mon = { nextId++, tenMon, gia, moTa };
    idToIndex[mon.id] = danhSachMon.size();
    danhSachMon.push_back(mon);
    index_.add(mon.id, mon.tenMon);
    return true;
}

bool MenuService::xoaMon(int id) {
    auto posIt = idToIndex.find(id);
    if (posIt == idToIndex.end()) return false;
    size_t idx = posIt->second;
    if (idx >= danhSachMon.size() || danhSachMon[idx].id != id) {
        // fallback linear remove if out of sync
        auto it = std::remove_if(danhSachMon.begin(), danhSachMon.end(), [id](const Mon& m){ return m.id == id; });
        bool removed = it != danhSachMon.end();
        if (removed) {
            for (auto jt = it; jt != danhSachMon.end(); ++jt) {
                // no-op
            }
            danhSachMon.erase(it, danhSachMon.end());
            rebuildIndex();
            idToIndex.clear();
            for (size_t i = 0; i < danhSachMon.size(); ++i) idToIndex[danhSachMon[i].id] = i;
        }
        return removed;
    }
    // remove and compact
    index_.remove(danhSachMon[idx].id, danhSachMon[idx].tenMon);
    danhSachMon.erase(danhSachMon.begin() + static_cast<std::ptrdiff_t>(idx));
    idToIndex.erase(posIt);
    // update indices map
    for (size_t i = idx; i < danhSachMon.size(); ++i) {
        idToIndex[danhSachMon[i].id] = i;
    }
    return true;
}

bool MenuService::capNhatMon(int id, const std::string& tenMoi, double giaMoi, const std::string& moTaMoi) {
    auto itPos = idToIndex.find(id);
    if (itPos == idToIndex.end()) return false;
    Mon& mon = danhSachMon[itPos->second];
    if (tenMoi != mon.tenMon) {
        index_.update(id, mon.tenMon, tenMoi);
    }
    mon.tenMon = tenMoi;
    mon.gia = giaMoi;
    mon.moTa = moTaMoi;
    return true;
}

std::vector<Mon> MenuService::getDanhSachMon() const {
    return danhSachMon;
}

Mon* MenuService::layMonTheoIndex(int index) {
    if (index < 0 || index >= (int)danhSachMon.size()) return nullptr;
    return &danhSachMon[index];
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
    idToIndex.clear();
    index_.clear();
}

void MenuService::loadFromList(const std::vector<Mon>& items) {
    clear();
    int maxId = 0;
    for (const auto& m : items) {
        addMonWithId(m);
        if (m.id > maxId) maxId = m.id;
    }
    setNextId(maxId + 1);
    rebuildIndex();
}

void MenuService::rebuildIndex() {
    std::vector<std::pair<int, std::string>> idNames;
    idNames.reserve(danhSachMon.size());
    for (const auto& m : danhSachMon) {
        idNames.emplace_back(m.id, m.tenMon);
    }
    index_.buildFrom(idNames, 20);
}

std::vector<Mon> MenuService::searchMonTheoPrefix(const std::string& q, size_t topN) const {
    std::vector<Mon> out;
    auto ids = index_.searchPrefix(q, topN);
    if (ids.empty()) return out;
    // Quick build of id->Mon (read-only copy), or linear scan
    for (int id : ids) {
        for (const auto& m : danhSachMon) {
            if (m.id == id) { out.push_back(m); break; }
        }
    }
    return out;
}

void MenuService::addMonWithId(const Mon& mon) {
    // Insert preserving id; do not touch nextId here
    idToIndex[mon.id] = danhSachMon.size();
    danhSachMon.push_back(mon);
    index_.add(mon.id, mon.tenMon);
}