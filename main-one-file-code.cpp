#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <ctime>
using namespace std;

// ==================== Помощни функции за валидация ====================

int readInt(const string &prompt, int minVal, int maxVal)
{
    while (true)
    {
        cout << prompt;
        int x;
        if (cin >> x && x >= minVal && x <= maxVal)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "Невалидно число. Моля въведете число между "
             << minVal << " и " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readDouble(const string &prompt, double minVal, double maxVal = 10000.0)
{
    while (true)
    {
        cout << prompt;
        double x;
        if (cin >> x && x >= minVal && x <= maxVal)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "Невалидно число. Моля въведете число между "
             << minVal << " и " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readNonEmpty(const string &prompt)
{
    while (true)
    {
        cout << prompt;
        string s;
        getline(cin, s);
        if (!s.empty())
            return s;
        cout << "Полето не може да бъде празно.\n";
    }
}

// ==================== Клас MenuItem (Артикул от менюто) ====================
// Представя единичен продукт в менюто на стола

class MenuItem
{
private:
    string name;      // Име на артикула
    string category;  // Категория: "Основно", "Салата", "Десерт", "Напитка"
    double basePrice; // Базова цена в лева
    int calories;     // Калории
    bool available;   // Наличен ли е в момента

public:
    // Конструктор по подразбиране
    MenuItem()
        : name("Неизвестен"), category("Друго"),
          basePrice(0.0), calories(0), available(true) {}

    // Конструктор с параметри
    MenuItem(const string &name_, const string &category_,
             double price_, int cal_, bool avail_ = true)
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
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getBasePrice() const { return basePrice; }
    int getCalories() const { return calories; }
    bool isAvailable() const { return available; }

    // Setters с валидация
    void setName(const string &n)
    {
        name = n.empty() ? "Неизвестен" : n;
    }

    void setCategory(const string &c)
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

    void setBasePrice(double p)
    {
        basePrice = (p < 0.0) ? 0.0 : ((p > 100.0) ? 100.0 : p);
    }

    void setCalories(int c)
    {
        calories = (c < 0) ? 0 : ((c > 5000) ? 5000 : c);
    }

    void setAvailable(bool a) { available = a; }

    // Предефиниране на оператор <<
    friend ostream &operator<<(ostream &os, const MenuItem &item)
    {
        os << "Артикул: " << item.name
           << " | Категория: " << item.category
           << " | Цена: " << fixed << setprecision(2) << item.basePrice << " лв"
           << " | Калории: " << item.calories
           << " | " << (item.available ? "Наличен" : "Изчерпан");
        return os;
    }
};

// ==================== Клас UserGroup (Потребителска група) ====================
// Представя група потребители с определена отстъпка/надценка

class UserGroup
{
private:
    string groupName;       // Име на групата
    double discountPercent; // Отстъпка в % (положителна = отстъпка, отрицателна = надценка)
    string description;     // Описание на групата
    int maxDailyOrders;     // Максимален брой поръчки на ден

public:
    // Конструктор по подразбиране
    UserGroup()
        : groupName("Гост"), discountPercent(0.0),
          description("Без отстъпка"), maxDailyOrders(3) {}

    // Конструктор с параметри
    UserGroup(const string &name_, double discount_,
              const string &desc_ = "", int maxOrders_ = 5)
        : groupName("Гост"), discountPercent(0.0),
          description("Без отстъпка"), maxDailyOrders(3)
    {
        setGroupName(name_);
        setDiscountPercent(discount_);
        setDescription(desc_);
        setMaxDailyOrders(maxOrders_);
    }

    // Getters
    string getGroupName() const { return groupName; }
    double getDiscountPercent() const { return discountPercent; }
    string getDescription() const { return description; }
    int getMaxDailyOrders() const { return maxDailyOrders; }

    // Setters с валидация
    void setGroupName(const string &n)
    {
        groupName = n.empty() ? "Гост" : n;
    }

    void setDiscountPercent(double d)
    {
        // Ограничаваме между -50% (надценка) и +50% (отстъпка)
        discountPercent = (d < -50.0) ? -50.0 : ((d > 50.0) ? 50.0 : d);
    }

    void setDescription(const string &d)
    {
        description = d.empty() ? "Без описание" : d;
    }

    void setMaxDailyOrders(int m)
    {
        maxDailyOrders = (m < 1) ? 1 : ((m > 10) ? 10 : m);
    }

    // Изчислява крайна цена след отстъпка/надценка
    double applyDiscount(double originalPrice) const
    {
        return originalPrice * (1.0 - discountPercent / 100.0);
    }

    // Предефиниране на оператор <<
    friend ostream &operator<<(ostream &os, const UserGroup &group)
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
};

// ==================== Клас User (Потребител) ====================
// Представя потребител на ученическия стол

class User
{
private:
    string fullName;  // Пълно име
    string idNumber;  // Идентификационен номер (ЕГН/номер на ученик)
    string groupName; // Принадлежност към група
    double balance;   // Баланс в лева
    int ordersToday;  // Брой поръчки днес

public:
    // Конструктор по подразбиране
    User()
        : fullName("Неизвестен"), idNumber("0"),
          groupName("Гост"), balance(0.0), ordersToday(0) {}

    // Конструктор с параметри (ID се задава автоматично от Cafeteria)
    User(const string &name_, int id_,
         const string &group_, double bal_ = 0.0)
        : fullName("Неизвестен"), idNumber("0"),
          groupName("Гост"), balance(0.0), ordersToday(0)
    {
        setFullName(name_);
        setIDNumber(id_);
        setGroupName(group_);
        setBalance(bal_);
    }

    // Конструктор за зареждане от файл (с string ID)
    User(const string &name_, const string &id_,
         const string &group_, double bal_)
        : fullName("Неизвестен"), idNumber("0"),
          groupName("Гост"), balance(0.0), ordersToday(0)
    {
        setFullName(name_);
        setIDNumber(id_);
        setGroupName(group_);
        setBalance(bal_);
    }

    // Getters
    string getFullName() const { return fullName; }
    string getIDNumber() const { return idNumber; }
    string getGroupName() const { return groupName; }
    double getBalance() const { return balance; }
    int getOrdersToday() const { return ordersToday; }

    // Setters с валидация
    void setFullName(const string &n)
    {
        fullName = n.empty() ? "Неизвестен" : n;
    }

    void setIDNumber(int id)
    {
        idNumber = to_string(id > 0 ? id : 1);
    }

    void setIDNumber(const string &id)
    {
        idNumber = id.empty() ? "0" : id;
    }

    void setGroupName(const string &g)
    {
        groupName = g.empty() ? "Гост" : g;
    }

    void setBalance(double b)
    {
        balance = (b < 0.0) ? 0.0 : ((b > 1000.0) ? 1000.0 : b);
    }

    void setOrdersToday(int o)
    {
        ordersToday = (o < 0) ? 0 : o;
    }

    // Добавяне на средства към баланса
    bool addFunds(double amount)
    {
        if (amount <= 0 || amount > 500)
            return false;
        balance += amount;
        if (balance > 1000)
            balance = 1000;
        return true;
    }

    // Теглене на средства (при поръчка)
    bool deductFunds(double amount)
    {
        if (amount <= 0 || amount > balance)
            return false;
        balance -= amount;
        ordersToday++;
        return true;
    }

    // Нулиране на дневните поръчки (нов ден)
    void resetDailyOrders() { ordersToday = 0; }

    // Предефиниране на оператор <<
    friend ostream &operator<<(ostream &os, const User &user)
    {
        os << "Потребител: " << user.fullName
           << " | ID: " << user.idNumber
           << " | Група: " << user.groupName
           << " | Баланс: " << fixed << setprecision(2) << user.balance << " лв"
           << " | Поръчки днес: " << user.ordersToday;
        return os;
    }
};

// ==================== Клас Order (Поръчка) ====================
// Представя единична поръчка в стола

class Order
{
private:
    string orderId;            // ID на поръчката
    string userId;             // ID на потребителя
    vector<string> itemNames;  // Имена на поръчаните артикули
    vector<double> itemPrices; // Цени (след отстъпка)
    double totalPrice;         // Обща сума
    string timestamp;          // Време на поръчката

public:
    // Конструктор по подразбиране
    Order() : orderId("ORD000"), userId("00000"), totalPrice(0.0)
    {
        time_t now = time(nullptr);
        timestamp = ctime(&now);
        if (!timestamp.empty() && timestamp.back() == '\n')
        {
            timestamp.pop_back();
        }
    }

    // Конструктор с параметри
    Order(const string &ordId, const string &usrId)
        : orderId(ordId), userId(usrId), totalPrice(0.0)
    {
        time_t now = time(nullptr);
        timestamp = ctime(&now);
        if (!timestamp.empty() && timestamp.back() == '\n')
        {
            timestamp.pop_back();
        }
    }

    // Getters
    string getOrderId() const { return orderId; }
    string getUserId() const { return userId; }
    double getTotalPrice() const { return totalPrice; }
    string getTimestamp() const { return timestamp; }
    const vector<string> &getItemNames() const { return itemNames; }
    const vector<double> &getItemPrices() const { return itemPrices; }

    // Setters
    void setOrderId(const string &id) { orderId = id; }
    void setUserId(const string &id) { userId = id; }
    void setTimestamp(const string &ts) { timestamp = ts; }

    // Добавяне на артикул към поръчката
    void addItem(const string &name, double price)
    {
        itemNames.push_back(name);
        itemPrices.push_back(price);
        totalPrice += price;
    }

    // Предефиниране на оператор <<
    friend ostream &operator<<(ostream &os, const Order &order)
    {
        os << "Поръчка #" << order.orderId
           << " | Потребител: " << order.userId
           << " | Време: " << order.timestamp
           << "\n   Артикули:\n";
        for (size_t i = 0; i < order.itemNames.size(); i++)
        {
            os << "      - " << order.itemNames[i]
               << ": " << fixed << setprecision(2) << order.itemPrices[i] << " лв\n";
        }
        os << "   ОБЩО: " << fixed << setprecision(2) << order.totalPrice << " лв";
        return os;
    }
};

// ==================== Клас Cafeteria (Ученически стол) ====================
// Главен клас, който управлява цялата система

class Cafeteria
{
private:
    string name;                  // Име на стола
    string schoolName;            // Име на училището
    vector<MenuItem> menu;        // Меню с артикули
    vector<UserGroup> userGroups; // Потребителски групи
    vector<User> users;           // Регистрирани потребители
    vector<Order> orders;         // История на поръчките
    int nextOrderId;              // Следващ номер на поръчка
    int nextUserId;               // Следващ номер на потребител

public:
    // Конструктор по подразбиране
    Cafeteria()
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
    Cafeteria(const string &cafeName, const string &school)
        : name(cafeName), schoolName(school), nextOrderId(1), nextUserId(1) {}

    // Getters
    string getName() const { return name; }
    string getSchoolName() const { return schoolName; }
    const vector<MenuItem> &getMenu() const { return menu; }
    const vector<UserGroup> &getUserGroups() const { return userGroups; }
    const vector<User> &getUsers() const { return users; }
    vector<User> &getUsers() { return users; }
    const vector<Order> &getOrders() const { return orders; }

    // Setters
    void setName(const string &n) { name = n.empty() ? "Ученически стол" : n; }
    void setSchoolName(const string &s) { schoolName = s.empty() ? "Неизвестно" : s; }

    // Добавяне на артикул в менюто
    void addMenuItem(const MenuItem &item) { menu.push_back(item); }

    // Добавяне на потребителска група
    void addUserGroup(const UserGroup &group) { userGroups.push_back(group); }

    // Добавяне на потребител (ID се генерира автоматично)
    int addUser(const string &name, const string &groupName, double balance = 0.0)
    {
        int newId = nextUserId++;
        users.push_back(User(name, newId, groupName, balance));
        return newId;
    }

    // Търсене на потребител по ID
    User *findUserByID(const string &id)
    {
        for (auto &u : users)
        {
            if (u.getIDNumber() == id)
                return &u;
        }
        return nullptr;
    }

    // Търсене на група по име
    const UserGroup *findGroupByName(const string &name) const
    {
        for (const auto &g : userGroups)
        {
            if (g.getGroupName() == name)
                return &g;
        }
        return nullptr;
    }

    // Създаване на поръчка
    bool createOrder(const string &userId, const vector<int> &itemIndices)
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
    double getTotalRevenue() const
    {
        double sum = 0.0;
        for (const auto &o : orders)
        {
            sum += o.getTotalPrice();
        }
        return sum;
    }

    // Запис във файл
    void saveToFile(const string &filename) const
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
    void loadFromFile(const string &filename)
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
    friend ostream &operator<<(ostream &os, const Cafeteria &caf)
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
};

// ==================== Менюта ====================

void showMainMenu()
{
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║     СИСТЕМА ЗА УПРАВЛЕНИЕ НА СТОЛ    ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║  1. Настройки на стола               ║\n";
    cout << "║  2. Управление на менюто             ║\n";
    cout << "║  3. Управление на групи              ║\n";
    cout << "║  4. Управление на потребители        ║\n";
    cout << "║  5. Нова поръчка                     ║\n";
    cout << "║  6. Преглед на информация            ║\n";
    cout << "║  7. Запис във файл                   ║\n";
    cout << "║  8. Зареждане от файл                ║\n";
    cout << "║  0. Изход                            ║\n";
    cout << "╚══════════════════════════════════════╝\n";
}

void setupCafeteria(Cafeteria &caf)
{
    string cafName = readNonEmpty("Име на стола: ");
    string schoolName = readNonEmpty("Име на училището: ");
    caf.setName(cafName);
    caf.setSchoolName(schoolName);
    cout << "Настройките са запазени.\n";
}

void addMenuItemMenu(Cafeteria &caf)
{
    cout << "\n--- Добавяне на артикул ---\n";
    string name = readNonEmpty("Име на артикула: ");

    cout << "Категории: Основно, Салата, Супа, Десерт, Напитка, Закуска\n";
    string category = readNonEmpty("Категория: ");

    double price = readDouble("Цена (лв): ", 0.01, 50.0);
    int calories = readInt("Калории: ", 0, 2000);

    caf.addMenuItem(MenuItem(name, category, price, calories, true));
    cout << "Артикулът е добавен успешно!\n";
}

void showMenu(const Cafeteria &caf)
{
    cout << "\n--- МЕНЮ ---\n";
    const auto &menu = caf.getMenu();
    if (menu.empty())
    {
        cout << "Менюто е празно.\n";
        return;
    }
    for (size_t i = 0; i < menu.size(); i++)
    {
        cout << i << ") " << menu[i] << "\n";
    }
}

void menuManagement(Cafeteria &caf)
{
    while (true)
    {
        cout << "\n--- Управление на менюто ---\n";
        cout << "1. Добави артикул\n";
        cout << "2. Покажи меню\n";
        cout << "0. Назад\n";

        int choice = readInt("Избор: ", 0, 2);
        if (choice == 0)
            break;
        else if (choice == 1)
            addMenuItemMenu(caf);
        else if (choice == 2)
            showMenu(caf);
    }
}

void addUserGroupMenu(Cafeteria &caf)
{
    cout << "\n--- Добавяне на потребителска група ---\n";
    string name = readNonEmpty("Име на групата: ");

    cout << "Отстъпка (положително число = отстъпка, отрицателно = надценка)\n";
    double discount = readDouble("Процент: ", -50.0, 50.0);

    string desc = readNonEmpty("Описание: ");
    int maxOrders = readInt("Максимални поръчки на ден: ", 1, 10);

    caf.addUserGroup(UserGroup(name, discount, desc, maxOrders));
    cout << "Групата е добавена успешно!\n";
}

void showGroups(const Cafeteria &caf)
{
    cout << "\n--- ПОТРЕБИТЕЛСКИ ГРУПИ ---\n";
    const auto &groups = caf.getUserGroups();
    if (groups.empty())
    {
        cout << "Няма дефинирани групи.\n";
        return;
    }
    for (size_t i = 0; i < groups.size(); i++)
    {
        cout << i << ") " << groups[i] << "\n\n";
    }
}

void groupManagement(Cafeteria &caf)
{
    while (true)
    {
        cout << "\n--- Управление на групи ---\n";
        cout << "1. Добави група\n";
        cout << "2. Покажи групи\n";
        cout << "0. Назад\n";

        int choice = readInt("Избор: ", 0, 2);
        if (choice == 0)
            break;
        else if (choice == 1)
            addUserGroupMenu(caf);
        else if (choice == 2)
            showGroups(caf);
    }
}

void addUserMenu(Cafeteria &caf)
{
    if (caf.getUserGroups().empty())
    {
        cout << "Първо добавете поне една група!\n";
        return;
    }

    cout << "\n--- Добавяне на потребител ---\n";
    string name = readNonEmpty("Пълно име: ");

    cout << "Налични групи:\n";
    const auto &groups = caf.getUserGroups();
    for (size_t i = 0; i < groups.size(); i++)
    {
        cout << i << ") " << groups[i].getGroupName() << "\n";
    }
    int groupIdx = readInt("Изберете група: ", 0, (int)groups.size() - 1);

    double balance = readDouble("Начален баланс (лв): ", 0.0, 500.0);

    int newId = caf.addUser(name, groups[groupIdx].getGroupName(), balance);
    cout << "Потребителят е добавен успешно с ID: " << newId << "\n";
}

void showUsers(const Cafeteria &caf)
{
    cout << "\n--- ПОТРЕБИТЕЛИ ---\n";
    const auto &users = caf.getUsers();
    if (users.empty())
    {
        cout << "Няма регистрирани потребители.\n";
        return;
    }
    for (size_t i = 0; i < users.size(); i++)
    {
        cout << i << ") " << users[i] << "\n";
    }
}

void addFundsMenu(Cafeteria &caf)
{
    if (caf.getUsers().empty())
    {
        cout << "Няма регистрирани потребители!\n";
        return;
    }

    showUsers(caf);
    int idx = readInt("Изберете потребител: ", 0, (int)caf.getUsers().size() - 1);
    double amount = readDouble("Сума за добавяне (лв): ", 0.01, 500.0);

    if (caf.getUsers()[idx].addFunds(amount))
    {
        cout << "Средствата са добавени. Нов баланс: "
             << fixed << setprecision(2) << caf.getUsers()[idx].getBalance() << " лв\n";
    }
    else
    {
        cout << "Грешка при добавяне на средства!\n";
    }
}

void userManagement(Cafeteria &caf)
{
    while (true)
    {
        cout << "\n--- Управление на потребители ---\n";
        cout << "1. Добави потребител\n";
        cout << "2. Покажи потребители\n";
        cout << "3. Добави средства към баланс\n";
        cout << "0. Назад\n";

        int choice = readInt("Избор: ", 0, 3);
        if (choice == 0)
            break;
        else if (choice == 1)
            addUserMenu(caf);
        else if (choice == 2)
            showUsers(caf);
        else if (choice == 3)
            addFundsMenu(caf);
    }
}

void createOrderMenu(Cafeteria &caf)
{
    if (caf.getUsers().empty())
    {
        cout << "Няма регистрирани потребители!\n";
        return;
    }
    if (caf.getMenu().empty())
    {
        cout << "Менюто е празно!\n";
        return;
    }

    cout << "\n--- НОВА ПОРЪЧКА ---\n";
    showUsers(caf);
    string userId = readNonEmpty("Въведете ID на потребител: ");

    User *user = caf.findUserByID(userId);
    if (!user)
    {
        cout << "Потребителят не е намерен!\n";
        return;
    }

    const UserGroup *group = caf.findGroupByName(user->getGroupName());
    if (group)
    {
        cout << "Група: " << group->getGroupName();
        if (group->getDiscountPercent() > 0)
        {
            cout << " (отстъпка " << group->getDiscountPercent() << "%)";
        }
        else if (group->getDiscountPercent() < 0)
        {
            cout << " (надценка " << (-group->getDiscountPercent()) << "%)";
        }
        cout << "\n";
    }

    cout << "\nНаличен баланс: " << fixed << setprecision(2)
         << user->getBalance() << " лв\n\n";

    showMenu(caf);

    cout << "\nВъведете индексите на артикулите (разделени с интервал), -1 за край:\n";
    vector<int> items;
    while (true)
    {
        int idx = readInt("Артикул: ", -1, (int)caf.getMenu().size() - 1);
        if (idx == -1)
            break;
        items.push_back(idx);
        cout << "Добавено: " << caf.getMenu()[idx].getName() << "\n";
    }

    if (items.empty())
    {
        cout << "Поръчката е празна.\n";
        return;
    }

    caf.createOrder(userId, items);
}

void showInfo(const Cafeteria &caf)
{
    while (true)
    {
        cout << "\n--- Преглед на информация ---\n";
        cout << "1. Обща информация за стола\n";
        cout << "2. Меню\n";
        cout << "3. Групи\n";
        cout << "4. Потребители\n";
        cout << "5. История на поръчките\n";
        cout << "0. Назад\n";

        int choice = readInt("Избор: ", 0, 5);
        if (choice == 0)
            break;
        else if (choice == 1)
            cout << caf;
        else if (choice == 2)
            showMenu(caf);
        else if (choice == 3)
            showGroups(caf);
        else if (choice == 4)
            showUsers(caf);
        else if (choice == 5)
        {
            cout << "\n--- ИСТОРИЯ НА ПОРЪЧКИТЕ ---\n";
            const auto &orders = caf.getOrders();
            if (orders.empty())
            {
                cout << "Няма поръчки.\n";
            }
            else
            {
                for (const auto &o : orders)
                {
                    cout << o << "\n\n";
                }
            }
        }
    }
}

// ==================== Главна функция ====================

int main()
{
    // Настройка за български символи (ако е възможно)
    setlocale(LC_ALL, "");

    Cafeteria cafeteria;

    cout << "╔══════════════════════════════════════╗\n";
    cout << "║  Добре дошли в системата за         ║\n";
    cout << "║  управление на ученически стол!     ║\n";
    cout << "╚══════════════════════════════════════╝\n";

    while (true)
    {
        showMainMenu();
        int choice = readInt("Вашият избор: ", 0, 8);

        switch (choice)
        {
        case 0:
            cout << "Довиждане!\n";
            return 0;
        case 1:
            setupCafeteria(cafeteria);
            break;
        case 2:
            menuManagement(cafeteria);
            break;
        case 3:
            groupManagement(cafeteria);
            break;
        case 4:
            userManagement(cafeteria);
            break;
        case 5:
            createOrderMenu(cafeteria);
            break;
        case 6:
            showInfo(cafeteria);
            break;
        case 7:
        {
            string fname = readNonEmpty("Име на файл за запис: ");
            cafeteria.saveToFile(fname);
            break;
        }
        case 8:
        {
            string fname = readNonEmpty("Име на файл за зареждане: ");
            cafeteria.loadFromFile(fname);
            break;
        }
        }
    }

    return 0;
}