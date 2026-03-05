#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <iostream>

/**
 * @class Order
 * @brief Представя единична поръчка в стола
 * 
 * Класът съхранява информация за поръчка, включително
 * артикули, цени, обща сума и време на създаване.
 */
class Order
{
private:
    std::string orderId;            // ID на поръчката
    std::string userId;             // ID на потребителя
    std::vector<std::string> itemNames;  // Имена на поръчаните артикули
    std::vector<double> itemPrices; // Цени (след отстъпка)
    double totalPrice;              // Обща сума
    std::string timestamp;          // Време на поръчката

public:
    // Конструктор по подразбиране
    Order();

    // Конструктор с параметри
    Order(const std::string &ordId, const std::string &usrId);

    // Getters
    std::string getOrderId() const;
    std::string getUserId() const;
    double getTotalPrice() const;
    std::string getTimestamp() const;
    const std::vector<std::string> &getItemNames() const;
    const std::vector<double> &getItemPrices() const;

    // Setters
    void setOrderId(const std::string &id);
    void setUserId(const std::string &id);
    void setTimestamp(const std::string &ts);

    // Добавяне на артикул към поръчката
    void addItem(const std::string &name, double price);

    // Предефиниране на оператор <<
    friend std::ostream &operator<<(std::ostream &os, const Order &order);
};

#endif // ORDER_H
