#include <stdio.h>
#include <stdarg.h>
#include <locale.h>

double evaluatePolynomial(double x, int degree, ...) {
    va_list args;
    va_start(args, degree);

    double result = 0.0;
    double powerX = 1.0;

    for (int i = 0; i <= degree; ++i) {
        double coefficient = va_arg(args, double);
        result += coefficient * powerX;
        powerX *= x;
    }

    va_end(args);
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример использования функции для вычисления значения многочлена
    double result = evaluatePolynomial(2.0, 3, 1.0, -2.0, 0.5, 3.0);

    printf("Значение многочлена в точке x = 2.0: %lf\n", result);

    return 0;
}
