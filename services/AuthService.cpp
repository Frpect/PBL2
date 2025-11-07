#include "AuthService.h"

AuthService::AuthService() : currentUser(nullptr) {}

// Đăng ký tài khoản mới với role
bool AuthService::registerUser(std::unique_ptr<User> user) {
    if (!user || userDatabase.find(user->getUsername()) != userDatabase.end()) {
        std::cout << "Ten dang nhap da ton tai!\n";
        return false; // username đã tồn tại
    }
    userDatabase[user->getUsername()] = std::move(user);
    return true;
}

// Đăng nhập: trả về User* nếu đúng, nullptr nếu sai
User* AuthService::login(const std::string& username, const std::string& password) {
    auto it = userDatabase.find(username);
    if (it != userDatabase.end() && it->second->getPassword() == password) {
        currentUser = it->second.get();
        return currentUser;
    }
    return nullptr;
}

// Đăng xuất
void AuthService::logout() {
    currentUser = nullptr;
}

// Kiểm tra có người đang đăng nhập không
bool AuthService::isLoggedIn() const {
    return currentUser != nullptr;
}

// Lấy tên người dùng hiện tại
std::string AuthService::getCurrentUser() const {
    if (currentUser)
        return currentUser->getUsername();
    return "";
}

// Lấy vai trò người dùng hiện tại
Role AuthService::getCurrentUserRole() const {
    if (currentUser)
        return currentUser->role;
    return Role::KHACH_HANG; // mặc định nếu chưa đăng nhập
}

// Kiểm tra xem tên đăng nhập đã tồn tại chưa
bool AuthService::userExists(const std::string& username) const {
    return userDatabase.find(username) != userDatabase.end();
}
