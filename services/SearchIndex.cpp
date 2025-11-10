#include "SearchIndex.h"
#include <algorithm>
#include <cctype>

SearchIndex::SearchIndex() : maxPrefixLen_(20) {}

void SearchIndex::clear() {
	prefixToIds_.clear();
}

static inline std::string trimCopy(const std::string& s) {
	size_t a = 0, b = s.size();
	while (a < b && std::isspace(static_cast<unsigned char>(s[a]))) a++;
	while (b > a && std::isspace(static_cast<unsigned char>(s[b - 1]))) b--;
	return s.substr(a, b - a);
}

std::string SearchIndex::normalize(const std::string& s) {
	std::string t = trimCopy(s);
	for (char& c : t) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
	return t;
}

void SearchIndex::indexOne(int id, const std::string& normName, size_t maxPrefixLen) {
	const size_t L = std::min(maxPrefixLen, normName.size());
	for (size_t i = 1; i <= L; ++i) {
		std::string prefix = normName.substr(0, i);
		auto& vec = prefixToIds_[prefix];
		if (vec.empty() || vec.back() != id) {
			vec.push_back(id);
		}
	}
}

void SearchIndex::buildFrom(const std::vector<std::pair<int, std::string>>& idAndNames, size_t maxPrefixLen) {
	clear();
	maxPrefixLen_ = maxPrefixLen;
	for (const auto& p : idAndNames) {
		indexOne(p.first, normalize(p.second), maxPrefixLen_);
	}
}

void SearchIndex::add(int id, const std::string& name) {
	indexOne(id, normalize(name), maxPrefixLen_);
}

void SearchIndex::remove(int id, const std::string& name) {
	std::string norm = normalize(name);
	const size_t L = std::min(maxPrefixLen_, norm.size());
	for (size_t i = 1; i <= L; ++i) {
		std::string prefix = norm.substr(0, i);
		auto it = prefixToIds_.find(prefix);
		if (it == prefixToIds_.end()) continue;
		auto& v = it->second;
		v.erase(std::remove(v.begin(), v.end(), id), v.end());
		if (v.empty()) prefixToIds_.erase(it);
	}
}

void SearchIndex::update(int id, const std::string& oldName, const std::string& newName) {
	remove(id, oldName);
	add(id, newName);
}

std::vector<int> SearchIndex::searchPrefix(const std::string& query, size_t topN) const {
	std::string norm = normalize(query);
	auto it = prefixToIds_.find(norm);
	if (it == prefixToIds_.end()) return {};
	const auto& v = it->second;
	if (v.size() <= topN) return v;
	return std::vector<int>(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(topN));
}


