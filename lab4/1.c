#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return 1;
    }

    char lines[MAX_LINES][MAX_LENGTH];
    int count = 0;

    while (count < MAX_LINES && fgets(lines[count], MAX_LENGTH, file)) {
        count++;
    }
    fclose(file);

    file = fopen("output.txt", "w");
    if (!file) {
        perror("Ошибка создания файла");
        return 1;
    }
    for (int i = count - 1; i >= 0; i--) {
        fprintf(file, "%s", lines[i]);
    }
    fclose(file);

    printf("Файл output.txt успешно создан!\n");
    
}
