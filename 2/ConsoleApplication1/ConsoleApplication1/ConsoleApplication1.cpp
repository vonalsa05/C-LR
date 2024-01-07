#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 1024

// Функция для подсчета длины строки
int countLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Функция для получения перевернутой строки
char* reverseString(const char* str) {
    int length = countLength(str);
    char* reversed = (char*)malloc((length + 1) * sizeof(char));

    if (reversed == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        reversed[i] = str[length - i - 1];
    }
    reversed[length] = '\0';
    return reversed;
}

// Функция для преобразования символов на нечетных позициях в верхний регистр
char* toUpperOdd(const char* str) {
    int length = countLength(str);
    char* result = (char*)malloc((length + 1) * sizeof(char));

    if (result == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        if (i % 2 != 0) {
            result[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] - 'a' + 'A' : str[i];
        }
        else {
            result[i] = str[i];
        }
    }
    result[length] = '\0';
    return result;
}

// Функция для формирования новой строки с символами в определенном порядке
char* rearrangeString(const char* str) {
    int length = countLength(str);
    char* result = (char*)malloc((length + 1) * sizeof(char));

    if (result == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }

    int digitIndex = 0;
    int letterIndex = 0;
    int otherIndex = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result[digitIndex++] = str[i];
        }
        else if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            result[length - letterIndex++ - 1] = str[i];
        }
        else {
            result[length + otherIndex++] = str[i];
        }
    }
    result[length] = '\0';
    return result;
}

// Функция для конкатенации строк в псевдослучайном порядке
char* concatenateStrings(int seed, int numStrings, char** strings) {
    srand(seed);
    char* result = (char*)malloc(1); // Исходный размер памяти для хранения строки
    result[0] = '\0'; // Пустая строка

    if (result == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }

    for (int i = 0; i < numStrings; i++) {
        int position = rand() % (countLength(result) + 1);
        char* temp = (char*)malloc((countLength(result) + countLength(strings[i]) + 1) * sizeof(char));

        if (temp == NULL) {
            // Обработка ошибки выделения памяти
            free(result);
            return NULL;
        }

        snprintf(temp, MAX_STRING_LENGTH, "%.*s%s%.*s", position, result, strings[i], countLength(result) - position, result + position);
        free(result);
        result = temp;
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <flag> <string> [additional arguments]\n", argv[0]);
        return 1;
    }

    char* flag = argv[1];
    const char* inputString = argv[2];

    if (flag[0] == '-') {
        switch (flag[1]) {
        case 'l':
            printf("Length: %d\n", countLength(inputString));
            break;
        case 'r': {
            char* reversed = reverseString(inputString);
            if (reversed != NULL) {
                printf("Reversed: %s\n", reversed);
                free(reversed);
            }
            else {
                printf("Memory allocation error\n");
            }
            break;
        }
        case 'u': {
            char* upperOdd = toUpperOdd(inputString);
            if (upperOdd != NULL) {
                printf("Upper odd: %s\n", upperOdd);
                free(upperOdd);
            }
            else {
                printf("Memory allocation error\n");
            }
            break;
        }
        case 'n': {
            char* rearranged = rearrangeString(inputString);
            if (rearranged != NULL) {
                printf("Rearranged: %s\n", rearranged);
                free(rearranged);
            }
            else {
                printf("Memory allocation error\n");
            }
            break;
        }
        case 'c': {
            if (argc >= 4) {
                int seed = atoi(argv[3]);
                char* concatenated = concatenateStrings(seed, argc - 4, argv + 4);
                if (concatenated != NULL) {
                    printf("Concatenated: %s\n", concatenated);
                    free(concatenated);
                }
                else {
                    printf("Memory allocation error\n");
                }
            }
            else {
                printf("Not enough additional arguments for -c flag\n");
            }
            break;
        }
        default:
            printf("Unknown flag: %s\n", flag);
            return 1;
        }
    }
    else {
        printf("Invalid flag format\n");
        return 1;
    }

    return 0;
}
