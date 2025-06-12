#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int** A;
int** B;
int** C;
int N, THREADS;

typedef struct {
    int start_row;
    int end_row;
} ThreadArg;

void* thread_multiply(void* arg) {
    ThreadArg* range = (ThreadArg*)arg;

    for (int i = range->start_row; i < range->end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
    }

    return NULL;
}

int** alloc_matrix(int n) {
    int** mat = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i)
        mat[i] = malloc(n * sizeof(int));
    return mat;
}

void fill_matrix(int** mat, int value) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            mat[i][j] = value;
}

void free_matrix(int** mat) {
    for (int i = 0; i < N; ++i)
        free(mat[i]);
    free(mat);
}

void print_matrix(const char* name, int** mat) {
    printf("Матрица %s:\n", name);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Использование: %s <размер_матрицы_N> <кол-во_потоков>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    THREADS = atoi(argv[2]);

    if (THREADS <= 0 || N <= 0 || N % THREADS != 0) {
        printf("Ошибка: N и THREADS должны быть положительными, и N делиться на THREADS.\n");
        return 1;
    }

    A = alloc_matrix(N);
    B = alloc_matrix(N);
    C = alloc_matrix(N);

    fill_matrix(A, 1);
    fill_matrix(B, 1);

    pthread_t threads[THREADS];
    ThreadArg args[THREADS];

    int rows_per_thread = N / THREADS;

    for (int i = 0; i < THREADS; ++i) {
        args[i].start_row = i * rows_per_thread;
        args[i].end_row = (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, thread_multiply, &args[i]);
    }

    for (int i = 0; i < THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    print_matrix("A", A);
    print_matrix("B", B);
    print_matrix("C", C);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);

    return 0;
}

