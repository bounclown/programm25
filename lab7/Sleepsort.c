#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_ELEMENTS 50


void* sleepsort_thread(void* arg) {
    int value = *(int*)arg;
    usleep(value * 1000);
    printf("%d ", value);
    free(arg);
    return NULL;
}

int main() {
    int array[MAX_ELEMENTS] = {5, 3, 8, 1, 4, 2};
    int n = 6;

    pthread_t threads[MAX_ELEMENTS];

    for (int i = 0; i < n; ++i) {
        int* val = malloc(sizeof(int));
        *val = array[i];

        if (pthread_create(&threads[i], NULL, sleepsort_thread, val) != 0) {
            perror("Ошибка создания потока");
            return 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("\nСортировка завершена (SLEEPSORT).\n");
    return 0;
}
