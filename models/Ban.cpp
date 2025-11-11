#include "Ban.h"
#include <utility>

// Sử dụng tên biến thành viên và tham số khớp với Ban.h
Ban::Ban(const std::string& maBan, const std::string& trangThai) 
    : maBan(maBan), trangThai(trangThai) {}

const std::string& Ban::getMaBan() const { 
    return maBan; 
}
const std::string& Ban::getTrangThai() const { 
    return trangThai; 
}

void Ban::capNhatTrangThai(const std::string& trangThaiMoi) {
    this->trangThai = trangThaiMoi;
}
