#include "UserRepo.h"
#include "FileStorage.h"
#include "AuthService.h"
#include "KhachHang.h"
#include "PhucVu.h"
#include "QuanLy.h"
#include <sstream>

using namespace Storage;

namespace Repo {
	static inline std::string pathJoin(const std::string& a, const std::string& b) {
		if (a.empty()) return b;
		if (a.back() == '/' || a.back() == '\\') return a + b;
		return a + "/" + b;
	}

	UserRepo::UserRepo(AuthService& auth, const std::string& dataDir)
		: auth_(auth), dir_(dataDir) {}

	bool UserRepo::load() {
		ensureDirectory(dir_);
		std::vector<std::string> lines;
		if (!readAllLines(pathJoin(dir_, "users.txt"), lines)) return false;
		for (const auto& line : lines) {
			if (line.empty()) continue;
			// username|password|role|hoten|sdt|gioitinh
			std::istringstream iss(line);
			std::string username, password, roleStr, hoten, sdt, gt;
			if (!std::getline(iss, username, '|')) continue;
			if (!std::getline(iss, password, '|')) continue;
			if (!std::getline(iss, roleStr, '|')) continue;
			if (!std::getline(iss, hoten, '|')) continue;
			if (!std::getline(iss, sdt, '|')) continue;
			if (!std::getline(iss, gt, '|')) gt = "";
			int roleVal = 0;
			try { roleVal = std::stoi(roleStr); } catch (...) { continue; }
			if (roleVal == 0) {
				auth_.registerUser(std::make_unique<KhachHang>(username, password, hoten, sdt, gt));
			} else if (roleVal == 1) {
				auth_.registerUser(std::make_unique<PhucVu>(username, password, hoten, sdt, gt, "Ca mac dinh", 7000000));
			} else if (roleVal == 2) {
				auth_.registerUser(std::make_unique<QuanLy>(username, password, hoten, sdt, gt, "Ca mac dinh", 12000000));
			}
		}
		return true;
	}

	bool UserRepo::save() const {
		ensureDirectory(dir_);
		std::vector<std::string> lines;
		auto all = auth_.getAllUsers();
		lines.reserve(all.size());
		for (auto* u : all) {
			int roleVal = 0;
			if (u->role == Role::NHAN_VIEN) roleVal = 1;
			else if (u->role == Role::QUAN_LY) roleVal = 2;
			std::ostringstream oss;
			oss << u->getUsername() << "|" << u->getPassword() << "|" << roleVal
			    << "|" << u->getHoTen() << "|" << u->getSDT() << "|" << u->getGioiTinh();
			lines.push_back(oss.str());
		}
		return writeAllLines(pathJoin(dir_, "users.txt"), lines);
	}
}


