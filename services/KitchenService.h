#ifndef KITCHENSERVICE_H
#define KITCHENSERVICE_H

#include "OrderService.h"
#include <vector>

class KitchenService {
private:
    OrderService* orderService_; // KitchenService phụ thuộc vào OrderService

public:
    // Constructor nhận vào một OrderService
    explicit KitchenService(OrderService* orderService);

    // Lấy danh sách các đơn hàng đang chờ bếp xử lý (theo thứ tự ưu tiên FIFO)
    std::vector<::DonHang> getDonHangCanChuanBi() const;

    // Lấy lịch sử các đơn hàng đã hoàn thành
    std::vector<::DonHang> getLichSuDonHoanThanh() const;

    // Đánh dấu một đơn hàng là "Đã hoàn thành"
    bool hoanThanhDon(int idDon);
};

#endif // KITCHENSERVICE_H