#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    FILE* inputFile, * outputFile;
    char inputFileName[] = "input.txt";
    char outputFileName[] = "output.txt";

    // Открытие файла для чтения
    if (fopen_s(&inputFile, inputFileName, "r") != 0) {
        perror("Не удалось открыть файл для чтения");
        return EXIT_FAILURE;
    }

    // Открытие файла для записи
    if (fopen_s(&outputFile, outputFileName, "w") != 0) {
        perror("Не удалось открыть файл для записи");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    // Чтение, перестановка столбцов и запись в новый файл
    int col1, col2, col3;
    while (fscanf_s(inputFile, "%d %d %d", &col1, &col2, &col3) == 3) {
        fprintf(outputFile, "%d %d %d\n", col3, col1, col2);
    }

    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);

    printf("Перестановка столбцов выполнена успешно. Результат сохранен в %s\n", outputFileName);

    return EXIT_SUCCESS;
}
