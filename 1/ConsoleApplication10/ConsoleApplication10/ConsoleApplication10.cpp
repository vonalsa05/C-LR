#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Функция для выделения динамической памяти под матрицу
int** allocateMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для матрицы\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Ошибка выделения памяти для строки матрицы\n");
            exit(EXIT_FAILURE);
        }
    }

    return matrix;
}

// Функция для освобождения динамической памяти, выделенной под матрицу
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для генерации матрицы с произвольными значениями
void generateMatrix(int** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 201 - 100; // значения в диапазоне [-100..100]
        }
    }
}

// Функция для вывода матрицы в стандартный поток вывода
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для умножения двух матриц
int** multiplyMatrices(int** matrix1, int rows1, int cols1,
    int** matrix2, int rows2, int cols2) {
    if (cols1 != rows2) {
        fprintf(stderr, "Ошибка: умножение матриц невозможно (несовпадение размеров)\n");
        exit(EXIT_FAILURE);
    }

    int** result = allocateMatrix(rows1, cols2);

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Функция для вычисления определителя матрицы
int determinant(int** matrix, int size) {
    if (size == 1) {
        return matrix[0][0];
    }

    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int det = 0;
    for (int i = 0; i < size; i++) {
        int** minor = allocateMatrix(size - 1, size - 1);
        for (int j = 1; j < size; j++) {
            for (int k = 0, l = 0; k < size; k++) {
                if (k != i) {
                    minor[j - 1][l++] = matrix[j][k];
                }
            }
        }
        det += (i % 2 == 1 ? -1 : 1) * matrix[0][i] * determinant(minor, size - 1);
        freeMatrix(minor, size - 1);
    }

    return det;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Генерация матриц
    int rows1 = 3, cols1 = 4;
    int rows2 = 4, cols2 = 3;

    int** matrix1 = allocateMatrix(rows1, cols1);
    int** matrix2 = allocateMatrix(rows2, cols2);

    generateMatrix(matrix1, rows1, cols1);
    generateMatrix(matrix2, rows2, cols2);

    // Вывод сгенерированных матриц
    printf("Матрица 1:\n");
    printMatrix(matrix1, rows1, cols1);
    printf("\nМатрица 2:\n");
    printMatrix(matrix2, rows2, cols2);

    // Умножение матриц
    int** resultMatrix = multiplyMatrices(matrix1, rows1, cols1, matrix2, rows2, cols2);
    printf("\nРезультат умножения матриц:\n");
    printMatrix(resultMatrix, rows1, cols2);

    // Вычисление определителя матрицы
    int det1 = determinant(matrix1, rows1);
    int det2 = determinant(matrix2, rows2);

    printf("\nОпределитель матрицы 1: %d\n", det1);
    printf("Определитель матрицы 2: %d\n", det2);

    // Освобождение памяти
    freeMatrix(matrix1, rows1);
    freeMatrix(matrix2, rows2);
    freeMatrix(resultMatrix, rows1);

    return 0;
}
