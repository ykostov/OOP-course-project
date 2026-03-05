@echo off
echo Изтриване на компилирани файлове...

if exist build rmdir /s /q build
if exist cafeteria.exe del cafeteria.exe

echo Готово!
pause
