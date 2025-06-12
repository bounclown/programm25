#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

typedef struct node node_t;

node_t *newNode(int data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

node_t* addBack(node_t* head, int data) {
    node_t* new_node = newNode(data);

    if (!head) {
        return new_node;
    }

    node_t* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = new_node;
    new_node->prev = cur;

    return head;
}

node_t* addStart(node_t* head, int data) {
    node_t* new_node = newNode(data);

    new_node->next = head;
    new_node->prev = NULL;

    if (head) {
        head->prev = new_node;
    }
    
    return new_node;
}

void printList(node_t* head) {
    node_t* cur = head;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
}

char get_key() {
    struct termios oldt, newt;
    char ch;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

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

    printf("\nУправление списком: WASD (или 2,4,6,8)\n");
    ch = getchar();
    while (1) {
        ch = get_key();
        
        switch (ch)
        {
        case 's':
        case 'S':
        case '2':
            printf("%d\n", S->data);
            break;
        case 'w':
        case 'W':
        case '8':
            printf("Закрытие...\n");
            return 0;
        case 'a':
        case 'A':
        case '4':
            printf("Вы начали движение только влево, для прекращения нажмите(W)\n");
            int Flag = 0;
            while(1) {
                if (Flag != 0) break;

                ch = get_key();

                switch (ch)
                {
                case 's':
                case 'S':
                case '2':
                    printf("%d\n", S->data);
                    break;
                case 'w':
                case 'W':
                    printf("Прекращение движения влево\n");
                    Flag = 1;
                    S = oddList;
                    break;
                case 'a':
                case 'A':
                case '4':
                    if (S->next) {
                        S = S->next;
                    } else {
                        printf("Вы достигли конца списка\n");
                        printf("Хотите вернуться в начало?Y/n\n");
                        while (S != oddList)
                        {
                            ch = get_key();

                            switch (ch)
                            {
                            case 'y':
                            case 'Y':
                                S = oddList;
                                Flag = 1;
                                printf("Вы вернулись в начало\n");
                                break;
                            case 'n':
                            case 'N':
                                printf("ЗАкрытие...\n");
                                return 0;
                            default:
                                printf("Вы нажали не ту клавишу, попробуйте снова\n");
                                break;
                            }
                        }
                        
                    }
                    break;
                
                default:
                    printf("Вы нажали не подходящую клавишу\n");
                    break;
                }
            
            }
            break;
        case 'd':
        case 'D':
        case '6':
            S = evenList;
            printf("Вы начали движение только вправо, для прекращения нажмите(W)\n");
            int F = 0;
            while(1) {
                if (F != 0) break;

                ch = get_key();

                switch (ch)
                {
                case 's':
                case 'S':
                case '2':
                    printf("%d\n", S->data);
                    break;
                case 'w':
                case 'W':
                    printf("Прекращение движения вправо\n");
                    F = 1;
                    S = evenList;
                    break;
                case 'd':
                case 'D':
                case '6':
                    if (S->next) {
                        S = S->next;
                    } else {
                        printf("Вы достигли конца списка\n");
                        printf("Хотите вернуться в начало?Y/n\n");
                        while (S != evenList)
                        {
                            ch = get_key();

                            switch (ch)
                            {
                            case 'y':
                            case 'Y':
                                S = evenList;
                                F = 1;
                                printf("Вы вернулись в начало\n");
                                break;
                            case 'n':
                            case 'N':
                                printf("ЗАкрытие...\n");
                                return 0;
                            default:
                                printf("Вы нажали не ту клавишу, попробуйте снова\n");
                                break;
                            }
                        }
                        
                    }
                    break;
                
                default:
                    printf("Вы нажали не подходящую клавишу\n");
                    break;
                }
            
            }
            break;
        default:
            printf("Вы нажали не подходящую клавишу\n");
            break;
        }
    }

}