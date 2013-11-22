#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "recognizer.h"
#include "lexer.h" 
#include "lexeme.h"

void recognizer(char* filename, int graphFlag){
	newLexer(filename);
	newParser();
	lexeme* parseTree = program();
    if(graphFlag)
        prettyPrint(parseTree);
	printf("legal\n");
}

int main( int argc, char* argv[]){
    if(argc > 2 && strcmp(argv[2], "--graph") == 0)
	    recognizer(argv[1], 1);
    else
        recognizer(argv[1], 0);
	return 0;
}
