#ifndef STORAGE_MENUREPO_H
#define STORAGE_MENUREPO_H

#include <string>

class MenuService;

namespace Repo {
	class MenuRepo {
	public:
		explicit MenuRepo(MenuService& menu, const std::string& dataDir = "data");
		bool load();
		bool save() const;
	private:
		MenuService& menu_;
		std::string dir_;
	};
}

#endif

