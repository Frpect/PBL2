#ifndef MONAN_H
#define MONAN_H

#include <string>
#include <sstream>

class MonAn {
private:
    std::string maMon_;
    std::string tenMon_;
    std::string loai_;
    double gia_{};
    int soLuong_{};

public:
    MonAn() = default;
    MonAn(std::string ma, std::string ten, std::string loai, double gia, int sl);

    const std::string& getTenMon() const { return tenMon_; }
    double getGia() const { return gia_; }

    void capNhatSoLuong(int delta);
    std::string xemThongTin() const;
};

#endif
