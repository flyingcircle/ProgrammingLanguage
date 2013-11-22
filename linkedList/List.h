#ifndef LIST_H
#define LIST_H
#include "Node.h"

typedef struct List{
    Node* head;
    int size;
} List;

List* newList(void);
void freeList(List* list);
void deleteHead(List* list);
List* prependList(List* list, void* data);
int size(List* list);

#endif
