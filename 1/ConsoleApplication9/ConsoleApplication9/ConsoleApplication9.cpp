#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

int convertToDecimal(char* number, int base) {
    int result = 0;
    int power = 0;

    while (*number) {
        char digit = *number;
        int value;

        if (digit >= '0' && digit <= '9') {
            value = digit - '0';
        }
        else if (digit >= 'A' && digit <= 'Z') {
            value = digit - 'A' + 10;
        }
        else if (digit >= 'a' && digit <= 'z') {
            value = digit - 'a' + 10;
        }
        else {
            // Некорректный символ
            return 0;
        }

        if (value >= base) {
            // Некорректная цифра для текущей системы счисления
            return 0;
        }

        result += value * pow(base, power);
        power++;
        number++;
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали

    char input[100];
    int maxMagnitude = 0;

    printf("Введите систему счисления (от 2 до 36): ");
    int base;
    scanf_s("%d", &base);

    while (1) {
        printf("Введите число или введите 'Stop' для завершения: ");
        scanf_s("%s", input, sizeof(input));

        if (_stricmp(input, "Stop") == 0) {
            break;
        }

        int decimalValue = convertToDecimal(input, base);
        int magnitude = abs(decimalValue);

        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
        }
    }

    printf("Максимальное по модулю число в системах с основаниями 9, 18, 27, 36: \n");
    printf("Десятичная: %d\n", maxMagnitude);
    printf("В системе с основанием 9: %o\n", maxMagnitude);
    printf("В системе с основанием 18: %o\n", maxMagnitude);
    printf("В системе с основанием 27: %o\n", maxMagnitude);
    printf("В системе с основанием 36: %o\n", maxMagnitude);

    return 0;
}
