#include "list.h"

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