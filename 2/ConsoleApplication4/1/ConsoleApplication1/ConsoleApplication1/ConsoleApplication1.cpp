#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <locale.h>

typedef struct {
    double x, y;
} Point;

bool isConvexPolygon(int numVertices, ...) {
    if (numVertices < 3) {
        // Многоугольник должен иметь не менее трех вершин
        return false;
    }

    va_list args;
    va_start(args, numVertices);

    Point p1 = va_arg(args, Point);
    Point p2 = va_arg(args, Point);
    Point p3;

    int direction = 0; // 0 - не определено, 1 - по часовой стрелке, -1 - против часовой стрелки

    for (int i = 2; i < numVertices; ++i) {
        p3 = va_arg(args, Point);

        double crossProduct = (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);

        if (crossProduct != 0) {
            if (direction == 0) {
                direction = (crossProduct > 0) ? 1 : -1;
            }
            else if ((crossProduct > 0 && direction == -1) || (crossProduct < 0 && direction == 1)) {
                // Нарушение условия выпуклости
                va_end(args);
                return false;
            }
        }

        p1 = p2;
        p2 = p3;
    }

    va_end(args);
    return true;
}

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
    // Пример использования функции для проверки выпуклости многоугольника
    Point p1 = { 0, 0 };
    Point p2 = { 1, 1 };
    Point p3 = { 2, 0 };

    if (isConvexPolygon(3, p1, p2, p3)) {
        printf("Многоугольник выпуклый.\n");
    }
    else {
        printf("Многоугольник не выпуклый.\n");
    }

    // Пример использования функции для вычисления значения многочлена
    double polyResult = evaluatePolynomial(2.0, 3, 1.0, -2.0, 0.5, 3.0);

    printf("Значение многочлена в точке x = 2.0: %lf\n", polyResult);

    return 0;
}
