#include "UserGroup.h"

using namespace std;

// Конструктор по подразбиране
UserGroup::UserGroup()
    : groupName("Гост"), discountPercent(0.0),
      description("Без отстъпка"), maxDailyOrders(3) {}

// Конструктор с параметри
UserGroup::UserGroup(const string &name_, double discount_,
                     const string &desc_, int maxOrders_)
    : groupName("Гост"), discountPercent(0.0),
      description("Без отстъпка"), maxDailyOrders(3)
{
    setGroupName(name_);
    setDiscountPercent(discount_);
    setDescription(desc_);
    setMaxDailyOrders(maxOrders_);
}

// Getters
string UserGroup::getGroupName() const { return groupName; }
double UserGroup::getDiscountPercent() const { return discountPercent; }
string UserGroup::getDescription() const { return description; }
int UserGroup::getMaxDailyOrders() const { return maxDailyOrders; }

// Setters с валидация
void UserGroup::setGroupName(const string &n)
{
    groupName = n.empty() ? "Гост" : n;
}

void UserGroup::setDiscountPercent(double d)
{
    // Ограничаваме между -50% (надценка) и +50% (отстъпка)
    discountPercent = (d < -50.0) ? -50.0 : ((d > 50.0) ? 50.0 : d);
}

void UserGroup::setDescription(const string &d)
{
    description = d.empty() ? "Без описание" : d;
}

void UserGroup::setMaxDailyOrders(int m)
{
    maxDailyOrders = (m < 1) ? 1 : ((m > 10) ? 10 : m);
}

// Изчислява крайна цена след отстъпка/надценка
double UserGroup::applyDiscount(double originalPrice) const
{
    return originalPrice * (1.0 - discountPercent / 100.0);
}

// Предефиниране на оператор <<
ostream &operator<<(ostream &os, const UserGroup &group)
{
    os << "Група: " << group.groupName;
    if (group.discountPercent > 0)
    {
        os << " | Отстъпка: " << group.discountPercent << "%";
    }
    else if (group.discountPercent < 0)
    {
        os << " | Надценка: " << (-group.discountPercent) << "%";
    }
    else
    {
        os << " | Без отстъпка/надценка";
    }
    os << " | Макс. поръчки/ден: " << group.maxDailyOrders
       << "\n   Описание: " << group.description;
    return os;
}
