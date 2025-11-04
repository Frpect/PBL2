#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <string>
#include <unordered_map>

class AuthService {
private:
    std::unordered_map<std::string, std::string> userDatabase; // username -> password
    std::string currentUser;

public:
    AuthService();

    // Đăng ký tài khoản mới
    // Trả về: true nếu thành công, false nếu username đã tồn tại
    bool registerUser(const std::string& username, const std::string& password);

    // Đăng nhập
    // Trả về: true nếu đúng mật khẩu, false nếu sai
    bool login(const std::string& username, const std::string& password);

    // Đăng xuất
    void logout();

    // Kiểm tra có người đang đăng nhập không
    bool isLoggedIn() const;

    // Lấy tên người dùng hiện tại
    std::string getCurrentUser() const;

    // Kiểm tra xem tên đăng nhập đã tồn tại chưa (hỗ trợ kiểm tra khi nhập GUI)
    bool userExists(const std::string& username) const;
};

#endif
