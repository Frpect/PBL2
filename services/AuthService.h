#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include<vector>
#include "User.h"

class AuthService {
private:
    std::unordered_map<std::string, std::unique_ptr<User>> userDatabase;
    User* currentUser;

public:
    AuthService();
    bool registerUser(std::unique_ptr<User> user);
    User* login(const std::string& username, const std::string& password);
    void logout();
    bool isLoggedIn() const;
    std::string getCurrentUser() const;
    Role getCurrentUserRole() const;
    bool userExists(const std::string& username) const;
    // Export all users for persistence
    std::vector<const User*> getAllUsers() const;
};

#endif
