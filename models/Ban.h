#ifndef BAN_H
#define BAN_H

#include <string>

class Ban {
private:
    std::string maBan_;
    std::string trangThai_;

public:
    Ban() = default;
    Ban(std::string ma, std::string tt = "Trống");

    const std::string& getMaBan() const;
    const std::string& getTrangThai() const;
    void capNhatTrangThai(const std::string& tt);
};

#endif
