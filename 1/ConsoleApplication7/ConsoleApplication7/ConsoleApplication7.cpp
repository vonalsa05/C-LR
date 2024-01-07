#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define ARRAY_SIZE 10

void fillArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;  // Генерация случайных чисел от 0 до 99
    }
}

void printArray(int array[], int size) {
    wprintf(L"Массив: ");
    for (int i = 0; i < size; i++) {
        wprintf(L"%d ", array[i]);
    }
    wprintf(L"\n");
}

int findMinIndex(int array[], int size) {
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (array[i] < array[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

int findMaxIndex(int array[], int size) {
    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        if (array[i] > array[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void swapElements(int array[], int index1, int index2) {
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

int main() {
    srand(time(NULL));  // Инициализация генератора случайных чисел

    setlocale(LC_ALL, "");  // Установка текущей локали

    int myArray[ARRAY_SIZE];
    fillArray(myArray, ARRAY_SIZE);

    wprintf(L"Исходный ");
    printArray(myArray, ARRAY_SIZE);

    int minIndex = findMinIndex(myArray, ARRAY_SIZE);
    int maxIndex = findMaxIndex(myArray, ARRAY_SIZE);

    wprintf(L"Минимальный элемент: %d (индекс %d)\n", myArray[minIndex], minIndex);
    wprintf(L"Максимальный элемент: %d (индекс %d)\n", myArray[maxIndex], maxIndex);

    swapElements(myArray, minIndex, maxIndex);

    wprintf(L"После обмена ");
    printArray(myArray, ARRAY_SIZE);

    return 0;
}
