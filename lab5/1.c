#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "PriceList.dat"
#define MAX_LEN 50
#define MAX_PRODUCTS 100

struct Product {
    char name[MAX_LEN];
    char store[MAX_LEN];
    float price; 
};

void createFile() {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (!fp) {
        perror("Ошибка при создании файла");
        return;
    }

    int n;
    printf("Введите количество товаров: ");
    scanf("%d", &n);
    getchar();

    struct Product product;
    for (int i = 0; i < n; i++) {
        printf("\nТовар %d:\n", i + 1);

        printf("Название товара: ");
        fgets(product.name, MAX_LEN, stdin);
        product.name[strcspn(product.name, "\n")] = '\0';

        printf("Название магазина: ");
        fgets(product.store, MAX_LEN, stdin);
        product.store[strcspn(product.store, "\n")] = '\0';

        printf("Стоимость: ");
        scanf("%f", &product.price);
        getchar();

        fwrite(&product, sizeof(struct Product), 1, fp);
    }

    fclose(fp);
    printf("\nФайл %s успешно создан.\n", FILE_NAME);
}

void searchFile() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        perror("Ошибка при открытии файла");
        return;
    }

    int choice;
    char query[MAX_LEN];
    float price_query;
    int found = 0;

    printf("\nВыберите поле для поиска:\n");
    printf("1. Название товара\n");
    printf("2. Название магазина\n");
    printf("3. Стоимость\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);
    getchar();

    struct Product product;

    switch (choice) {
        case 1:
            printf("Введите название товара: ");
            fgets(query, MAX_LEN, stdin);
            query[strcspn(query, "\n")] = '\0';
            while (fread(&product, sizeof(struct Product), 1, fp)) {
                if (strcmp(product.name, query) == 0) {
                    printf("%s | %s | %.2f\n", product.name, product.store, product.price);
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Введите название магазина: ");
            fgets(query, MAX_LEN, stdin);
            query[strcspn(query, "\n")] = '\0';
            while (fread(&product, sizeof(struct Product), 1, fp)) {
                if (strcmp(product.store, query) == 0) {
                    printf("%s | %s | %.2f\n", product.name, product.store, product.price);
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Введите стоимость: ");
            scanf("%f", &price_query);
            while (fread(&product, sizeof(struct Product), 1, fp)) {
                if (product.price == price_query) {
                    printf("%s | %s | %.2f\n", product.name, product.store, product.price);
                    found = 1;
                }
            }
            break;
        default:
            printf("Некорректный выбор.\n");
            fclose(fp);
            return;
    }

    if (!found) {
        printf("Совпадений не найдено.\n");
    }

    fclose(fp);
}

int main() {
    int action;
    printf("Выберите действие:\n1. Создать файл\n2. Поиск в файле\nВаш выбор: ");
    scanf("%d", &action);
    getchar();

    if (action == 1) {
        createFile();
    } else if (action == 2) {
        searchFile();
    } else {
        printf("Некорректный выбор.\n");
    }

}