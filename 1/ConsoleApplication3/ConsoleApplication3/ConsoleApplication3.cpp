#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

void excludeDigits(FILE* inputFile, FILE* outputFile) {
    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, outputFile);
        }
    }
}

void countLetters(FILE* inputFile, FILE* outputFile) {
    int ch;
    int letterCount = 0;

    while ((ch = fgetc(inputFile)) != EOF) {
        if (isalpha(ch)) {
            letterCount++;
        }
        else if (ch == '\n') {
            fprintf(outputFile, "   Letters count: %d\n", letterCount);
            letterCount = 0;
        }

        fputc(ch, outputFile);
    }

    if (letterCount > 0) {
        fprintf(outputFile, "   Letters count: %d\n", letterCount);
    }
}

void countNonAlphanumeric(FILE* inputFile, FILE* outputFile) {
    int ch;
    int nonAlphanumericCount = 0;

    while ((ch = fgetc(inputFile)) != EOF) {
        if (!isalnum(ch) && !isspace(ch)) {
            nonAlphanumericCount++;
        }
        else if (ch == '\n') {
            fprintf(outputFile, "   Non-alphanumeric count: %d\n", nonAlphanumericCount);
            nonAlphanumericCount = 0;
        }

        fputc(ch, outputFile);
    }

    if (nonAlphanumericCount > 0) {
        fprintf(outputFile, "   Non-alphanumeric count: %d\n", nonAlphanumericCount);
    }
}

void replaceWithAscii(FILE* inputFile, FILE* outputFile) {
    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (!isdigit(ch)) {
            fprintf(outputFile, "%d", ch);
        }
        else {
            fputc(ch, outputFile);
        }
    }
}

void transformLexemes(FILE* inputFile, FILE* outputFile) {
    int ch;
    int lexemeCount = 0;
    int isUpperCase = 1;

    while ((ch = fgetc(inputFile)) != EOF) {
        if (isalpha(ch)) {
            if (lexemeCount % 2 == 1) {
                if (isUpperCase) {
                    fputc(tolower(ch), outputFile);
                }
                else {
                    fputc(toupper(ch), outputFile);
                }
            }
            else if (lexemeCount % 5 == 4) {
                fprintf(outputFile, "%d", ch);
            }
            else {
                fputc(ch, outputFile);
            }

            lexemeCount++;
        }
        else if (ch == ' ' || ch == '\n') {
            lexemeCount = 0;
            fputc(ch, outputFile);
        }
        else {
            fputc(ch, outputFile);
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    if (argc < 3) {
        printf("Usage: %s -flag input_file [output_file]\n", argv[0]);
        return 1;
    }

    const char* flag = argv[1];
    const char* inputFileName = argv[2];
    const char* outputFileName = (argc == 4) ? argv[3] : "out_";

    FILE* inputFile;
    FILE* outputFile;

    if (fopen_s(&inputFile, inputFileName, "r") != 0) {
        perror("Error opening input file");
        return 1;
    }

    if (fopen_s(&outputFile, outputFileName, "w") != 0) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    if (strstr(flag, "-nd") != NULL) {
        excludeDigits(inputFile, outputFile);
    }
    else if (strstr(flag, "-ni") != NULL) {
        countLetters(inputFile, outputFile);
    }
    else if (strstr(flag, "-ns") != NULL) {
        countNonAlphanumeric(inputFile, outputFile);
    }
    else if (strstr(flag, "-na") != NULL) {
        replaceWithAscii(inputFile, outputFile);
    }
    else if (strstr(flag, "-nf") != NULL) {
        transformLexemes(inputFile, outputFile);
    }
    else {
        printf("Invalid flag\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
