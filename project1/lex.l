%{
    #define YYSTYPE char *
    #include"syntax.tab.h"
    #include "iostream"
    extern void yyerror(const char *);
    using namespace std;
    char *p = NULL;
    int lines = 0;
%}
%%
(int)|(float)|(char)    {yylval=yytext; return TYPE;}
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
    yylval = yytext;
    return FLOAT;
}
[0-9]+                  {yylval = yytext; return INT; }
[a-zA-Z_0-9]+           {yylval = yytext; return ID;}
\'\S\'                      {yylval = yytext; return CHAR;}
\n                      {lines++;}
%%
int yywrap()
{
  return 1;
}