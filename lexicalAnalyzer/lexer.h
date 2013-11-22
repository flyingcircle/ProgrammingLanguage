/*
File written by Jeremy Hamilton.
*/
#ifndef LEXER_H_
#define LEXER_H_
#include "lexeme.h"

void skipWhiteSpace();
void growString(char** oldString, int* len);
lexeme* lexNumber();
lexeme* lexVariable();
lexeme* lexString();
void skipComment();
lexeme* lexUnknown();
lexeme* lex(void);
void newLexer(char* filename);

#endif
