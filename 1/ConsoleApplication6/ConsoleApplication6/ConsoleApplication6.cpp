#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long convertToDecimal(const char* num, int base) {
    long long decimal = 0;
    int len = strlen(num);

    for (int i = 0; i < len; ++i) {
        char digit = num[i];
        int value = isdigit(digit) ? digit - '0' : toupper(digit) - 'A' + 10;

        if (value >= base) {
            // Некорректная цифра для текущей системы счисления
            return -1;
        }

        decimal = decimal * base + value;
    }

    return decimal;
}

int main() {
    FILE* inputFile, * outputFile;
    errno_t err;

    // Используем fopen_s вместо fopen
    if ((err = fopen_s(&inputFile, "input.txt", "r")) != 0 || (err = fopen_s(&outputFile, "output.txt", "w")) != 0) {
        perror("Ошибка открытия файла");
        return -1;
    }

    char buffer[256];

    // Используем fscanf_s вместо fscanf
    while (fscanf_s(inputFile, "%s", buffer, sizeof(buffer)) != EOF) {
        int base = 2;  // Минимальная система счисления, начиная с 2

        while (base <= 36) {
            long long decimal = convertToDecimal(buffer, base);
            if (decimal != -1) {
                fprintf(outputFile, "%s в системе счисления %d равно %lld в десятичной системе\n", buffer, base, decimal);
                break;
            }

            base++;
        }
    }

    // Используем fclose вместо fclose_s, так как fclose_s не предоставляет значительного уровня безопасности по сравнению с fclose
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
