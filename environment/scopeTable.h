#ifndef SCOPE_H
#define SCOPE_H

#include "lexeme.h"

lexeme* extend(lexeme* vars, lexeme* vals, lexeme* scope);
void addVariable(char* name, void* value, lexeme* scope);
lexeme* getVaribale(lexeme* name, lexeme* scope);
void setVariable(char* name, void* value, lexeme* scope);

#endif
