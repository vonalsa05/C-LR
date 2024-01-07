#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>

double averageGeometric(int count, ...) {
    if (count <= 0) {
        // Обработка ошибки: неверное количество аргументов
        return 0.0; // Можно выбрать другое значение по умолчанию
    }

    va_list args;
    va_start(args, count);

    double product = 1.0;

    for (int i = 0; i < count; ++i) {
        double value = va_arg(args, double);
        if (value <= 0.0) {
            // Обработка ошибки: неверное значение аргумента
            va_end(args);
            return 0.0; // Можно выбрать другое значение по умолчанию
        }
        product *= value;
    }

    va_end(args);

    return pow(product, 1.0 / count);
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример использования функции averageGeometric
    double result = averageGeometric(3, 2.0, 3.0, 4.0);
    // Вывод результата
    printf("Среднее геометрическое: %lf\n", result);

    return 0;
}
