/*
file written by Jeremy Hamilton.
*/
#ifndef LEXEME_H_
#define LEXEME_H_

typedef struct lexeme{
	char* type;
	char* string;
	int integer;

    struct lexeme* left;
    struct lexeme* right;
}lexeme;

lexeme* newLexeme(char* type);
lexeme* cons(char* type, lexeme* left, lexeme* right);
lexeme* car(lexeme* parent);
lexeme* cdr(lexeme* parent);
void setCar(lexeme* parent, void* value);
void setCdr(lexeme* parent, void* value);
void prettyPrint(lexeme* s);

#endif
