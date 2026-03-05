#ifndef CAFETERIA_H
#define CAFETERIA_H

#include <string>
#include <vector>
#include <iostream>
#include "MenuItem.h"
#include "UserGroup.h"
#include "User.h"
#include "Order.h"

/**
 * @class Cafeteria
 * @brief Главен клас, който управлява цялата система на ученическия стол
 * 
 * Класът обединява всички компоненти на системата - меню, групи,
 * потребители и поръчки, и предоставя методи за тяхното управление.
 */
class Cafeteria
{
private:
    std::string name;                  // Име на стола
    std::string schoolName;            // Име на училището
    std::vector<MenuItem> menu;        // Меню с артикули
    std::vector<UserGroup> userGroups; // Потребителски групи
    std::vector<User> users;           // Регистрирани потребители
    std::vector<Order> orders;         // История на поръчките
    int nextOrderId;                   // Следващ номер на поръчка
    int nextUserId;                    // Следващ номер на потребител

public:
    // Конструктор по подразбиране
    Cafeteria();

    // Конструктор с параметри
    Cafeteria(const std::string &cafeName, const std::string &school);

    // Getters
    std::string getName() const;
    std::string getSchoolName() const;
    const std::vector<MenuItem> &getMenu() const;
    const std::vector<UserGroup> &getUserGroups() const;
    const std::vector<User> &getUsers() const;
    std::vector<User> &getUsers();
    const std::vector<Order> &getOrders() const;

    // Setters
    void setName(const std::string &n);
    void setSchoolName(const std::string &s);

    // Добавяне на артикул в менюто
    void addMenuItem(const MenuItem &item);

    // Добавяне на потребителска група
    void addUserGroup(const UserGroup &group);

    // Добавяне на потребител (ID се генерира автоматично)
    int addUser(const std::string &name, const std::string &groupName, double balance = 0.0);

    // Търсене на потребител по ID
    User *findUserByID(const std::string &id);

    // Търсене на група по име
    const UserGroup *findGroupByName(const std::string &name) const;

    // Създаване на поръчка
    bool createOrder(const std::string &userId, const std::vector<int> &itemIndices);

    // Статистика за приходите
    double getTotalRevenue() const;

    // Запис във файл
    void saveToFile(const std::string &filename) const;

    // Четене от файл
    void loadFromFile(const std::string &filename);

    // Предефиниране на оператор <<
    friend std::ostream &operator<<(std::ostream &os, const Cafeteria &caf);
};

#endif // CAFETERIA_H
