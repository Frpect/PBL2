#include "KitchenService.h"
#include <algorithm>

KitchenService::KitchenService(OrderService* orderService) : orderService_(orderService) {}

std::vector<::DonHang> KitchenService::getDonHangCanChuanBi() const {
    if (!orderService_) return {};

    auto allOrders = orderService_->getDanhSachDonHang();
    std::vector<::DonHang> kitchenOrders;

    // Lọc các đơn hàng có trạng thái "Đang chuẩn bị"
    for (const auto& don : allOrders) {
        if (don.getTrangThai() == "Đang chuẩn bị") {
            kitchenOrders.push_back(don);
        }
    }
    return kitchenOrders;
}

std::vector<::DonHang> KitchenService::getLichSuDonHoanThanh() const {
    if (!orderService_) return {};

    auto allOrders = orderService_->getDanhSachDonHang();
    std::vector<::DonHang> completedOrders;

    for (const auto& don : allOrders) {
        if (don.getTrangThai() == "Đã hoàn thành") {
            completedOrders.push_back(don);
        }
    }
    return completedOrders;
}

bool KitchenService::hoanThanhDon(int idDon) {
    if (!orderService_) return false;
    return orderService_->capNhatTrangThai(idDon, "Đã hoàn thành");
}