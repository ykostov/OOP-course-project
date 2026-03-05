@echo off
chcp 65001 >nul
echo ========================================
echo    Компилация на проект "Ученически стол"
echo ========================================

:: Проверка за g++
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo ГРЕШКА: g++ не е намерен!
    echo Моля инсталирайте MinGW или TDM-GCC
    echo Изтеглете от: https://www.mingw-w64.org/
    pause
    exit /b 1
)

:: Създаване на build директория
if not exist build mkdir build

echo.
echo Компилиране на обектни файлове...

:: Компилиране на всеки source файл
g++ -Wall -Wextra -std=c++17 -Iinclude -c src/MenuItem.cpp -o build/MenuItem.o
if %errorlevel% neq 0 goto :error

g++ -Wall -Wextra -std=c++17 -Iinclude -c src/UserGroup.cpp -o build/UserGroup.o
if %errorlevel% neq 0 goto :error

g++ -Wall -Wextra -std=c++17 -Iinclude -c src/User.cpp -o build/User.o
if %errorlevel% neq 0 goto :error

g++ -Wall -Wextra -std=c++17 -Iinclude -c src/Order.cpp -o build/Order.o
if %errorlevel% neq 0 goto :error

g++ -Wall -Wextra -std=c++17 -Iinclude -c src/Cafeteria.cpp -o build/Cafeteria.o
if %errorlevel% neq 0 goto :error

g++ -Wall -Wextra -std=c++17 -Iinclude -c src/utils.cpp -o build/utils.o
if %errorlevel% neq 0 goto :error

g++ -Wall -Wextra -std=c++17 -Iinclude -c src/main.cpp -o build/main.o
if %errorlevel% neq 0 goto :error

echo.
echo Линкване...

:: Линкване на изпълнимия файл
g++ build/*.o -o cafeteria.exe
if %errorlevel% neq 0 goto :error

echo.
echo ========================================
echo    Компилацията е УСПЕШНА!
echo    Стартирайте с: cafeteria.exe
echo ========================================
pause
exit /b 0

:error
echo.
echo ========================================
echo    ГРЕШКА при компилация!
echo ========================================
pause
exit /b 1
