#include <iostream>
#include <iomanip>
#include <clocale>
#include "Cafeteria.h"
#include "utils.h"

using namespace std;

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
