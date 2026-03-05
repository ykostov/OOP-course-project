#include "User.h"
#include <iomanip>

using namespace std;

// Конструктор по подразбиране
User::User()
    : Person(), groupName("Гост"), balance(0.0), ordersToday(0) {}

// Конструктор с параметри (ID се задава автоматично от Cafeteria)
User::User(const string &name_, int id_,
           const string &group_, double bal_)
    : Person(name_, to_string(id_ > 0 ? id_ : 1)),
      groupName("Гост"), balance(0.0), ordersToday(0)
{
    setGroupName(group_);
    setBalance(bal_);
}

// Конструктор за зареждане от файл (с string ID)
User::User(const string &name_, const string &id_,
           const string &group_, double bal_)
    : Person(name_, id_),
      groupName("Гост"), balance(0.0), ordersToday(0)
{
    setGroupName(group_);
    setBalance(bal_);
}

// Getters
string User::getGroupName() const { return groupName; }
double User::getBalance() const { return balance; }
int User::getOrdersToday() const { return ordersToday; }

// Setters с валидация
void User::setGroupName(const string &g)
{
    groupName = g.empty() ? "Гост" : g;
}

void User::setBalance(double b)
{
    balance = (b < 0.0) ? 0.0 : ((b > 1000.0) ? 1000.0 : b);
}

void User::setOrdersToday(int o)
{
    ordersToday = (o < 0) ? 0 : o;
}

// Добавяне на средства към баланса
bool User::addFunds(double amount)
{
    if (amount <= 0 || amount > 500)
        return false;
    balance += amount;
    if (balance > 1000)
        balance = 1000;
    return true;
}

// Теглене на средства (при поръчка)
bool User::deductFunds(double amount)
{
    if (amount <= 0 || amount > balance)
        return false;
    balance -= amount;
    ordersToday++;
    return true;
}

// Нулиране на дневните поръчки (нов ден)
void User::resetDailyOrders() { ordersToday = 0; }

// Предефиниране на виртуалния метод от Person
void User::printInfo(ostream &os) const
{
    os << "Потребител: " << fullName
       << " | ID: " << idNumber
       << " | Група: " << groupName
       << " | Баланс: " << fixed << setprecision(2) << balance << " лв"
       << " | Поръчки днес: " << ordersToday;
}

// Предефиниране на оператор <<
ostream &operator<<(ostream &os, const User &user)
{
    user.printInfo(os);
    return os;
}
