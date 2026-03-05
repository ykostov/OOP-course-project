#ifndef UTILS_H
#define UTILS_H

#include <string>

// Помощни функции за валидация на вход
int readInt(const std::string &prompt, int minVal, int maxVal);
double readDouble(const std::string &prompt, double minVal, double maxVal = 10000.0);
std::string readNonEmpty(const std::string &prompt);

#endif // UTILS_H
