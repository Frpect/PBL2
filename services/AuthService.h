#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <string>
#include <vector>
#include <memory>
#include "User.h"

class AuthService {
private:
    std::vector<std::unique_ptr<User>> users_;
    User* currentUser_ = nullptr;

public:
    AuthService() = default;

    bool registerUser(std::unique_ptr<User> user);
    User* login(const std::string& username, const std::string& password);
    void logout();
    User* getCurrentUser() const;
    std::vector<const User*> getAllUsers() const;
    bool deleteUser(const std::string& username);

    // For persistence
    void clearUsers();
    const std::vector<std::unique_ptr<User>>& getUsersForSave() const;
};

#endif // AUTHSERVICE_H