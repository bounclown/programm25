#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Cf = 0;
int Mf = 0;

void Quicksort(int L, int R, int a[]) {
    int x = a[L];
    int i = L;
    int j = R;
    while (i <= j) {
        Cf++;
        while (a[i] < x) {
            Cf++;
            i++;
        }
        Cf++;
        while (a[j] > x) {
            Cf++;
            j--;
        }
        Cf++;
        if (i <= j) {
            if (i != j) {
                Mf += 3;
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
            i++;
            j--;
        }
    }
    if (L < j)
        Quicksort(L, j, a);
    if (i < R)
        Quicksort(i, R, a);
}

void generateArray(int arr[], int n, int type) {
    switch(type) {
        case 0:
            for (int i = 0; i < n; i++) arr[i] = n - i;
            break;
        case 1:
            for (int i = 0; i < n; i++) arr[i] = rand() % (2*n);
            break;
        case 2:
            for (int i = 0; i < n; i++) arr[i] = i + 1;
            break;
    }
}

