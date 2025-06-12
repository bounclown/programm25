#define LIST_H

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

node_t *newNode(int data);
node_t* addBack(node_t* head, int data);
node_t* addStart(node_t* head, int data);
void printList(node_t* head);
char get_key();
void movingList(char ch, node_t* S, node_t* oddList, node_t* evenList);

