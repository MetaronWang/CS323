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
A [/]
B [*]
C [^*/]
comment "/*"{A}*({C}{A}*|{B}|{C})*"*/"
%%
\/\/.*                        {}
"/*"{A}*({C}{A}*|{B}|{C})*{comment}(.|\n)*"*/"  {
  string e = "Error type B at Line "+to_string(yylineno)+":  nested multi-line comments";
  cout<<e<<endl;
  errList.push_back(e);
}
{comment} {}
('.')|('\\x[0-9a-fA-F]{2}') {yylval=createNode(yytext);return CHAR;}
(int)|(float)|(char)    {yylval = createNode(yytext); return TYPE;}
"struct"                {return STRUCT;}
"if"                    {return IF;}
"else"                  {return ELSE;}
"while"                 {return WHILE;}
"for"                   {return FOR;}
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
[a-zA-Z_][a-zA-Z_0-9]*  {yylval=createNode(yytext); return ID;}
0x[0-9A-Za-z]+          {yylval=createNode(yytext); return LEXERR; }
('\\x[0-9a-zA-Z]*')     {yylval=createNode(yytext); return LEXERR; }
[0-9][a-zA-Z_0-9]*      {yylval=createNode(yytext); return LEXERR; }
\n                      {lines++;}
[ \f\n\r\t\v]           {}
.                       {yylval=createNode(yytext); return LEXERR;}

%%
int yywrap()
{
  return 1;
}