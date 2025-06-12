#ifndef FREQ_H
#define FREQ_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INITIAL_CAPACITY 16

typedef struct {
    char* word;
    int count;
} WordFreq;

typedef struct {
    WordFreq* data;
    int size;
    int capacity;
} FreqTable;

FreqTable* create_table();
void add_word(FreqTable* table, const char* word);
void sort_table(FreqTable* table);
void write_table(FreqTable* table, const char* filename);
void free_table(FreqTable* table);

#endif
