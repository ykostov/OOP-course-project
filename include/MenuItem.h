#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <iostream>

/**
 * @class MenuItem
 * @brief Представя единичен продукт в менюто на стола
 * 
 * Класът съхранява информация за артикул от менюто,
 * включително име, категория, цена, калории и наличност.
 */
class MenuItem
{
private:
    std::string name;      // Име на артикула
    std::string category;  // Категория: "Основно", "Салата", "Десерт", "Напитка"
    double basePrice;      // Базова цена в лева
    int calories;          // Калории
    bool available;        // Наличен ли е в момента

public:
    // Конструктор по подразбиране
    MenuItem();

    // Конструктор с параметри
    MenuItem(const std::string &name_, const std::string &category_,
             double price_, int cal_, bool avail_ = true);

    // Getters
    std::string getName() const;
    std::string getCategory() const;
    double getBasePrice() const;
    int getCalories() const;
    bool isAvailable() const;

    // Setters с валидация
    void setName(const std::string &n);
    void setCategory(const std::string &c);
    void setBasePrice(double p);
    void setCalories(int c);
    void setAvailable(bool a);

    // Предефиниране на оператор <<
    friend std::ostream &operator<<(std::ostream &os, const MenuItem &item);
};

#endif // MENUITEM_H
