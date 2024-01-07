#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <locale.h>

typedef enum {
    FINITE_REPRESENTATION,
    INFINITE_REPRESENTATION,
    INVALID_ARGUMENT,
} Status;

Status checkFiniteRepresentation(double base, int count, ...) {
    if (base <= 1 || base >= 10) {
        return INVALID_ARGUMENT; // Неподдерживаемое основание системы счисления
    }

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        double fraction = va_arg(args, double);

        if (fraction <= 0 || fraction >= 1) {
            va_end(args);
            return INVALID_ARGUMENT; // Неподдерживаемая десятичная дробь
        }

        // Проверка конечности представления в системе счисления
        double product = fraction * base;
        double intPart;
        double fractPart = modf(product, &intPart);

        if (fractPart != 0) {
            va_end(args);
            return INFINITE_REPRESENTATION; // Бесконечное представление
        }
    }

    va_end(args);
    return FINITE_REPRESENTATION; // Конечное представление
}

int main() {
    setlocale(LC_ALL, "Russian");
    double base = 2; // Задаем основание системы счисления
    int numFractions = 3; // Задаем количество десятичных дробей

    // Пример десятичных дробей (в пределах от 0 до 1)
    double fraction1 = 0.25;
    double fraction2 = 0.5;
    double fraction3 = 0.75;

    // Проверяем, имеют ли дроби конечное представление в двоичной системе
    Status result = checkFiniteRepresentation(base, numFractions, fraction1, fraction2, fraction3);

    switch (result) {
    case FINITE_REPRESENTATION:
        printf("Все дроби имеют конечное представление в системе с основанием %lf.\n", base);
        break;
    case INFINITE_REPRESENTATION:
        printf("Одна из дробей имеет бесконечное представление в системе с основанием %lf.\n", base);
        break;
    case INVALID_ARGUMENT:
        printf("Ошибка: Некорректные аргументы.\n");
        break;
    }

    return 0;
}
