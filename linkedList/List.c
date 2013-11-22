#include <stdlib.h>
#include "List.h"
#include "Node.h"

List* newList(void){
    List* list = (List*) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    return list;
}

void freeList(List* list){
    while(list->head != NULL){
        deleteHead(list);
    }
    free(list);
}

void deleteHead(List* list){
    if(list->head == NULL) return;
    Node* nextHead = getNext(list->head);
    freeNode(list->head);
    list->head = nextHead;
    list->size -= 1;
}

void prepend(List* list, void* value){
    Node* node = newNode(value);
    setNext(node->next, list->head);
    list->head = node;
    list->size += 1;
}

int size(List* list){
    return list->size;
}
