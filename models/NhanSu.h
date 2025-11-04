#ifndef NHANSU_H
#define NHANSU_H

#include "User.h"
#include <string>

class NhanSu : public User {
protected:
    std::string maNhanVien_;
    std::string taiKhoan_;
    std::string matKhau_;
    double luong_;
    std::string caLam_;

public:
    NhanSu() = default;
    NhanSu(std::string ma, std::string ten, std::string sdt, std::string gt,
           std::string tk, std::string mk, double luong, std::string ca);

    virtual ~NhanSu() = default;

    const std::string& getMaNhanVien() const;
    const std::string& getCaLam() const;
    double getLuong() const;

    void setCaLam(const std::string& ca);
    void setLuong(double luong);

    bool dangNhap(const std::string& tk, const std::string& mk) const;
    void dangXuat() const;

    virtual std::string xemThongTin() const override;
};

#endif
