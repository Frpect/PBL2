#include "Input.h"
#include <iostream>
#include <sstream>
#include <cctype>

namespace {
	static inline std::string trim(const std::string& s) {
		size_t start = 0;
		while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) start++;
		size_t end = s.size();
		while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) end--;
		return s.substr(start, end - start);
	}
}

int Input::readInt(const std::string& prompt, int minValue, int maxValue) {
	while (true) {
		std::cout << prompt;
		std::string line;
		if (!std::getline(std::cin, line)) {
			std::cin.clear();
			continue;
		}
		line = trim(line);
		if (line.empty()) {
			std::cout << "Vui long nhap so.\n";
			continue;
		}
		std::istringstream iss(line);
		long long value;
		char extra;
		if (!(iss >> value) || (iss >> extra)) {
			std::cout << "Khong hop le. Hay nhap so nguyen.\n";
			continue;
		}
		if (value < minValue || value > maxValue) {
			std::cout << "Gia tri phai trong [" << minValue << ", " << maxValue << "].\n";
			continue;
		}
		return static_cast<int>(value);
	}
}

double Input::readDouble(const std::string& prompt, double minValue, double maxValue) {
	while (true) {
		std::cout << prompt;
		std::string line;
		if (!std::getline(std::cin, line)) {
			std::cin.clear();
			continue;
		}
		line = trim(line);
		if (line.empty()) {
			std::cout << "Vui long nhap so.\n";
			continue;
		}
		std::istringstream iss(line);
		double value;
		char extra;
		if (!(iss >> value) || (iss >> extra)) {
			std::cout << "Khong hop le. Hay nhap so thuc.\n";
			continue;
		}
		if (value < minValue || value > maxValue) {
			std::cout << "Gia tri phai trong [" << minValue << ", " << maxValue << "].\n";
			continue;
		}
		return value;
	}
}

std::string Input::readString(const std::string& prompt, bool allowEmpty) {
	while (true) {
		std::cout << prompt;
		std::string line;
		if (!std::getline(std::cin, line)) {
			std::cin.clear();
			continue;
		}
		line = trim(line);
		if (!allowEmpty && line.empty()) {
			std::cout << "Khong duoc de trong.\n";
			continue;
		}
		return line;
	}
}

bool Input::confirm(const std::string& prompt) {
	while (true) {
		std::cout << prompt << " (y/n): ";
		std::string line;
		if (!std::getline(std::cin, line)) {
			std::cin.clear();
			continue;
		}
		line = trim(line);
		if (line == "y" || line == "Y") return true;
		if (line == "n" || line == "N") return false;
		std::cout << "Hay nhap y hoac n.\n";
	}
}


