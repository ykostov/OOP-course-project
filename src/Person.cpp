#include "Person.h"

using namespace std;

// Конструктор по подразбиране
Person::Person()
    : fullName("Неизвестен"), idNumber("0") {}

// Конструктор с параметри
Person::Person(const string &name_, const string &id_)
    : fullName("Неизвестен"), idNumber("0")
{
    setFullName(name_);
    setIDNumber(id_);
}

// Виртуален деструктор
Person::~Person() {}

// Getters
string Person::getFullName() const { return fullName; }
string Person::getIDNumber() const { return idNumber; }

// Setters с валидация
void Person::setFullName(const string &n)
{
    fullName = n.empty() ? "Неизвестен" : n;
}

void Person::setIDNumber(const string &id)
{
    idNumber = id.empty() ? "0" : id;
}

void Person::setIDNumber(int id)
{
    idNumber = to_string(id > 0 ? id : 1);
}

// Виртуален метод за извеждане на информация
void Person::printInfo(ostream &os) const
{
    os << "Име: " << fullName << " | ID: " << idNumber;
}

// Предефиниране на оператор <<
ostream &operator<<(ostream &os, const Person &person)
{
    person.printInfo(os);
    return os;
}
