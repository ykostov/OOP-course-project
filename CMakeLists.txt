# CMakeLists.txt - Крос-платформена конфигурация
# Работи на Windows, macOS и Linux

cmake_minimum_required(VERSION 3.10)
project(Cafeteria VERSION 1.0 LANGUAGES CXX)

# C++17 стандарт
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include директория
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source файлове
set(SOURCES
    src/Person.cpp
    src/MenuItem.cpp
    src/UserGroup.cpp
    src/User.cpp
    src/Order.cpp
    src/Cafeteria.cpp
    src/utils.cpp
    src/main.cpp
)

# Създаване на изпълним файл
add_executable(cafeteria ${SOURCES})

# Предупреждения при компилация
if(MSVC)
    target_compile_options(cafeteria PRIVATE /W4)
else()
    target_compile_options(cafeteria PRIVATE -Wall -Wextra)
endif()

# Съобщение след успешна компилация
add_custom_command(TARGET cafeteria POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Компилацията е успешна! Стартирайте с: ./cafeteria"
)
