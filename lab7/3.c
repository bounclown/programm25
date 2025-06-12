#include <stdio.h>

#define N 4

void fill_matrix(int matrix[N][N], int value) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = value;
}

void multiply(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void print_matrix(const char* name, int matrix[N][N]) {
    printf("Матрица %s:\n", name);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    fill_matrix(A, 1);
    fill_matrix(B, 1);

    multiply(A, B, C);

    if (N < 5) {
        print_matrix("A", A);
        print_matrix("B", B);
        print_matrix("C", C);
    }

    return 0;
}
