#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int turn = 0;

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
        pthread_mutex_lock(&mutex);
        while (turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("[%s] %s\n", data->name, data->lines[i]);
        sleep(1);
        pthread_testcancel();
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_cleanup_pop(1);
    return NULL;
}

int main() {
    pthread_t thread;
    ThreadData thread_data = {
        "Дочерний поток",
        {"один", "два", "три", "четыре", "пять"}
    };

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&thread, NULL, thread_func, &thread_data);

    const char* parent_lines[5] = {"раз", "два", "три", "четыре", "пять"};

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex);
        while (turn != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("[Родительский поток] %s\n", parent_lines[i]);
        sleep(1);
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("Основной поток: завершение программы.\n");

    return 0;
}
