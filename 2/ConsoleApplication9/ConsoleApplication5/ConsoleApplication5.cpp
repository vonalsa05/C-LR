#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

// Структура для представления многочлена
typedef struct {
    int degree;         // Степень многочлена
    double* coefficients; // Коэффициенты многочлена
} Polynomial;

// Функция для вычисления коэффициентов многочлена (x - a)
int calculate_coefficients(double epsilon, double a, Polynomial* result, int count, ...) {
    va_list args;
    va_start(args, count);

    // Выделяем память под коэффициенты многочлена (x - a)
    result->degree = count;
    result->coefficients = (double*)malloc((count + 1) * sizeof(double));

    if (result->coefficients == NULL) {
        va_end(args);
        return -1; // Ошибка выделения памяти
    }

    // Вычисляем коэффициенты многочлена (x - a)
    for (int i = 0; i <= count; ++i) {
        double fi = va_arg(args, double);
        result->coefficients[i] = fi;

        for (int j = i - 1; j >= 0; --j) {
            result->coefficients[j] = (result->coefficients[j] - a * result->coefficients[j + 1]) / (i - j);
        }
    }

    va_end(args);

    return 0; // Успешное завершение
}

// Функция для освобождения памяти, выделенной под коэффициенты многочлена
void free_polynomial(Polynomial* poly) {
    free(poly->coefficients);
}

int main() {
    double epsilon = 1e-6;
    double a = 2.0;

    // Пример многочлена: f(x) = 2x^2 + 3x + 4
    Polynomial poly;
    int status = calculate_coefficients(epsilon, a, &poly, 3, 4.0, 3.0, 2.0);

    if (status == 0) {
        printf("Original polynomial coefficients: ");
        for (int i = 0; i <= 2; ++i) {
            printf("%f ", poly.coefficients[i]);
        }

        // Используйте poly.coefficients для работы с коэффициентами многочлена (x - a)

        free_polynomial(&poly); // Освобождаем память
    }
    else {
        printf("Error allocating memory for coefficients.\n");
    }

    return 0;
}
