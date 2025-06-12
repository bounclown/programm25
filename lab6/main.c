#include "list.h"

int main() {
    srand(time(NULL));
    char ch;
    int data, i = 1, n;
    node_t* oddList = NULL;
    node_t* evenList = NULL;
    node_t* oddPtr = NULL;
    node_t* evenPtr = NULL;
    node_t* S = NULL;

    printf("Выберите способ заполнения списка\n");
    printf("1 - вручную\n");
    printf("2 - случайное\n");
    
    printf("Способ заполнения: ");
    if (scanf("%d", &n) != 1) {
        printf("Ошибка ввода\n");
        return 0;
    }

    if (n == 1) {
        printf("Вводите элементы списка, чтобы прекратить введите 0\n");

        while (1) {
            printf("%d элемент списка: ", i);
            if (scanf("%d", &data) != 1) {
                printf("Ошибка ввода\n");
                break;
            }
            if (data == 0) break;

            if (i % 2 == 1) {
                oddList = addStart(oddList, data);
            } else {
                evenList = addStart(evenList, data);
            }
            i++;
        }
    } else if(n == 2) {
        printf("Введите количество чисел в списке: ");
        if (scanf("%d", &n) != 1) {
            printf("Ошибка ввода\n");
            return 0;
        }

        while (n != 0) {
            data = rand() % 100;

            if (i % 2 == 1) {
                oddList = addStart(oddList, data);
            } else {
                evenList = addStart(evenList, data);
            }
            i++;
            n--;
        }
    } else {
        printf("Не подходящий способ заполнения, завершение работы...\n");
        return 0;
    }

    S = oddList;

    if (oddList && evenList) {
        oddList->prev = evenList;
    }

    if (S) {

    } else {
        printf("Список пуст, завершение работы...\n");
        return 0;
    }

    printf("\nНечётный список:\n");
    printList(oddList);

    printf("\nЧётный список:\n");
    printList(evenList);

    node_t* tempOdd = oddList;
    node_t* tempEven = evenList;

    movingList(ch, S, oddList, evenList);
}