#include "list.h"


void movingList(char ch, node_t* S, node_t* oddList, node_t* evenList) {
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