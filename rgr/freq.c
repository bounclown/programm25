#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "freq.h"

FreqTable* create_table() {
    FreqTable* table = malloc(sizeof(FreqTable));
    table->data = malloc(INITIAL_CAPACITY * sizeof(WordFreq));
    table->size = 0;
    table->capacity = INITIAL_CAPACITY;
    return table;
}

void add_word(FreqTable* table, const char* word) {
    for (int i = 0; i < table->size; ++i) {
        if (strcmp(table->data[i].word, word) == 0) {
            table->data[i].count++;
            return;
        }
    }
    if (table->size == table->capacity) {
        table->capacity *= 2;
        table->data = realloc(table->data, table->capacity * sizeof(WordFreq));
    }
    table->data[table->size].word = strdup(word);
    table->data[table->size].count = 1;
    table->size++;
}

int compare(const void* a, const void* b) {
    return ((WordFreq*)b)->count - ((WordFreq*)a)->count;
}

void sort_table(FreqTable* table) {
    qsort(table->data, table->size, sizeof(WordFreq), compare);
}

void write_table(FreqTable* table, const char* filename) {
    FILE* f = fopen(filename, "w");
    for (int i = 0; i < table->size; ++i) {
        fprintf(f, "%s: %d\n", table->data[i].word, table->data[i].count);
    }
    fclose(f);
}

void free_table(FreqTable* table) {
    for (int i = 0; i < table->size; ++i) {
        free(table->data[i].word);
    }
    free(table->data);
    free(table);
}
