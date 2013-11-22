#include <stdlib.h>
#include "type.h"
#include "scopeTable.h"

lexeme* extend(lexeme* vars, lexeme* vals, lexeme* scope){
    return cons(ENV, cons(GLUE, vars, vals), scope);
}

void addVariable(char* name, void* value, lexeme* scope){
    lexeme* t = car(scope);
    lexeme* var = newLexeme(VARIABLE);
    lexeme* val = newLexeme(    
    t->left = cons(GLUE, newLexeme(VARIABLE,name), t->left);
    t->right = cons(GLUE, value, t->right);
    return;
}

lexeme* getVariable(char* name, lexeme* scope){
    lexeme* s = scope;
    while(s != NULL){
        lexeme* t = car(s);
        vars = car(t); vals = cdr(t);
        while(vars != NULL){
            if(strcmp(name,car(vars)->string) == 0)
                return car(vals);
            vars = cdr(vars);
            vals = cdr(vals);
        }
        s = cdr(s);
    }
    fprintf(stderr,"the variable, %s, does not exist in the current scope.\n",name);
    exit(EXIT_FAILURE);
}

void setVariable(char* name, void* value, lexeme* scope){
    lexeme* s = scope;
    while(s != NULL){
        lexeme* t = car(s);
        vars = car(t); vals = cdr(t);
        while(vars != NULL){
            if(strcmp(name, car(vars)->string) == 0){
                setCar(vals, value);
                return;
            }
            vars = cdr(vars);
            vals = cdr(vars);
        }
        s = cdr(s);
    }
    return addVariable(name, value, scope);
}
