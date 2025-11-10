#include "MenuRepo.h"
#include "FileStorage.h"
#include "MenuService.h"
#include <sstream>

using namespace Storage;

namespace Repo {
	static inline std::string pathJoin(const std::string& a, const std::string& b) {
		if (a.empty()) return b;
		if (a.back() == '/' || a.back() == '\\') return a + b;
		return a + "/" + b;
	}

	MenuRepo::MenuRepo(MenuService& menu, const std::string& dataDir)
		: menu_(menu), dir_(dataDir) {}

	bool MenuRepo::load() {
		ensureDirectory(dir_);
		std::vector<std::string> lines;
		if (!readAllLines(pathJoin(dir_, "menu.txt"), lines)) return false;
		menu_.clear();
		int maxId = 0;
		for (const auto& line : lines) {
			if (line.empty()) continue;
			// id|ten|gia|mota
			std::istringstream iss(line);
			std::string idStr, ten, giaStr, moTa;
			if (!std::getline(iss, idStr, '|')) continue;
			if (!std::getline(iss, ten, '|')) continue;
			if (!std::getline(iss, giaStr, '|')) continue;
			if (!std::getline(iss, moTa, '|')) moTa = "";
			double gia = 0;
			int id = 0;
			try { id = std::stoi(idStr); } catch (...) { continue; }
			try { gia = std::stod(giaStr); } catch (...) { continue; }
			menu_.addMonWithId({id, ten, gia, moTa});
			if (id > maxId) maxId = id;
		}
		menu_.setNextId(maxId + 1);
		menu_.rebuildIndex();
		return true;
	}

	bool MenuRepo::save() const {
		ensureDirectory(dir_);
		auto ds = menu_.getDanhSachMon();
		std::vector<std::string> lines;
		lines.reserve(ds.size());
		for (const auto& m : ds) {
			std::ostringstream oss;
			oss << m.id << "|" << m.tenMon << "|" << m.gia << "|" << m.moTa;
			lines.push_back(oss.str());
		}
		return writeAllLines(pathJoin(dir_, "menu.txt"), lines);
	}
}


