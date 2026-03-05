#include "MenuItem.h"
#include <iomanip>

using namespace std;

// Конструктор по подразбиране
MenuItem::MenuItem()
    : name("Неизвестен"), category("Друго"),
      basePrice(0.0), calories(0), available(true) {}

// Конструктор с параметри
MenuItem::MenuItem(const string &name_, const string &category_,
                   double price_, int cal_, bool avail_)
    : name("Неизвестен"), category("Друго"),
      basePrice(0.0), calories(0), available(true)
{
    setName(name_);
    setCategory(category_);
    setBasePrice(price_);
    setCalories(cal_);
    setAvailable(avail_);
}

// Getters
string MenuItem::getName() const { return name; }
string MenuItem::getCategory() const { return category; }
double MenuItem::getBasePrice() const { return basePrice; }
int MenuItem::getCalories() const { return calories; }
bool MenuItem::isAvailable() const { return available; }

// Setters с валидация
void MenuItem::setName(const string &n)
{
    name = n.empty() ? "Неизвестен" : n;
}

void MenuItem::setCategory(const string &c)
{
    // Валидни категории
    if (c == "Основно" || c == "Салата" || c == "Десерт" ||
        c == "Напитка" || c == "Закуска" || c == "Супа")
    {
        category = c;
    }
    else
    {
        category = "Друго";
    }
}

void MenuItem::setBasePrice(double p)
{
    basePrice = (p < 0.0) ? 0.0 : ((p > 100.0) ? 100.0 : p);
}

void MenuItem::setCalories(int c)
{
    calories = (c < 0) ? 0 : ((c > 5000) ? 5000 : c);
}

void MenuItem::setAvailable(bool a) { available = a; }

// Предефиниране на оператор <<
ostream &operator<<(ostream &os, const MenuItem &item)
{
    os << "Артикул: " << item.name
       << " | Категория: " << item.category
       << " | Цена: " << fixed << setprecision(2) << item.basePrice << " лв"
       << " | Калории: " << item.calories
       << " | " << (item.available ? "Наличен" : "Изчерпан");
    return os;
}
