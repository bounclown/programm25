#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


typedef struct {
    const char* name;
    const char* lines[5];
} ThreadData;

void cleanup_handler(void* arg) {
    const char* name = (const char*)arg;
    printf("[%s] Завершение потока по отмене или выходу\n", name);
}

void* thread_func(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    pthread_cleanup_push(cleanup_handler, (void*)data->name);

    for (int i = 0; i < 5; ++i) {
        printf("[%s] %s\n", data->name, data->lines[i]);
        sleep(1);
        pthread_testcancel();
    }

    pthread_cleanup_pop(1);

    return NULL;
}

int main() {
    pthread_t threads[4];
    ThreadData thread_data[4] = {
        {"Поток 1", {"Привет", "это", "первый", "поток", "ура"}},
        {"Поток 2", {"Второй", "поток", "тоже", "работает", "хайп"}},
        {"Поток 3", {"Здравствуй", "третий", "мир", "из", "потока"}},
        {"Поток 4", {"Четвёртый", "поток", "всегда", "на", "готове"}}
    };

    for (int i = 0; i < 4; ++i) {
        pthread_create(&threads[i], NULL, thread_func, &thread_data[i]);
    }

    sleep(2);

    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Основной поток: все потоки были остановлены.\n");

    return 0;
}