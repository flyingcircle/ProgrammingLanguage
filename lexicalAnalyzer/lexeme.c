/*
File written by Jeremy Hamilton
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexeme.h"
#include "types.h"

lexeme* newLexeme( char* type ){
	lexeme* new = (lexeme*) malloc(sizeof(lexeme));
	new->type = type;
	new->string = "";
	new->integer = 0;
    new->left = NULL;
    new->right = NULL;
	return new;
}

lexeme* cons( char* type, lexeme* left, lexeme* right){
    lexeme* final = newLexeme(type);
    final->left = left;
    final->right = right;
    return final;
}

lexeme* car(lexeme* parent){
    return parent->left;
}

lexeme* cdr(lexeme* parent){
    return parent->right;
}

void setCar(lexeme* parent, void* value){
    if(strcmp(parent->type, NUMBER) == 0){
        int* newValue = (int*) value;
        parent->left->integer = *newValue;
    }
    else{
        parent->left->string = (char*) value;
    }
}

void setCdr(lexeme* parent, void* value){
    if(strcmp(parent->right->type, NUMBER) == 0){   
        int* newValue = (int*) value;
        parent->right->integer = *newValue;
    }
    else{
        parent->right->string = (char*) value;
    }
}

void visualizeHelper(lexeme* curr, FILE* writer){
    static int i = 0;
    int parentId = i;
    lexeme* left, *right;
    fprintf(writer,"\t%i [label=\"<f0> left| <f1> type = %s | <f2> int = %i | <f3> str = %s | <f4> right\"];\n", i, curr->type, curr->integer, curr->string);
    if(curr->left != NULL){
        left = curr->left;
        fprintf(writer,"\t%i:f0 -> %i;\n", parentId, i+1);
        i++;
        visualizeHelper(left, writer);
    }
    if(curr->right != NULL) {
        right = curr->right;
        fprintf(writer,"\t%i:f4 -> %i;\n", parentId, i+1);
        i++;
        visualizeHelper(right, writer);
    }
}

void prettyPrint(lexeme* s){
    FILE* f_write = fopen("graph.dot","w+");
    if(f_write == NULL){
        printf("I couldn't open results.dat for writing. \n");
        exit(0);
    }
    fprintf(f_write, "digraph BinaryTree {\n");
    visualizeHelper(s,f_write);
    fprintf(f_write, "}");
    fclose(f_write);
    system("dot -Tpng -O graph.dot"); 
}
