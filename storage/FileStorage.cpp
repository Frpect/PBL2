#include "FileStorage.h"
#include <fstream>
#include <filesystem>

namespace Storage {

	bool ensureDirectory(const std::string& dirPath) {
		std::error_code ec;
		if (std::filesystem::exists(dirPath, ec)) return true;
		return std::filesystem::create_directories(dirPath, ec) || std::filesystem::exists(dirPath, ec);
	}

	bool readAllLines(const std::string& filePath, std::vector<std::string>& outLines) {
		outLines.clear();
		std::ifstream in(filePath);
		if (!in.is_open()) return false;
		std::string line;
		while (std::getline(in, line)) {
			outLines.push_back(line);
		}
		return true;
	}

	bool writeAllLines(const std::string& filePath, const std::vector<std::string>& lines) {
		std::ofstream out(filePath, std::ios::trunc);
		if (!out.is_open()) return false;
		for (size_t i = 0; i < lines.size(); ++i) {
			out << lines[i];
			if (i + 1 < lines.size()) out << "\n";
		}
		return true;
	}
}


