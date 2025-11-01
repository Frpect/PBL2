#include "Ban.h"

Ban::Ban(std::string ma, std::string tt) : maBan_(std::move(ma)), trangThai_(std::move(tt)) {}

const std::string& Ban::getMaBan() const { return maBan_; }
const std::string& Ban::getTrangThai() const { return trangThai_; }

void Ban::capNhatTrangThai(const std::string& tt) {
    trangThai_ = tt;
}
