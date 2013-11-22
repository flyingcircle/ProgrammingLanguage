#include <stdlib.h>
#include "scopeTable.h"
#include "lexeme.h"
#include "parser.h"
#include "types.h"

void testEnvironment(lexeme* env){
    printf("Creating a new environment\n");
    printf("The environment is: ENV1\n");
    lexeme* ENV1 = extend(NULL,NULL, env);
    printf("Adding the variable 'x' with a value 3\n"); 
    int* value = 3;
    addVariable("x", (void*) value, ENV1);
    printf("Extending the environment with y:4 and z:\"hello\"\n");
    lexeme* vars = cons(VARIABLE,"y", cons(VARIABLE, "z"));
    lexeme* vals = cons(INTEGER, 3, 
    lexeme* ENV2 = extend(
} 

int main(int argc, char* argv[]){
    //char* filename; //add filename
    lexeme* env = extend(NULL, NULL, NULL);
    testEnvironment(env);
    //possibly add builtins e.g. addBuiltins(env);
    //lexeme* p = parser(filename);
    //eval(p, env);
}
