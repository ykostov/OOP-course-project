#include "utils.h"
#include <iostream>
#include <limits>

using namespace std;

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

double readDouble(const string &prompt, double minVal, double maxVal)
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
