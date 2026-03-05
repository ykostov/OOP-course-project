#include "Cafeteria.h"
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

// Конструктор по подразбиране
Cafeteria::Cafeteria()
    : name("Ученически стол"), schoolName("Неизвестно училище"),
      nextOrderId(1), nextUserId(1)
{
    // Добавяме групи по подразбиране
    userGroups.push_back(UserGroup("Ученик 1-4 клас", 30.0,
                                   "Ученици от начален курс - 30% отстъпка", 2));
    userGroups.push_back(UserGroup("Ученик 5-12 клас", 20.0,
                                   "Ученици от прогимназиален и гимназиален курс - 20% отстъпка", 3));
    userGroups.push_back(UserGroup("Учител", 15.0,
                                   "Преподаватели - 15% отстъпка", 5));
    userGroups.push_back(UserGroup("Персонал", 10.0,
                                   "Помощен персонал - 10% отстъпка", 5));
    userGroups.push_back(UserGroup("Гост", -10.0,
                                   "Външни лица - 10% надценка", 2));
}

// Конструктор с параметри
Cafeteria::Cafeteria(const string &cafeName, const string &school)
    : name(cafeName), schoolName(school), nextOrderId(1), nextUserId(1) {}

// Getters
string Cafeteria::getName() const { return name; }
string Cafeteria::getSchoolName() const { return schoolName; }
const vector<MenuItem> &Cafeteria::getMenu() const { return menu; }
const vector<UserGroup> &Cafeteria::getUserGroups() const { return userGroups; }
const vector<User> &Cafeteria::getUsers() const { return users; }
vector<User> &Cafeteria::getUsers() { return users; }
const vector<Order> &Cafeteria::getOrders() const { return orders; }

// Setters
void Cafeteria::setName(const string &n) { name = n.empty() ? "Ученически стол" : n; }
void Cafeteria::setSchoolName(const string &s) { schoolName = s.empty() ? "Неизвестно" : s; }

// Добавяне на артикул в менюто
void Cafeteria::addMenuItem(const MenuItem &item) { menu.push_back(item); }

// Добавяне на потребителска група
void Cafeteria::addUserGroup(const UserGroup &group) { userGroups.push_back(group); }

// Добавяне на потребител (ID се генерира автоматично)
int Cafeteria::addUser(const string &name, const string &groupName, double balance)
{
    int newId = nextUserId++;
    users.push_back(User(name, newId, groupName, balance));
    return newId;
}

// Търсене на потребител по ID
User *Cafeteria::findUserByID(const string &id)
{
    for (auto &u : users)
    {
        if (u.getIDNumber() == id)
            return &u;
    }
    return nullptr;
}

// Търсене на група по име
const UserGroup *Cafeteria::findGroupByName(const string &name) const
{
    for (const auto &g : userGroups)
    {
        if (g.getGroupName() == name)
            return &g;
    }
    return nullptr;
}

// Създаване на поръчка
bool Cafeteria::createOrder(const string &userId, const vector<int> &itemIndices)
{
    User *user = findUserByID(userId);
    if (!user)
    {
        cout << "Потребителят не е намерен!\n";
        return false;
    }

    const UserGroup *group = findGroupByName(user->getGroupName());
    if (!group)
    {
        cout << "Групата на потребителя не съществува!\n";
        return false;
    }

    if (user->getOrdersToday() >= group->getMaxDailyOrders())
    {
        cout << "Достигнат е лимитът за дневни поръчки!\n";
        return false;
    }

    // Създаваме поръчка
    string orderId = "ORD" + to_string(nextOrderId++);
    Order order(orderId, userId);

    double total = 0.0;
    for (int idx : itemIndices)
    {
        if (idx >= 0 && idx < (int)menu.size() && menu[idx].isAvailable())
        {
            double discountedPrice = group->applyDiscount(menu[idx].getBasePrice());
            order.addItem(menu[idx].getName(), discountedPrice);
            total += discountedPrice;
        }
    }

    if (total == 0.0)
    {
        cout << "Няма валидни артикули в поръчката!\n";
        return false;
    }

    if (user->getBalance() < total)
    {
        cout << "Недостатъчен баланс! Нужни са " << fixed << setprecision(2)
             << total << " лв, а имате " << user->getBalance() << " лв.\n";
        return false;
    }

    user->deductFunds(total);
    orders.push_back(order);
    cout << "Поръчката е успешна!\n"
         << order << "\n";
    return true;
}

// Статистика за приходите
double Cafeteria::getTotalRevenue() const
{
    double sum = 0.0;
    for (const auto &o : orders)
    {
        sum += o.getTotalPrice();
    }
    return sum;
}

// Запис във файл
void Cafeteria::saveToFile(const string &filename) const
{
    ofstream out(filename);
    if (!out)
    {
        cerr << "Грешка при запис във файл!\n";
        return;
    }

    // Основни данни
    out << name << "\n"
        << schoolName << "\n"
        << nextOrderId << "\n"
        << nextUserId << "\n";

    // Меню
    out << menu.size() << "\n";
    for (const auto &item : menu)
    {
        out << item.getName() << "\n"
            << item.getCategory() << "\n"
            << item.getBasePrice() << "\n"
            << item.getCalories() << "\n"
            << item.isAvailable() << "\n";
    }

    // Групи
    out << userGroups.size() << "\n";
    for (const auto &g : userGroups)
    {
        out << g.getGroupName() << "\n"
            << g.getDiscountPercent() << "\n"
            << g.getDescription() << "\n"
            << g.getMaxDailyOrders() << "\n";
    }

    // Потребители
    out << users.size() << "\n";
    for (const auto &u : users)
    {
        out << u.getFullName() << "\n"
            << u.getIDNumber() << "\n"
            << u.getGroupName() << "\n"
            << u.getBalance() << "\n"
            << u.getOrdersToday() << "\n";
    }

    // Поръчки
    out << orders.size() << "\n";
    for (const auto &o : orders)
    {
        out << o.getOrderId() << "\n"
            << o.getUserId() << "\n"
            << o.getTimestamp() << "\n"
            << o.getItemNames().size() << "\n";
        for (size_t i = 0; i < o.getItemNames().size(); i++)
        {
            out << o.getItemNames()[i] << "\n"
                << o.getItemPrices()[i] << "\n";
        }
    }

    cout << "Данните са записани успешно в " << filename << "\n";
}

// Четене от файл
void Cafeteria::loadFromFile(const string &filename)
{
    ifstream in(filename);
    if (!in)
    {
        cerr << "Грешка при четене на файл!\n";
        return;
    }

    menu.clear();
    userGroups.clear();
    users.clear();
    orders.clear();

    // Основни данни
    getline(in, name);
    getline(in, schoolName);
    in >> nextOrderId >> nextUserId;
    in.ignore(numeric_limits<streamsize>::max(), '\n');

    // Меню
    size_t menuCount;
    in >> menuCount;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < menuCount; i++)
    {
        string itemName, category;
        double price;
        int calories;
        bool available;

        getline(in, itemName);
        getline(in, category);
        in >> price >> calories >> available;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        menu.push_back(MenuItem(itemName, category, price, calories, available));
    }

    // Групи
    size_t groupCount;
    in >> groupCount;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < groupCount; i++)
    {
        string gname, desc;
        double discount;
        int maxOrders;

        getline(in, gname);
        in >> discount;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(in, desc);
        in >> maxOrders;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        userGroups.push_back(UserGroup(gname, discount, desc, maxOrders));
    }

    // Потребители
    size_t userCount;
    in >> userCount;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < userCount; i++)
    {
        string fullName, idNumber, groupName;
        double balance;
        int ordersToday;

        getline(in, fullName);
        getline(in, idNumber);
        getline(in, groupName);
        in >> balance >> ordersToday;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        User u(fullName, idNumber, groupName, balance);
        u.setOrdersToday(ordersToday);
        users.push_back(u);
    }

    // Поръчки
    size_t orderCount;
    in >> orderCount;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < orderCount; i++)
    {
        string orderId, usrId, timestamp;
        size_t itemCount;

        getline(in, orderId);
        getline(in, usrId);
        getline(in, timestamp);
        in >> itemCount;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        Order o(orderId, usrId);
        o.setTimestamp(timestamp);

        for (size_t j = 0; j < itemCount; j++)
        {
            string itemName;
            double itemPrice;
            getline(in, itemName);
            in >> itemPrice;
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            o.addItem(itemName, itemPrice);
        }
        orders.push_back(o);
    }

    cout << "Данните са заредени успешно от " << filename << "\n";
}

// Предефиниране на оператор <<
ostream &operator<<(ostream &os, const Cafeteria &caf)
{
    os << "========================================\n"
       << "       " << caf.name << "\n"
       << "       " << caf.schoolName << "\n"
       << "========================================\n"
       << "Артикули в менюто: " << caf.menu.size() << "\n"
       << "Потребителски групи: " << caf.userGroups.size() << "\n"
       << "Регистрирани потребители: " << caf.users.size() << "\n"
       << "Общо поръчки: " << caf.orders.size() << "\n"
       << "Общи приходи: " << fixed << setprecision(2)
       << caf.getTotalRevenue() << " лв\n"
       << "========================================\n";
    return os;
}
