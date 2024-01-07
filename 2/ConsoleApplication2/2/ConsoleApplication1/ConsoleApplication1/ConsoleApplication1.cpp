#include <stdio.h>
#include <locale.h>

double powerRecursive(double base, int exponent) {
    if (exponent == 0) {
        return 1.0;
    }
    else if (exponent % 2 == 0) {
        // Четная степень
        double temp = powerRecursive(base, exponent / 2);
        return temp * temp;
    }
    else {
        // Нечетная степень
        return base * powerRecursive(base, exponent - 1);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример использования функции powerRecursive
    double base = 2.0;
    int exponent = 3;
    double result = powerRecursive(base, exponent);
    // Вывод результата
    printf("%lf в степени %d равно %lf\n", base, exponent, result);

    return 0;
}
