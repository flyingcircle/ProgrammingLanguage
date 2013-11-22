#include <stdlib.h>
#include "Node.h"

Node* newNode(void* value){
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

void freeNode(Node* node){
    free(node);
}

Node* getNext(Node* node){
    return node->next;
}

void setNext(Node* node, Node* nextNode){
    node->next = nextNode;
}
