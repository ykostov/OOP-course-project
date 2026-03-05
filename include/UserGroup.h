#ifndef USERGROUP_H
#define USERGROUP_H

#include <string>
#include <iostream>

/**
 * @class UserGroup
 * @brief Представя група потребители с определена отстъпка/надценка
 * 
 * Класът дефинира различни типове потребители (ученици, учители, гости)
 * и техните специфични отстъпки или надценки.
 */
class UserGroup
{
private:
    std::string groupName;       // Име на групата
    double discountPercent;      // Отстъпка в % (положителна = отстъпка, отрицателна = надценка)
    std::string description;     // Описание на групата
    int maxDailyOrders;          // Максимален брой поръчки на ден

public:
    // Конструктор по подразбиране
    UserGroup();

    // Конструктор с параметри
    UserGroup(const std::string &name_, double discount_,
              const std::string &desc_ = "", int maxOrders_ = 5);

    // Getters
    std::string getGroupName() const;
    double getDiscountPercent() const;
    std::string getDescription() const;
    int getMaxDailyOrders() const;

    // Setters с валидация
    void setGroupName(const std::string &n);
    void setDiscountPercent(double d);
    void setDescription(const std::string &d);
    void setMaxDailyOrders(int m);

    // Изчислява крайна цена след отстъпка/надценка
    double applyDiscount(double originalPrice) const;

    // Предефиниране на оператор <<
    friend std::ostream &operator<<(std::ostream &os, const UserGroup &group);
};

#endif // USERGROUP_H
