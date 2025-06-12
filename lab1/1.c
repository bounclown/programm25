#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100000
#define C 0

struct Student {
    char name[64];
    int math;
    int physics;
    int informatics;
    int total;
};

struct Student addStudent(const char *name, int math, int physics, int informatics) {
    struct Student newStudent;
    strncpy(newStudent.name, name, sizeof(newStudent.name) - 1);
    newStudent.name[sizeof(newStudent.name) - 1] = '\0';
    newStudent.math = math;
    newStudent.physics = physics;
    newStudent.informatics = informatics;
    newStudent.total = math + physics + informatics;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("Имя: %s\n", student.name);
    printf("Математика: %d\n", student.math);
    printf("Физика: %d\n", student.physics);
    printf("Информатика: %d\n", student.informatics);
    printf("Общий балл: %d\n", student.total);
    printf("-------------------------\n");
}

void RandomName(char *name, int length) {
    static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length - 1; i++) {
        name[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    name[length - 1] = '\0';
}

void SelectSort(struct Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].total > arr[k].total) {
                k = j;
            }
        }
        if (k != i) {
            struct Student temp = arr[i];
            arr[i] = arr[k];
            arr[k] = temp;
        }
    }
}

void CountSort(struct Student arr[], int n) {
    struct Student output[n];
    int count[301] = {0};

    for (int i = 0; i < n; i++) {
        count[arr[i].total]++;
    }

    for (int i = 299; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    for (int i = 0; i < n; i++) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void QuickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        struct Student pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j].total > pivot.total) {
                i++;
                struct Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        struct Student temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;

        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

int main() {
    printf("Информация о процессоре:\n");
    system("grep 'model name' /proc/cpuinfo | head -1");
    system("grep 'cpu MHz' /proc/cpuinfo | head -1");

    //struct Student students[N];
    //struct Student students1[N];
    struct Student students2[N];
    srand(time(NULL));

    /*for (int i = 0; i < N; i++) {
        char name[10];
        RandomName(name, sizeof(name));
        int math = rand() % 101;
        int physics = rand() % 101;
        int informatics = rand() % 101;
        students[i] = addStudent(name, math, physics, informatics);
    }

    for (int i = 0; i < N; i++) {
        char name[10];
        RandomName(name, sizeof(name));
        int math = rand() % 101;
        int physics = rand() % 101;
        int informatics = rand() % 101;
        students1[i] = addStudent(name, math, physics, informatics);
    }*/

    for (int i = 0; i < N; i++) {
        char name[10];
        RandomName(name, sizeof(name));
        int math = rand() % 101;
        int physics = rand() % 101;
        int informatics = rand() % 101;
        students2[i] = addStudent(name, math, physics, informatics);
    }


    clock_t start, end;
    double cpu_time_used;

    /*printf("Список студентов до сортировки:\n");
    for (int i = 0; i < C; i++) {
        printStudentInfo(students[i]);
    }

    start = clock();
    SelectSort(students, N);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Список студентов после сортировки:\n");
    for (int i = 0; i < C; i++) {
        printStudentInfo(students[i]);
    }
    printf("Время работы сортировки выбором: %f секунд для N = %d\n", cpu_time_used, N);
    printf("-------------------------\n");

    printf("Список студентов до сортировки:\n");
    for (int i = 0; i < C; i++) {
        printStudentInfo(students1[i]);
    }

    start = clock();
    CountSort(students1, N);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Список студентов после сортировки:\n");
    for (int i = 0; i < C; i++) {
        printStudentInfo(students1[i]);
    }
    printf("Время работы сортировки подсчетом: %f секунд для N = %d\n", cpu_time_used, N);
    printf("-------------------------\n");*/

    printf("Список студентов до сортировки:\n");
    for (int i = 0; i < C; i++) {
        printStudentInfo(students2[i]);
    }

    start = clock();
    QuickSort(students2, 0, N - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Список студентов после сортировки:\n");
    for (int i = 0; i < C; i++) {
        printStudentInfo(students2[i]);
    }
    printf("Время работы быстрой сортировки: %f секунд для N = %d\n", cpu_time_used, N);
    printf("-------------------------\n");

}