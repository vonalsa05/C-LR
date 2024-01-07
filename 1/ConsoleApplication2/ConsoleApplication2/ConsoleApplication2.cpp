#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solveQuadraticEquation(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Roots: %.2f, %.2f\n", root1, root2);
    }
    else if (discriminant == 0) {
        double root = -b / (2 * a);
        printf("Root: %.2f\n", root);
    }
    else {
        printf("No real roots\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        return 1;
    }

    char flag = argv[1][1];

    // Объявление переменных перед switch
    double a_q, b_q, c_q;
    int num1_m, num2_m;
    double side1_t, side2_t, side3_t;

    switch (flag) {
    case 'q':
        if (argc != 4) {
            printf("Invalid number of parameters for quadratic equation\n");
            return 1;
        }

        a_q = atof(argv[2]);
        b_q = atof(argv[3]);
        c_q = atof(argv[4]);

        solveQuadraticEquation(a_q, b_q, c_q);
        break;

    case 'm':
        if (argc != 4) {
            printf("Invalid number of parameters for checking divisibility\n");
            return 1;
        }

        num1_m = atoi(argv[2]);
        num2_m = atoi(argv[3]);

        if (num2_m != 0 && num1_m % num2_m == 0) {
            printf("%d is divisible by %d\n", num1_m, num2_m);
        }
        else {
            printf("%d is not divisible by %d\n", num1_m, num2_m);
        }
        break;

    case 't':
        if (argc != 5) {
            printf("Invalid number of parameters for triangle sides\n");
            return 1;
        }

        side1_t = atof(argv[2]);
        side2_t = atof(argv[3]);
        side3_t = atof(argv[4]);

        if (side1_t > 0 && side2_t > 0 && side3_t > 0 &&
            (side1_t + side2_t > side3_t) &&
            (side1_t + side3_t > side2_t) &&
            (side2_t + side3_t > side1_t)) {
            printf("These sides can form a triangle\n");
            double sides_squared[3] = { side1_t * side1_t, side2_t * side2_t, side3_t * side3_t };
            if (sides_squared[0] == sides_squared[1] + sides_squared[2] ||
                sides_squared[1] == sides_squared[0] + sides_squared[2] ||
                sides_squared[2] == sides_squared[0] + sides_squared[1]) {
                printf("It's also a right-angled triangle\n");
            }
        }
        else {
            printf("These sides cannot form a triangle\n");
        }
        break;

    default:
        printf("Unknown flag\n");
        return 1;
    }

    return 0;
}
