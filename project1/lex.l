%{
    #include"node.hpp"
    #define YYSTYPE Node
    #include"pro_1.tab.h"
    #include "iostream"
    using namespace std;
    char *p = NULL;
    int lines = 1;
    int yycolno = 1;
    #define YY_USER_ACTION \
      yylloc.first_line = yylineno; \
      yylloc.first_column = yycolno; \
      yylloc.last_line = yylineno; \
      yylloc.last_column = yycolno + yyleng; \
      yycolno += yyleng;
%}
%option yylineno
%%
('.')|('\\x[0-9a-fA-F]{2}') {yylval=createNode(yytext); cout<<yytext<<endl;return CHAR;}
(int)|(float)|(char)    {yylval = createNode(yytext); return TYPE;}
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
    yylval=createNode(yytext);
    return FLOAT;
}
([0-9]+)|(0x[0-9A-Fa-f]+) {yylval=createNode(yytext); return INT; }
0x[0-9A-Za-z]+            {yylval=createNode(yytext);cout<<yytext<<endl; return INT; }
[a-zA-Z_][a-zA-Z_0-9]*  {yylval=createNode(yytext); return ID;}
\n                      {lines++;}
" "                     {}
[ \f\n\r\t\v]           {}
.                       {yylval=createNode(yytext); return LEXERR;}

%%
int yywrap()
{
  return 1;
}