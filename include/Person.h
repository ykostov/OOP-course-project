#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

/**
 * @class Person
 * @brief Базов клас, представящ човек с основни лични данни
 *
 * Класът съхранява основна информация за човек - име и идентификационен номер.
 * Служи като базов клас за User и други производни класове.
 */
class Person
{
protected:
    std::string fullName;  // Пълно име
    std::string idNumber;  // Идентификационен номер

public:
    // Конструктор по подразбиране
    Person();

    // Конструктор с параметри
    Person(const std::string &name_, const std::string &id_);

    // Виртуален деструктор за правилно унищожаване на производни класове
    virtual ~Person();

    // Getters
    std::string getFullName() const;
    std::string getIDNumber() const;

    // Setters с валидация
    void setFullName(const std::string &n);
    void setIDNumber(const std::string &id);
    void setIDNumber(int id);

    // Виртуален метод за извеждане на информация
    virtual void printInfo(std::ostream &os) const;

    // Предефиниране на оператор <<
    friend std::ostream &operator<<(std::ostream &os, const Person &person);
};

#endif // PERSON_H
