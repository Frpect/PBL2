#ifndef STORAGE_USERREPO_H
#define STORAGE_USERREPO_H

#include <string>

class AuthService;

namespace Repo {
	class UserRepo {
	public:
		explicit UserRepo(AuthService& auth, const std::string& dataDir = "data");
		bool load();
		bool save() const;
	private:
		AuthService& auth_;
		std::string dir_;
	};
}

#endif

