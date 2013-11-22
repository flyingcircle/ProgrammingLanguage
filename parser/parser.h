#ifndef PARSER_H_
#define PARSER_H_

#include "lexeme.h"

void newParser(void);
int check(char* type);
void advance(void);
void matchNoAdvance(char* type);
lexeme* match(char* type);
lexeme* operator(void);
int operatorPending(void);
lexeme* primary(void);
int primaryPending(void);
lexeme* varExpression(void);
int varExpressionPending(void);
lexeme* expression(void);
int expressionPending(void);
lexeme* list(void);
lexeme* optList(void);
lexeme* assignment(void);
lexeme* array(void);
int arrayPending(void);
lexeme* statement(void);
int statementPending(void);
lexeme* block(void);
lexeme* ifStatement(void);
int ifStatementPending(void);
lexeme* optElse(void);
lexeme* whileStatement(void);
int whileStatementPending(void);
lexeme* args(void);
lexeme* optArgs(void);
lexeme* functionDef(void);
int functionDefPending(void);
lexeme* program(void);
int programPending(void);

#endif
