#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_SIZE 128

void readArray(int arr[], int size) {
    printf("Введите элементы массива (не более %d элементов):\n", size);
    for (int i = 0; i < size; ++i) {
        scanf_s("%d", &arr[i]);
    }
}

void printArray(int arr[], int size) {
    printf("Массив:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int findMaxDistanceIndex(int source[], int size, int currentIndex) {
    int maxDistance = 0;
    int maxDistanceIndex = currentIndex;

    for (int i = 0; i < size; ++i) {
        int distance = abs(currentIndex - i);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxDistanceIndex = i;
        }
    }

    return maxDistanceIndex;
}

void copyMaxDistanceValues(int source[], int dest[], int size) {
    for (int i = 0; i < size; ++i) {
        int currentIndex;
        printf("Введите индекс для элемента %d: ", i);
        scanf_s("%d", &currentIndex);

        if (currentIndex < 0 || currentIndex >= size) {
            printf("Некорректный индекс. Введите снова.\n");
            --i;
            continue;
        }

        int maxDistanceIndex = findMaxDistanceIndex(source, size, currentIndex);
        dest[i] = source[maxDistanceIndex];
    }
}

void copyPrecedingSum(int source[], int dest[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += source[i];
        dest[i] = sum;
    }
}

void copyLesserSum(int source[], int dest[], int size) {
    for (int i = 0; i < size; ++i) {
        int sum = 0;
        for (int j = 0; j < i; ++j) {
            if (source[j] < source[i]) {
                sum += source[j];
            }
        }
        dest[i] = sum;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int originalArray[MAX_SIZE];
    int newArray[MAX_SIZE];

    int size;
    printf("Введите размер массива (не более %d): ", MAX_SIZE);
    scanf_s("%d", &size);

    if (size > 0 && size <= MAX_SIZE) {
        readArray(originalArray, size);

        char choice;
        printf("Выберите вариант (c-e): ");
        scanf_s(" %c", &choice);

        switch (choice) {
        case 'c':
            copyMaxDistanceValues(originalArray, newArray, size);
            break;
        case 'd':
            copyPrecedingSum(originalArray, newArray, size);
            break;
        case 'e':
            copyLesserSum(originalArray, newArray, size);
            break;
        default:
            printf("Некорректный выбор.\n");
            return 1;
        }

        printArray(newArray, size);
    }
    else {
        printf("Некорректный размер массива.\n");
        return 1;
    }

    return 0;
}
