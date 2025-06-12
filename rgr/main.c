
#include "freq.h"

#define WORD_MAX 128

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <входной_файл> <выходной_файл>\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    if (!in) {
        perror("Ошибка открытия входного файла");
        return 1;
    }

    FreqTable* table = create_table();
    char word[WORD_MAX];
    int index = 0;
    int ch;
    int total_words = 0;
    int total_chars = 0;

    while ((ch = fgetc(in)) != EOF) {
        if (isalnum(ch)) {
            if (index < WORD_MAX - 1) {
                word[index++] = tolower(ch);
                total_chars++;
            }
        } else if (index > 0) {
            word[index] = '\0';
            add_word(table, word);
            total_words++;
            index = 0;
        }
    }

    if (index > 0) {
        word[index] = '\0';
        add_word(table, word);
    }

    fclose(in);

    sort_table(table);
    write_table(table, argv[2]);
    free_table(table);

    printf("Всего слов: %d\n", total_words);
    printf("Всего символов (без пробелов и знаков): %d\n", total_chars);

    return 0;
}
