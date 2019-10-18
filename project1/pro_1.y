%{
#include "lex.yy.c"
#include "stdlib.h"
#include "stdio.h"
#include "node.hpp"
#include "queue"
#include "stack"
#include "iostream"
#include "string"
#include "vector"
#define YYSTYPE Node
using namespace std;
void yyerror(const char*); //必须要有
extern int yylex(void);
string addLine(string,int);

Node program;
%}

%token INT FLOAT CHAR ID TYPE
%token STRUCT IF ELSE WHILE RETURN DOT SEMI COMMA ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT LP RP LB RB LC RC LEXERR

%type  Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

%right ASSIGN
%left OR
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left MUL DIV
%right NOT
%left LP RP LB RB DOT


%%
Program 
    : ExtDefList {
        program.show = addLine("Program", @$.first_line);
        program.subNode.push_back($1);
    }
	;
ExtDefList 
    : ExtDef ExtDefList {
        Node temp; 
        temp.subNode.push_back($1);
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        temp.show = addLine("ExtDefList", @$.first_line);
        $$ = temp;
    }
    | 
    {
        Node temp; 
        temp.show = addLine("ExtDefList", @$.first_line);
        $$ = temp;
    }
	;
ExtDef 
    : Specifier ExtDecList SEMI {
        Node temp;
        Node semi;
        semi.show = "SEMI";
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back(semi);
        temp.show = addLine("ExtDef", @$.first_line);
        $$ = temp;
    }
    | Specifier SEMI {
        Node temp;
        Node semi;
        semi.show = "SEMI";
        temp.subNode.push_back($1);
        temp.subNode.push_back(semi);
        temp.show = addLine("ExtDef", @$.first_line);
        $$ = temp;
    }
    | Specifier FunDec CompSt {
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back($3);
        temp.show = addLine("ExtDef", @$.first_line);
        $$ = temp;
    }
	;
ExtDecList 
    : VarDec {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = addLine("ExtDecList", @$.first_line);
        $$ = temp;
    }
    | VarDec COMMA ExtDecList {
        Node temp;
        Node comma;
        temp.subNode.push_back($1);
        comma.show = "COMMA";
        temp.subNode.push_back($3);
        temp.show = addLine("ExtDecList", @$.first_line);
        $$ = temp;
    }
	;
Specifier 
    : TYPE {
        Node temp;
        Node type;
        type.show = "TYPE: "+$1.show;
        temp.subNode.push_back(type);
        temp.show = addLine("Specifier", @$.first_line);
        $$ = temp;
    }
    | StructSpecifier {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = addLine("Specifier", @$.first_line);
        $$ = temp;
    }
	;
StructSpecifier 
    : STRUCT ID LC DefList RC {
        Node temp, struc, id, lc, rc;
        struc.show = "STRUCT";
        id.show = "ID: "+$2.show;
        lc.show = "LC";
        rc.show = "RC";
        temp.subNode.push_back(struc);
        temp.subNode.push_back(id);
        temp.subNode.push_back(lc);
        temp.subNode.push_back($4);
        temp.subNode.push_back(rc);
        temp.show = addLine("StructSpecifier", @$.first_line);
        $$ = temp;
    }
    | STRUCT ID {
        Node temp, struc, id;
        struc.show = "STRUCT";
        id.show = "ID: "+$2.show;
        temp.subNode.push_back(struc);
        temp.subNode.push_back(id);
        temp.show = addLine("StructSpecifier", @$.first_line);
        $$ = temp;
    }
	;
VarDec 
    : ID {
        Node temp, id;
        id.show = "ID: "+$1.show;
        temp.subNode.push_back(id);
        temp.show = addLine("VarDec", @$.first_line);
        $$ = temp;
    }
    | VarDec LB INT RB {
        Node temp, lb, i, rb;
        lb.show = "LB";
        rb.show = "RB";
        i.show = "INT: "+$3.show;
        temp.subNode.push_back($1);
        temp.subNode.push_back(lb);
        temp.subNode.push_back(i);
        temp.subNode.push_back(rb);
        temp.show = addLine("VarDec", @$.first_line);
        $$ = temp;
    }
	;
FunDec 
    : ID LP VarList RP {
        Node temp, id, lp, rp;
        id.show = "ID: "+$1.show;
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(id);
        temp.subNode.push_back(lp);
        temp.subNode.push_back($3);
        temp.subNode.push_back(rp);
        temp.show = addLine("FunDec", @$.first_line);
        $$ = temp;
    }
    | ID LP RP {
        Node temp, id, lp, rp;
        id.show = "ID: "+$1.show;
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(id);
        temp.subNode.push_back(lp);
        temp.subNode.push_back(rp);
        temp.show = addLine("FunDec", @$.first_line);
        $$ = temp;
    }
	;
VarList 
    : ParamDec COMMA VarList {
        Node temp, comma;
        comma.show ="COMMA";
        temp.subNode.push_back($1);
        temp.subNode.push_back(comma);
        temp.subNode.push_back($3);
        temp.show = addLine("VarList", @$.first_line);
        $$ = temp;
    }
    | ParamDec {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = addLine("VarList", @$.first_line);
        $$ = temp;
    }
	;
ParamDec 
    : Specifier VarDec{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.show = addLine("ParamDec", @$.first_line);
        $$ = temp;
    }
	;
CompSt 
    : LC DefList StmtList error{
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \'}\'";
        errList.push_back(e);
    }
    |
    LC DefList StmtList RC {
        Node temp, lc, rc;
        lc.show = "LC";
        rc.show = "RC";
        temp.subNode.push_back(lc);
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        if (! $3.subNode.empty())
            temp.subNode.push_back($3);
        temp.subNode.push_back(rc);
        temp.show = addLine("CompSt", @$.first_line);
        $$ = temp;
    }
	;
StmtList 
    : Stmt StmtList {
        Node temp;
        temp.subNode.push_back($1);
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        temp.show = addLine("StmtList", @$.first_line);
        $$ = temp;
    }
    | 
    {
        Node temp;
        temp.show = addLine("StmtList", @$.first_line);
        $$ = temp;
    }
	;
Stmt 
    : Exp error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \';\'";
        cout<<e<<endl;
        errList.push_back(e);
    }
    |
    Exp SEMI {
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("SEMI"));
        temp.show = addLine("Stmt", @$.first_line);
        $$ = temp;
    }
    | CompSt {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = addLine("Stmt", @$.first_line);
        $$ = temp;
    }
    | RETURN Exp SEMI {
        Node temp, ret, semi;
        ret.show = "RETURN";
        semi.show = "SEMI";
        temp.subNode.push_back(ret);
        temp.subNode.push_back($2);
        temp.subNode.push_back(semi);
        temp.show = addLine("Stmt", @$.first_line);
        cout<<$2.show<<endl;
        $$ = temp;
    }
    | IF LP Exp RP Stmt {
        Node temp, i, lp, rp;
        i.show = "IF";
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(i);
        temp.subNode.push_back(lp);
        temp.subNode.push_back($3);
        temp.subNode.push_back(rp);
        temp.subNode.push_back($5);
        temp.show = addLine("Stmt", @$.first_line);
        $$ = temp;
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        Node temp, i, lp, rp, e;
        i.show = "IF";
        lp.show = "LP";
        rp.show = "RP";
        e.show = "ELSE";
        temp.subNode.push_back(i);
        temp.subNode.push_back(lp);
        temp.subNode.push_back($3);
        temp.subNode.push_back(rp);
        temp.subNode.push_back($5);
        temp.subNode.push_back(e);
        temp.subNode.push_back($7);
        temp.show = addLine("Stmt", @$.first_line);
        $$ = temp;
    }
    | WHILE LP Exp RP Stmt {
        Node temp, w, lp, rp;
        w.show = "WHILE";
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(w);
        temp.subNode.push_back(lp);
        temp.subNode.push_back($3);
        temp.subNode.push_back(rp);
        temp.subNode.push_back($5);
        temp.show = addLine("Stmt", @$.first_line);
        $$ = temp;
    }
	;
DefList 
    : Def DefList {
        Node temp;
        temp.subNode.push_back($1);
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        temp.show = addLine("DefList", @$.first_line);
        $$ = temp;
    }
    | 
    {
        Node temp;
        temp.show = addLine("DefList", @$.first_line);
        $$ = temp;
    }
	;
Def 
    : Specifier DecList SEMI {
        Node temp, semi;
        semi.show = "SEMI";
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back(semi);
        temp.show = addLine("Def", @$.first_line);
        $$ = temp;
    }
	;
DecList 
    : Dec {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = addLine("DecList", @$.first_line);
        $$ = temp;
    }
    | Dec COMMA DecList {
        Node temp, comma;
        comma.show= "COMMA";
        temp.subNode.push_back($1);
        temp.subNode.push_back(comma);
        temp.subNode.push_back($3);
        $$ = temp;
    }
	;
Dec 
    : VarDec {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = addLine("Dec", @$.first_line);
        $$ = temp;
    }
    | VarDec ASSIGN Exp {
        Node temp, assign;
        assign.show = "ASSIGN";
        temp.subNode.push_back($1);
        temp.subNode.push_back(assign);
        temp.subNode.push_back($3);
        temp.show = addLine("Dec", @$.first_line);
        $$ = temp;
    }
	;
Exp 
    :
    ID LP Args error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \')\'";
        errList.push_back(e);
    } 
    |
    Exp ASSIGN Exp {
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("ASSIGN"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp AND Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("AND"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp OR Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("OR"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp LT Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("LT"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp LE Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("LE"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp GT Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("GT"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp GE Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("GE"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp NE Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("NE"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp EQ Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("EQ"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp PLUS Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("PLUS"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp MINUS Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("MINUS"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp MUL Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("MUL"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp DIV Exp{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("DIV"));
        temp.subNode.push_back($3);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | LP Exp RP{
        Node temp;
        temp.subNode.push_back(createNode("LP"));
        temp.subNode.push_back($2);
        temp.subNode.push_back(createNode("RP"));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | MINUS Exp{
        Node temp;
        temp.subNode.push_back(createNode("MINUS"));
        temp.subNode.push_back($2);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | NOT Exp{
        Node temp;
        temp.subNode.push_back(createNode("NOT"));
        temp.subNode.push_back($2);
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | ID LP Args RP{
        Node temp;
        temp.subNode.push_back(createNode("ID: "+$1.show));
        temp.subNode.push_back(createNode("LP"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RP"));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | ID LP RP{
        Node temp;
        temp.subNode.push_back(createNode("ID: "+$1.show));
        temp.subNode.push_back(createNode("LP"));
        temp.subNode.push_back(createNode("RP"));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp LB Exp RB{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("LB"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RB"));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | Exp DOT ID{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("DOT"));
        temp.subNode.push_back(createNode("ID: "+$3.show));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | ID{
        Node temp;
        temp.subNode.push_back(createNode("ID: "+$1.show));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | INT{
        Node temp;
        temp.subNode.push_back(createNode("INT: "+$1.show));
        temp.show = addLine("Exp", @$.first_line);
        cout<<$1.show<<endl;
        $$ = temp;
    }
    | FLOAT{
        Node temp;
        temp.subNode.push_back(createNode("FLOAT: "+$1.show));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | CHAR{
        Node temp;
        temp.subNode.push_back(createNode("CHAR: "+$1.show));
        temp.show = addLine("Exp", @$.first_line);
        $$ = temp;
    }
    | LEXERR {
        string e = "Error type A at Line "+to_string(@$.first_line)+": Unknown lexeme \'"+$1.show+"\'";
        cout<<e<<endl;
        errList.push_back(e);
    } 
    | error {
        string e = "Error type A at Line "+to_string(@$.first_line)+": Unknown error";
        cout<<e<<endl;
        errList.push_back(e);
        cout<<$1.show<<endl;
        $$ = createNode("error");
    }
	;
Args 
    : Exp COMMA Args{
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("COMMA"));
        temp.subNode.push_back($3);
        temp.show = addLine("Args", @$.first_line);
        $$ = temp;
    }
    | Exp {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = addLine("Args", @$.first_line);
        $$ = temp;
    }
	;
%%
 
 
void yyerror(const char *s){
    fprintf(stderr, "%s\n", s);
}

void output(Node node, int num){
    int size = node.subNode.size();
    string tab(num,' ');
    cout<<tab<<node.show<<endl; 
    for (int i=0;i<size;i++){
        output(node.subNode[i],num+2);
    }
      
}

string addLine(string s, int line){
    return s+" ("+to_string(line)+")";
}

int main(){
    yyparse();
    // cout<<endl;
    output(program,0);
}

