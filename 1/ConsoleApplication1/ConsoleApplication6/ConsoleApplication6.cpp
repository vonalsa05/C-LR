#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int is_prime(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // число составное
        }
    }
    return 1; // число простое
}

void print_multiples(int num) {
    int count = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % num == 0) {
            printf("%d ", i);
            count++;
        }
    }
    if (count == 0) {
        printf("Нет кратных чисел в пределах 100.\n");
    }
    printf("\n");
}

void print_digits(int num) {
    while (num > 0) {
        printf("%d ", num % 10);
        num /= 10;
    }
    printf("\n");
}

void print_powers(int num) {
    for (int i = 1; i <= 10; i++) {
        int result = 1;
        for (int j = 1; j <= num; j++) {
            result *= i;
            printf("%d^%d = %d\n", i, j, result);
        }
    }
}

void print_sum(int num) {
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        sum += i;
    }
    printf("Сумма чисел от 1 до %d: %d\n", num, sum);
}

void print_factorial(int num) {
    if (num < 0) {
        printf("Факториал отрицательного числа не определен.\n");
        return;
    }

    unsigned long long factorial = 1;
    for (int i = 1; i <= num; i++) {
        factorial *= i;
    }
    printf("Факториал %d: %llu\n", num, factorial);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    if (argc != 3) {
        printf("Использование: %s <число> <флаг>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    switch (argv[2][0]) {
    case 'h':
        print_multiples(num);
        break;
    case 'p':
        if (is_prime(num)) {
            printf("%d - простое число.\n", num);
        }
        else {
            printf("%d - составное число.\n", num);
        }
        break;
    case 's':
        print_digits(num);
        break;
    case 'e':
        if (num <= 10) {
            print_powers(num);
        }
        else {
            printf("Введите число, не превышающее 10, для флага -e.\n");
        }
        break;
    case 'a':
        print_sum(num);
        break;
    case 'f':
        print_factorial(num);
        break;
    default:
        printf("Неизвестный флаг: %c\n", argv[2][0]);
        return 1;
    }

    return 0;
}
