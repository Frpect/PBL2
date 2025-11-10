#ifndef STORAGE_ORDERREPO_H
#define STORAGE_ORDERREPO_H

#include <string>

class OrderService;

namespace Repo {
	class OrderRepo {
	public:
		explicit OrderRepo(OrderService& order, const std::string& dataDir = "data");
		bool load();
		bool save() const;
	private:
		OrderService& order_;
		std::string dir_;
	};
}

#endif

