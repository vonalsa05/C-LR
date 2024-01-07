#include <stdio.h>
#include <stdarg.h>
#include <locale.h>

// Функция для поиска подстроки в строке
int findSubstring(const char* substring, const char* str) {
    int subLen = 0;
    int strLen = 0;

    // Находим длины подстроки и строки
    while (substring[subLen] != '\0') {
        subLen++;
    }

    while (str[strLen] != '\0') {
        strLen++;
    }

    // Ищем подстроку в строке
    for (int i = 0; i <= strLen - subLen; i++) {
        int j;
        // Проверяем совпадение символов
        for (j = 0; j < subLen; j++) {
            if (str[i + j] != substring[j]) {
                break;
            }
        }

        // Если все символы совпали, возвращаем позицию начала подстроки
        if (j == subLen) {
            return i;
        }
    }

    // Подстрока не найдена
    return -1;
}

// Функция для поиска подстроки в файле
void searchSubstringInFile(const char* substring, const char* filename, ...) {
    // Открываем файл для чтения
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        fprintf(stderr, "Ошибка открытия файла %s\n", filename);
        return;
    }

    // Переменные для хранения текущей строки и ее номера
    char buffer[4096];
    int lineNumber = 0;

    // Читаем файл построчно
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineNumber++;

        // Ищем подстроку в текущей строке
        int position = findSubstring(substring, buffer);
        while (position != -1) {
            // Выводим результат
            printf("Файл: %s, Строка: %d, Позиция: %d\n", filename, lineNumber, position + 1);

            // Ищем следующее вхождение
            position = findSubstring(substring, buffer + position + 1);
        }
    }

    // Закрываем файл
    fclose(file);
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример использования функции
    searchSubstringInFile("example", "file1.txt");
    searchSubstringInFile("example", "file2.txt");
    return 0;
}
