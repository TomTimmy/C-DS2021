#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // node 안에 문자열로 넣을꺼임

typedef struct sNode {

    char *data;
    struct sNode *next;
    
}Node;

typedef struct listStack {

    Node *peek;
    int size;

}listStack;

void createStack(listStack **Stack) {
    (*Stack) = (listStack*)malloc(sizeof(listStack));
    (*Stack)->peek = NULL;
    (*Stack)->size = 0;
}

Node* createNode(char *newChar) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    // newNode-> data = malloc(str)
}