#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void mergeFiles(FILE* output, char** inputFiles, int numFiles) {
    FILE* input;
    int ch;

    for (int i = 0; i < numFiles; ++i) {
        if (fopen_s(&input, inputFiles[i], "r") != 0) {
            fprintf(stderr, "Unable to open file: %s\n", inputFiles[i]);
            exit(EXIT_FAILURE);
        }

        while ((ch = fgetc(input)) != EOF) {
            fputc(ch, output);
        }

        fclose(input);
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    if (argc < 4) {
        fprintf(stderr, "Usage: %s -fi <file_name> OR %s -cin OR %s -arg <file1> <file2> ... <fileN>\n",
            argv[0], argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    FILE* output;
    if (fopen_s(&output, "output.txt", "w") != 0) {
        fprintf(stderr, "Unable to create output file.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-fi") == 0) {
        FILE* inputList;
        if (fopen_s(&inputList, argv[2], "r") != 0) {
            fprintf(stderr, "Unable to open file list: %s\n", argv[2]);
            fclose(output);
            return EXIT_FAILURE;
        }

        char buffer[256];
        int numFiles = 0;
        while (fgets(buffer, sizeof(buffer), inputList) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character
            ++numFiles;
        }

        rewind(inputList);

        char** inputFiles = (char**)malloc(numFiles * sizeof(char*));
        if (inputFiles == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            fclose(inputList);
            fclose(output);
            return EXIT_FAILURE;
        }

        for (int i = 0; i < numFiles; ++i) {
            inputFiles[i] = (char*)malloc(256 * sizeof(char));
            if (inputFiles[i] == NULL) {
                fprintf(stderr, "Memory allocation error.\n");
                fclose(inputList);
                fclose(output);
                for (int j = 0; j < i; ++j) {
                    free(inputFiles[j]);
                }
                free(inputFiles);
                return EXIT_FAILURE;
            }
            fgets(inputFiles[i], 256, inputList);
            inputFiles[i][strcspn(inputFiles[i], "\n")] = '\0';  // Remove newline character
        }

        mergeFiles(output, inputFiles, numFiles);

        fclose(inputList);
        for (int i = 0; i < numFiles; ++i) {
            free(inputFiles[i]);
        }
        free(inputFiles);
    }
    else if (strcmp(argv[1], "-cin") == 0) {
        printf("Enter file names (Ctrl-D to end input):\n");
        char buffer[256];
        int numFiles = 0;

        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character
            ++numFiles;
        }

        rewind(stdin);

        char** inputFiles = (char**)malloc(numFiles * sizeof(char*));
        if (inputFiles == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            fclose(output);
            return EXIT_FAILURE;
        }

        for (int i = 0; i < numFiles; ++i) {
            inputFiles[i] = (char*)malloc(256 * sizeof(char));
            if (inputFiles[i] == NULL) {
                fprintf(stderr, "Memory allocation error.\n");
                fclose(output);
                for (int j = 0; j < i; ++j) {
                    free(inputFiles[j]);
                }
                free(inputFiles);
                return EXIT_FAILURE;
            }
            fgets(inputFiles[i], 256, stdin);
            inputFiles[i][strcspn(inputFiles[i], "\n")] = '\0';  // Remove newline character
        }

        mergeFiles(output, inputFiles, numFiles);

        for (int i = 0; i < numFiles; ++i) {
            free(inputFiles[i]);
        }
        free(inputFiles);
    }
    else if (strcmp(argv[1], "-arg") == 0) {
        mergeFiles(output, argv + 2, argc - 2);
    }
    else {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        fclose(output);
        return EXIT_FAILURE;
    }

    fclose(output);
    printf("Files merged successfully.\n");

    return EXIT_SUCCESS;
}
