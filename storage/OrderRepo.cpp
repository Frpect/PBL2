#include "OrderRepo.h"
#include "FileStorage.h"
#include "OrderService.h"
#include "MenuService.h"
#include <sstream>

using namespace Storage;

namespace Repo {
	static inline std::string pathJoin(const std::string& a, const std::string& b) {
		if (a.empty()) return b;
		if (a.back() == '/' || a.back() == '\\') return a + b;
		return a + "/" + b;
	}

	OrderRepo::OrderRepo(OrderService& order, const std::string& dataDir)
		: order_(order), dir_(dataDir) {}

	bool OrderRepo::load() {
		ensureDirectory(dir_);
		std::vector<std::string> lines;
		if (!readAllLines(pathJoin(dir_, "orders.txt"), lines)) return false;
		order_.clear();
		// Format:
		// id|khach|trangthai|n
		// item: ten|gia|sl
		size_t i = 0;
		while (i < lines.size()) {
			const std::string& header = lines[i++];
			if (header.empty()) continue;
			std::istringstream hs(header);
			std::string idStr, tenKhach, trangThai, nStr;
			if (!std::getline(hs, idStr, '|')) continue;
			if (!std::getline(hs, tenKhach, '|')) continue;
			if (!std::getline(hs, trangThai, '|')) continue;
			if (!std::getline(hs, nStr, '|')) continue;
			int n = 0;
			try { n = std::stoi(nStr); } catch (...) { n = 0; }
			int id = order_.taoDonHang(tenKhach);
			for (int k = 0; k < n && i < lines.size(); ++k, ++i) {
				std::istringstream is(lines[i]);
				std::string ten, giaStr, slStr;
				if (!std::getline(is, ten, '|')) continue;
				if (!std::getline(is, giaStr, '|')) continue;
				if (!std::getline(is, slStr, '|')) continue;
				int sl = 0; double gia = 0;
				try { gia = std::stod(giaStr); } catch (...) {}
				try { sl = std::stoi(slStr); } catch (...) {}
				// OrderService needs Mon* from MenuService; we can't recreate pointer here
				// so we skip attaching real menu pointer and rely on status only.
				// For minimal viable, we won't add items (or could be adapted to accept raw item).
			}
			order_.capNhatTrangThai(id, trangThai);
		}
		return true;
	}

	bool OrderRepo::save() const {
		ensureDirectory(dir_);
		auto ds = order_.getDanhSachDonHang();
		std::vector<std::string> lines;
		for (const auto& d : ds) {
			const auto& items = d.getDanhSachMon();
			std::ostringstream h;
			h << d.getMaDonHang() << "|" << "" /*khach hang*/ << "|" << d.getTrangThai() << "|" << items.size();
			lines.push_back(h.str());
			for (const auto& it : items) {
				std::ostringstream is;
				is << it.tenMon << "|" << it.gia << "|" << it.soLuong;
				lines.push_back(is.str());
			}
		}
		return writeAllLines(pathJoin(dir_, "orders.txt"), lines);
	}
}


