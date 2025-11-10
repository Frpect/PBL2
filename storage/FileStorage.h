#ifndef STORAGE_FILESTORAGE_H
#define STORAGE_FILESTORAGE_H

#include <string>
#include <vector>

namespace Storage {
	bool ensureDirectory(const std::string& dirPath);
	bool readAllLines(const std::string& filePath, std::vector<std::string>& outLines);
	bool writeAllLines(const std::string& filePath, const std::vector<std::string>& lines);
}

#endif

