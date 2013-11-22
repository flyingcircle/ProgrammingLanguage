#ifndef NODE_H
#define NODE_H

typedef struct Node{
    void* data;
    struct Node* next;
}Node;

Node* newNode(void* value);
void freeNode(Node* node);
Node* getNext(Node* node);
void setNext(Node* node, Node* nextNode);

#endif 
