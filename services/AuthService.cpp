#include "AuthService.h"

AuthService::AuthService() : currentUser("") {}

bool AuthService::registerUser(const std::string& username, const std::string& password) {
    if (userDatabase.find(username) != userDatabase.end()) {
        return false; // username đã tồn tại
    }
    userDatabase[username] = password;
    return true;
}

bool AuthService::login(const std::string& username, const std::string& password) {
    auto it = userDatabase.find(username);
    if (it != userDatabase.end() && it->second == password) {
        currentUser = username;
        return true;
    }
    return false;
}

void AuthService::logout() {
    currentUser.clear();
}

bool AuthService::isLoggedIn() const {
    return !currentUser.empty();
}

std::string AuthService::getCurrentUser() const {
    return currentUser;
}

bool AuthService::userExists(const std::string& username) const {
    return userDatabase.find(username) != userDatabase.end();
}
