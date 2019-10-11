%{
    void yyerror(char *);
    #include"syntax.tab.h"
    char *p = NULL;
%}
%%
    (int)|(float)|(char)    {return TYPE;}
    "struct"                {return STRUCT;}
    "if"                    {return IF;}
    "else"                  {return ELSE;}
    "while"                 {return WHILE;}
    "return"                {return RETURN;}
    "."                     {return DOT;}
    ";"                     {return SEMI;}
    ","                     {return COMMA;}
    "="                     {return ASSIGN;}
    "<"                     {return LT;}
    "<="                    {return LE;}
    ">"                     {return GT;}
    ">="                    {return GE;}
    "!="                    {return NE;}
    "=="                    {return EQ;}
    "+"                     {return PLUS;}
    "-"                     {return MINUS;}
    "*"                     {return MUL;}
    "/"                     {return DIV;}
    "&&"                    {return AND;}
    "||"                    {return OR;}
    "!"                     {return NOT;}
    "("                     {return LP;}
    ")"                     {return RP;}
    "["                     {return LB;}
    "]"                     {return RB;}
    "{"                     {return LC;}
    "}"                     {return RC;}
    [0-9]+\.[0-9]+          {
        printf("%s", yytext);
        yylval = strtof(yytext, &p);
        printf("%f has been readn", yylval);
        return FLOAT;
    }
    [0-9]+                  { yylval = atoi(yytext); return INT; }
    [\S]                    {yylval = yytext; return CHAR;}

%%