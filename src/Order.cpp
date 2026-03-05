#include "Order.h"
#include <iomanip>
#include <ctime>

using namespace std;

// Конструктор по подразбиране
Order::Order() : orderId("ORD000"), userId("00000"), totalPrice(0.0)
{
    time_t now = time(nullptr);
    timestamp = ctime(&now);
    if (!timestamp.empty() && timestamp.back() == '\n')
    {
        timestamp.pop_back();
    }
}

// Конструктор с параметри
Order::Order(const string &ordId, const string &usrId)
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
string Order::getOrderId() const { return orderId; }
string Order::getUserId() const { return userId; }
double Order::getTotalPrice() const { return totalPrice; }
string Order::getTimestamp() const { return timestamp; }
const vector<string> &Order::getItemNames() const { return itemNames; }
const vector<double> &Order::getItemPrices() const { return itemPrices; }

// Setters
void Order::setOrderId(const string &id) { orderId = id; }
void Order::setUserId(const string &id) { userId = id; }
void Order::setTimestamp(const string &ts) { timestamp = ts; }

// Добавяне на артикул към поръчката
void Order::addItem(const string &name, double price)
{
    itemNames.push_back(name);
    itemPrices.push_back(price);
    totalPrice += price;
}

// Предефиниране на оператор <<
ostream &operator<<(ostream &os, const Order &order)
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
