# Makefile за проекта "Ученически стол"

# Компилатор и флагове
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INCLUDE_DIR)

# Директории
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Изходен файл
TARGET = cafeteria

# Сорс файлове
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Обектни файлове
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Главна цел
all: $(BUILD_DIR) $(TARGET)

# Създаване на директорията за build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Линкване
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Компилацията е успешна! Стартирайте с: ./$(TARGET)"

# Компилиране на обектни файлове
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Почистване
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Прекомпилиране
rebuild: clean all

# Debug версия
debug: CXXFLAGS += -g -DDEBUG
debug: clean all

# Release версия с оптимизации
release: CXXFLAGS += -O2
release: clean all

# Помощ
help:
	@echo "Налични команди:"
	@echo "  make          - Компилира проекта"
	@echo "  make clean    - Изтрива компилираните файлове"
	@echo "  make rebuild  - Прекомпилира проекта"
	@echo "  make debug    - Компилира с debug информация"
	@echo "  make release  - Компилира с оптимизации"
	@echo "  make help     - Показва тази помощ"

.PHONY: all clean rebuild debug release help
