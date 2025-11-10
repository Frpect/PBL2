#ifndef UTILS_INPUT_H
#define UTILS_INPUT_H
//Doc du lieu nhap vao chuyen nghiep hon
#include <string>
#include <limits>

namespace Input {
	int readInt(const std::string& prompt, int minValue, int maxValue);
	double readDouble(const std::string& prompt, double minValue, double maxValue);
	std::string readString(const std::string& prompt, bool allowEmpty = false);
	bool confirm(const std::string& prompt); // y/n
}

#endif

