#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Person.h"

/**
 * @class User
 * @brief Представя потребител на ученическия стол
 *
 * Класът наследява Person и добавя информация специфична
 * за потребител на стола - група, баланс и брой поръчки.
 */
class User : public Person
{
private:
    std::string groupName; // Принадлежност към група
    double balance;        // Баланс в лева
    int ordersToday;       // Брой поръчки днес

public:
    // Конструктор по подразбиране
    User();

    // Конструктор с параметри (ID се задава автоматично от Cafeteria)
    User(const std::string &name_, int id_,
         const std::string &group_, double bal_ = 0.0);

    // Конструктор за зареждане от файл (с string ID)
    User(const std::string &name_, const std::string &id_,
         const std::string &group_, double bal_);

    // Getters
    std::string getGroupName() const;
    double getBalance() const;
    int getOrdersToday() const;

    // Setters с валидация
    void setGroupName(const std::string &g);
    void setBalance(double b);
    void setOrdersToday(int o);

    // Добавяне на средства към баланса
    bool addFunds(double amount);

    // Теглене на средства (при поръчка)
    bool deductFunds(double amount);

    // Нулиране на дневните поръчки (нов ден)
    void resetDailyOrders();

    // Предефиниране на виртуалния метод от Person
    void printInfo(std::ostream &os) const override;

    // Предефиниране на оператор <<
    friend std::ostream &operator<<(std::ostream &os, const User &user);
};

#endif // USER_H
