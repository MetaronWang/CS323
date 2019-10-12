%{
    #include "lex.yy.c"
    #include "stdlib.h"
    void yyerror(const char*); //必须要有
    char* stringAppend(char *s1, char *s2);
    char* result;
    #define APPEND(s) result = stringAppend(result,s)
%}
%error-verbose
%token INT FLOAT CHAR
%token ID TYPE STRUCT IF ELSE WHILE RETURN DOT SEMI COMMA ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT LP RP LB RB LC RC

%%
Quiz : Exp ASSIGN {  APPEND("a");  printf("%d\n", lines);}
    ;
Exp : Factor
    | Factor PLUS Exp {  APPEND("b");  printf("%d\n", lines);}
    | Factor MINUS Exp {  APPEND("c");  printf("%d\n", lines);}
    ;
Factor : INT
    | INT MUL Factor {  APPEND("d");  printf("%d\n", lines);}
    | INT DIV Factor {  APPEND("e");  printf("%d\n", lines);}
    ;
%%
 
 
void yyerror(const char *s){
    fprintf(stderr, "%s\n", s);
}


char* stringAppend(char *s1, char *s2)
{
    char *result = (char*)malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
	if (result == NULL) exit (1);
 
    strcpy(result, s1);
    strcat(result, s2);
    free(s1);
    return result;
}


int main(){
    result = (char*)malloc(0);
    yyparse();
    printf("%s\n", result);
    printf("%d\n", lines);
}

