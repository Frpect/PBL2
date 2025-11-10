#ifndef SERVICES_SEARCHINDEX_H
#define SERVICES_SEARCHINDEX_H

#include <string>
#include <unordered_map>
#include <vector>

class SearchIndex {
public:
	SearchIndex();
	void clear();
	void buildFrom(const std::vector<std::pair<int, std::string>>& idAndNames, size_t maxPrefixLen = 20);
	void add(int id, const std::string& name);
	void remove(int id, const std::string& name);
	void update(int id, const std::string& oldName, const std::string& newName);
	std::vector<int> searchPrefix(const std::string& query, size_t topN = 10) const;
private:
	static std::string normalize(const std::string& s);
	void indexOne(int id, const std::string& normName, size_t maxPrefixLen);
private:
	std::unordered_map<std::string, std::vector<int>> prefixToIds_;
	size_t maxPrefixLen_;
};

#endif

