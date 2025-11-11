#include "AuthService.h"
#include <algorithm>
#include <iostream>

bool AuthService::registerUser(std::unique_ptr<User> user) {
    if (!user) return false;
    for (const auto& u : users_) {
        if (u->getUsername() == user->getUsername()) {
            return false; // Tên đăng nhập đã tồn tại
        }
    }
    users_.push_back(std::move(user));
    return true;
}

User* AuthService::login(const std::string& username, const std::string& password) {
    for (const auto& user : users_) {
        if (user->getUsername() == username && user->getPassword() == password) {
            currentUser_ = user.get();
            return currentUser_;
        }
    }
    return nullptr;
}

void AuthService::logout() {
    currentUser_ = nullptr;
}

User* AuthService::getCurrentUser() const {
    return currentUser_;
}

std::vector<const User*> AuthService::getAllUsers() const {
    std::vector<const User*> userPointers;
    for (const auto& u : users_) {
        userPointers.push_back(u.get());
    }
    return userPointers;
}

bool AuthService::deleteUser(const std::string& username) {
    if (currentUser_ && currentUser_->getUsername() == username) {
        return false; // Không cho phép xóa người dùng đang đăng nhập
    }

    auto it = std::remove_if(users_.begin(), users_.end(),
        [&](const std::unique_ptr<User>& user) { // Sửa lỗi cú pháp lambda
            return user->getUsername() == username;
        });

    if (it != users_.end()) {
        users_.erase(it, users_.end());
        return true;
    }
    return false;
}

void AuthService::clearUsers() {
    users_.clear();
}

const std::vector<std::unique_ptr<User>>& AuthService::getUsersForSave() const {
    return users_;
}