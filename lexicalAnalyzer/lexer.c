/*
File written by Jeremy Hamilton
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexeme.h"
#include "types.h"

FILE *Input;
char ch;

void skipWhiteSpace(){
	while(isspace(ch) || ch == '#'){
		if(ch == '#'){
			while((ch= (char) fgetc(Input)) != ';');
		}
		ch = (char) fgetc(Input);
	}
}

char* growString(char* oldString, int* len){
	*len = *len * 2;
	char* newString = (char*)malloc(sizeof(char) * *len);
	printf("Old: %i\n",atoi(oldString));
	strcpy(newString,oldString);
	free(oldString);
	return newString;
}

//not calling growString inside lexNumber because there would
//overflow error anyways. Perhaps later figure out a warning.
lexeme* lexNumber(){
	lexeme* new = newLexeme(NUMBER);
	char* num = (char*)malloc(sizeof(char) * 30);
	int i = 0;
	while(isdigit(ch = fgetc(Input))){
		num[i++] = (char) ch;
	}
	ungetc(ch, Input);
	new->integer = atoi(num);
	return new;
}

lexeme* lexVariable(){
	lexeme* new;
	char* var = (char*)malloc(sizeof(char) * 30);
	int len = 30;
	int i = 0;
	while(isalnum(ch = fgetc(Input))){
		if(i == len)
			var = growString(var,&len);
		var[i++] = (char) ch;
	}
	if(strcmp(var,"moenus") == 0)
		new = newLexeme(FUNCTION);
	else if(strcmp(var,"dum") == 0)
		new = newLexeme(WHILE);
	else if(strcmp(var,"si") == 0)
		new = newLexeme(IF);
	else if(strcmp(var,"aut") == 0)
		new = newLexeme(ELSE);
	else if(strcmp(var,"revenire") == 0)
		new = newLexeme(RETURN);
	else
		new = newLexeme(VARIABLE);
	new->string = var;
	ungetc(ch, Input);
	return new;
}

lexeme* lexString(){
	lexeme* new = newLexeme(STRING);
	char* str = (char*)malloc(sizeof(char) * 30);
	int len = 30;
	int i = 0;
	while((ch = fgetc(Input)) != '"'){
		if(i == len)
			str = growString(str,&len);
		str[len++] = (char) ch;
	}
	new->string = str;
	return new;
}

lexeme* lexUnknown(){
	lexeme* new = newLexeme(UNKNOWN);
	int* input = malloc(sizeof(int));
	*input = fgetc(Input);
	new->string = (char *) input;
	return new;
}

lexeme* lex(void)
{
	int cha = fgetc(Input);
	ch = (char) cha;

	skipWhiteSpace();
	if(ch == EOF || ferror(Input) != 0){
		fclose(Input);
		return newLexeme(ENDOFINPUT);
	}

	switch(ch)
	{
		case '[':
			return newLexeme(OBRACKET);
		case ']':
			return newLexeme(CBRACKET);
		case '.':
			return newLexeme(PERIOD);
		case ';':
			return newLexeme(SEMICOLON);
		case ':':
			return newLexeme(COLON);
		case ',':
			return newLexeme(COMMA);
		case '+':
			return newLexeme(PLUS);
		case '-':
			return newLexeme(SUBTRACT);
		case '*':
			return newLexeme(TIMES);
		case '/':
			return newLexeme(DIVIDE);
		case '%':
			return newLexeme(MODULUS);
		case '&':
			return newLexeme(AND);
		case '|':
			return newLexeme(OR);
		case '^':
			return newLexeme(XOR);
		case '=':
			ch = fgetc(Input);
			if(ch == '='){
				return newLexeme(EQUALS);
			}
			else{
				ungetc(ch, Input);
				return newLexeme(ASSIGN);
			}
		case '!':
			ch = fgetc(Input);
			if(ch == '='){
				return newLexeme(NOTEQUALS);
			}
			else{
				ungetc(ch, Input);
				return newLexeme(NOT);
			}
		case '<':
			ch = fgetc(Input);
			if(ch == '='){
				return newLexeme(LESSOREQUAL);
			}
			else{
				ungetc(ch, Input);
				return newLexeme(LESSTHAN);
			}
		case '>':
			ch = fgetc(Input);
			if(ch == '='){
				return newLexeme(GREATEROREQUAL);
			}
			else{
				ungetc(ch, Input);
				return newLexeme(GREATERTHAN);
			}
		default:
			//for multi char tokens
			if(isdigit(ch)){
				ungetc(ch, Input);
				return lexNumber();
			}
			else if(isalpha(ch)){
				ungetc(ch, Input);
				return lexVariable(); //and keywords
			}
			else if(ch == '"'){
				return lexString();
			}
	}
	return lexUnknown();
}

void newLexer(char* filename)
{
	Input = fopen(filename, "r");
	if (Input == NULL)
	{
		fprintf(stderr, "Can't open input file %s\n",filename);
	}
}
