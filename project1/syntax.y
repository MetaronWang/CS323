%{
    #include"lex.yy.c"
    void yyerror(const char*);
    int result;
%}
%token INT FLOAT
%token ID TYPE STRUCT IF ELSE WHILE RETURN DOT SEMI COMMA ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT LP RP LB RB LC RC
%%
%%
