#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// Функция для сложения двух чисел в столбик в заданной системе счисления
char* addInBase(char* num1, char* num2, int base) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = (len1 > len2) ? len1 : len2;

    char* result = (char*)malloc((maxLen + 2) * sizeof(char));
    if (result == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }

    memset(result, '0', maxLen + 1);
    result[maxLen + 1] = '\0';

    int carry = 0;

    for (int i = maxLen - 1; i >= 0; i--) {
        int digit1 = (i >= len1) ? 0 : num1[i] - '0';
        int digit2 = (i >= len2) ? 0 : num2[i] - '0';

        int sum = digit1 + digit2 + carry;
        carry = sum / base;

        result[i] = (sum % base) + '0';
    }

    if (carry > 0) {
        memmove(result + 1, result, maxLen + 1);
        result[0] = carry + '0';
    }

    return result;
}

// Функция для вычисления суммы чисел в заданной системе счисления
char* sumInBase(int base, int numCount, ...) {
    char* result = (char*)malloc(2 * sizeof(char));
    if (result == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }

    strcpy(result, "0");

    va_list args;
    va_start(args, numCount);

    for (int i = 0; i < numCount; i++) {
        char* currentNum = va_arg(args, char*);

        char* tempResult = addInBase(result, currentNum, base);
        free(result);

        if (tempResult == NULL) {
            // Обработка ошибки выделения памяти
            va_end(args);
            return NULL;
        }

        result = tempResult;
    }

    va_end(args);

    return result;
}

int main() {
    int base = 10;

    char* num1 = "123";
    char* num2 = "456";
    char* num3 = "789";

    char* result = sumInBase(base, 3, num1, num2, num3);

    if (result != NULL) {
        printf("Сумма: %s\n", result);
        free(result);
    }
    else {
        printf("Ошибка при вычислении суммы.\n");
    }

    return 0;
}
