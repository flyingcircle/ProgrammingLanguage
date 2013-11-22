/*
File by Jeremy Hamilton
*/
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "lexer.h"
#include "lexeme.h"
#include "scanner.h"

void scanner(char* filename){
	newLexer(filename);
	lexeme* token = lex();

	while(strcmp(token->type, ENDOFINPUT) != 0){
		if(strcmp(token->type, NUMBER) != 0)
			printf("%s %s\n", token->type, token->string);
		else
			printf("%s %i\n", token->type, token->integer);
		token = lex();
	}
	printf("%s\n", token->type);
}

int main( int argc, char* argv[] ){
	scanner(argv[1]);
	return 0;
}
