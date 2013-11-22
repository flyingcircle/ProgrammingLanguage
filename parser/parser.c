#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexeme.h"
#include "lexer.h"
#include "types.h"

lexeme* currLexeme;

void newParser(void){
	advance();
}

int check(char* type){
	return (strcmp(currLexeme->type, type) == 0);
}

void advance(void){
	currLexeme = lex();
}

//error message on incorrect match.
void matchNoAdvance(char* type){
	if(!check(type)){
		printf("illegal\n");
		fprintf(stderr, "expected %s, but encountered %s %s\n",type,currLexeme->type, currLexeme->string);
		exit(EXIT_FAILURE);
	}
}		

lexeme* match(char* type){
	matchNoAdvance(type);
    lexeme* temp = currLexeme;
	if(strcmp(currLexeme->type,ENDOFINPUT) != 0)
		advance();
    return temp;
}

lexeme* operator(void){
	if(check(PLUS))
		return match(PLUS);
	else if(check(TIMES))
		return match(TIMES);
	else if(check(DIVIDE))
		return match(DIVIDE);
	else if(check(SUBTRACT))
		return match(SUBTRACT);
	else if(check(MODULUS))
		return match(MODULUS);
	else if(check(AND))
		return match(AND);
	else if(check(OR))
		return match(OR);
	else if(check(NOT))
		return match(NOT);
	else if(check(XOR))
		return match(XOR);
	else if(check(EQUALS))
		return match(EQUALS);
	else if(check(NOTEQUALS))
		return match(NOTEQUALS);
	else if(check(GREATERTHAN))
		return match(GREATERTHAN);
	else if(check(LESSTHAN))
		return match(LESSTHAN);
	else if(check(GREATEROREQUAL))
		return match(GREATEROREQUAL);
	else 
		return match(LESSOREQUAL);
}

int operatorPending(void){
	return (check(PLUS) ||
		check(TIMES) ||
		check(DIVIDE) ||
		check(SUBTRACT) ||
		check(MODULUS) ||
		check(AND) ||
		check(OR) ||
		check(XOR) ||
		check(EQUALS) ||
		check(NOTEQUALS) ||
		check(GREATERTHAN) ||
		check(LESSTHAN) ||
		check(GREATEROREQUAL) ||
		check(LESSOREQUAL));
}

lexeme* primary(void){
    lexeme* e;
	if(check(NUMBER))
		return match(NUMBER);
	else if(check(STRING))
		return match(STRING);
	else if(check(OBRACKET)){
		free(match(OBRACKET));
		e = expression();
		free(match(CBRACKET));
        return e;
	}
	else if(arrayPending())
		return array();
	else
		return varExpression();
}

int primaryPending(void){
	return (check(NUMBER) ||
		check(STRING) ||
		varExpressionPending() ||
		check(OBRACKET));
}

lexeme* varExpression(void){
    lexeme* v, *l;
	v = match(VARIABLE);
	if(check(OBRACKET)){
		free(match(OBRACKET));
		l = optList();
		free(match(CBRACKET));
        return cons(FUNCTION_CALL, v, l);
	}
    return v;
}

int varExpressionPending(void){
	return(check(VARIABLE));
}

lexeme* expression(void){
    lexeme* p, *o, *e;
	p = primary();
	if(operatorPending()){
		o = operator();
		e = expression();
        return cons(EXPRESSION, p, cons(GLUE, o, e));
	}
    return cons(EXPRESSION, p, NULL);
}

int expressionPending(void){
	return (primaryPending());
}

lexeme* list(void){
    lexeme* e;
	e = expression();
	if(check(COMMA)){
		free(match(COMMA));
		return cons(LIST, e, list());
	}
    return cons(LIST, e, NULL);
}

lexeme* optList(void){
	if(expressionPending()){
		return list();
	}
    return NULL;
}

lexeme* assignment(void){
    lexeme* v, *e;
	v = match(VARIABLE);
	free(match(ASSIGN));
    e = expression();
    return cons(ASSIGN, v, e);
}

lexeme* array(void){
	free(match(COLON));
	lexeme* l = optList();
	free(match(SEMICOLON));
    return cons(ARRAY, NULL, l);
}

int arrayPending(void){
	return (check(COLON));
}

lexeme* statement(void){
    lexeme* s;
	if(ifStatementPending())
		return ifStatement();
	else if(whileStatementPending())
		return whileStatement();
	else if(functionDefPending())
		return functionDef();
	else if(check(RETURN)){
		free(match(RETURN));
        s = expression();
		free(match(PERIOD));
		return cons(RETURN, s, NULL);
	}
	//between assignment and functionCall in grammar.
	else{
		s = match(VARIABLE);
		if(check(ASSIGN)){
			free(match(ASSIGN));
			s = cons(ASSIGN, s, expression());
		}
		else{
			free(match(OBRACKET));
			s = cons(FUNCTION_CALL, s, optList());
			free(match(CBRACKET));
		}
		free(match(PERIOD));
        return s;
	}
}

int statementPending(void){
	return (ifStatementPending() ||
		whileStatementPending() ||
		functionDefPending() ||
		check(VARIABLE));
}

lexeme* block(void){
    lexeme* s;
	if(check(SEMICOLON))
		free(match(SEMICOLON));
	else{
		s = statement();
		return cons(BODY, s, block());
	}
    return NULL;
}

lexeme* ifStatement(void){
    lexeme* cond, *b, *e;
	free(match(IF));
	free(match(OBRACKET));
	cond = expression();
	free(match(CBRACKET));
	b = block();
	e = optElse();
    return cons(IF, cond, cons(GLUE, b, e));
}

int ifStatementPending(void){
	return (check(IF));
}

lexeme* optElse(void){
	if(check(ELSE)){
		free(match(ELSE));
		return cons(ELSE, block(), NULL);
	}
    return NULL;
}

lexeme* whileStatement(void){
    lexeme* cond;
	free(match(WHILE));
	free(match(OBRACKET));
	cond = expression();
	free(match(CBRACKET));
	return cons(WHILE, cond, block());
}

int whileStatementPending(void){
	return (check(WHILE));
}

lexeme* args(void){
    lexeme* param;
	param = match(VARIABLE);
	if(check(COMMA)){
		free(match(COMMA));
		return cons(PARAMETERS, param, args());
	}
    return cons(PARAMETERS, param, NULL);
}

lexeme* optArgs(void){
	if(check(VARIABLE)){
		return args();
	}
    return NULL;
}	

lexeme* functionDef(void){
    lexeme* name, *parameters, *body;
	free(match(FUNCTION));
	name = match(VARIABLE);
	free(match(OBRACKET));
	parameters = optArgs();
	free(match(CBRACKET));
	body = block();
    return cons(FUNCTION_DEF, name, cons(GLUE, parameters, body));
}

int functionDefPending(void){
	return (check(FUNCTION));
}

lexeme* program(void){
    lexeme* s;
	s = statement();
	if(programPending())
		return cons(GLOBAL, s, program());
	else
		return cons(GLOBAL, s, match(ENDOFINPUT));
}

int programPending(void){
	return (statementPending());
}
