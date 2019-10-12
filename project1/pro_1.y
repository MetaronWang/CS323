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
#define YYSTYPE char *
using namespace std;
void yyerror(const char*); //必须要有
extern int yylex(void);
string lp = "(";
string rp = ")";
#define STMT(s) s+lp+to_string(lines)+rp
Node program;
%}
%error-verbose
%token INT FLOAT CHAR
%token ID TYPE STRUCT IF ELSE WHILE RETURN DOT SEMI COMMA ASSIGN LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT LP RP LB RB LC RC LINE

%type <Node *> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args
%%
Program : ExtDefList {
    program.subNode.push_back($1); 
    program.show = STMT("program");
    }
	;
ExtDefList : ExtDef ExtDefList {
    Node temp; 
    temp.subNode.push_back($1); 
    temp.subNode.push_back($2);
    temp.show = STMT("ExtDefList");
    $$ = &temp;
    }
    | {
    Node temp; 
    temp.show = STMT("ExtDefList");
    $$ = &temp;
    }
	;
ExtDef : Specifier ExtDecList SEMI {
        Node temp;
        Node semi;
        semi.show = "SEMI";
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back(&semi);
        temp.show = STMT("ExtDef");
        $$ = &temp;
    }
    | Specifier SEMI {
        Node temp;
        Node semi;
        semi.show = "SEMI";
        temp.subNode.push_back($1);
        temp.subNode.push_back(&semi);
        temp.show = STMT("ExtDef");
        $$ = &temp;
    }
    | Specifier FunDec CompSt {
        Node temp;
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back($3);
        temp.show = STMT("ExtDef");
        $$ = &temp;
    }
	;
ExtDecList : VarDec {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = STMT("ExtDecList");
        $$ = &temp;
    }
    | VarDec COMMA ExtDecList {
        Node temp;
        Node comma;
        temp.subNode.push_back($1);
        comma.show = "COMMA";
        temp.subNode.push_back($2);
        temp.show = STMT("ExtDecList");
        $$ = &temp;
    }
	;
Specifier : TYPE {
        Node temp;
        Node type;
        type.show = "TYPE: " + $1;
        temp.subNode.push_back(&type);
        temp.show = STMT("Specifier");
        $$ = &temp;
    }
    | StructSpecifier {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = STMT("Specifier");
        $$ = &temp;
    }
	;
StructSpecifier : STRUCT ID LC DefList RC {
        Node temp, struc, id, lc, rc;
        struc.show = "STRUCT";
        id.show = "ID: " + $2;
        lc.show = "LC";
        rc.show = "RC";
        temp.subNode.push_back(&struc);
        temp.subNode.push_back(&id);
        temp.subNode.push_back(&ls);
        temp.subNode.push_back($4);
        temp.subNode.push_back(&rc);
        temp.show = STMT("StructSpecifier");
        $$ = &temp;
    }
    | STRUCT ID {
        Node temp, struc, id;
        struc.show = "STRUCT";
        id.show = "ID: " + $2;
        temp.subNode.push_back(&struc);
        temp.subNode.push_back(&id);
        temp.show = STMT("StructSpecifier");
        $$ = &temp;
    }
	;
VarDec : ID {
        Node temp, id;
        id.show = "ID: "+$1;
        temp.subNode.push_back(&id);
        temp.show = STMT("VarDec");
        $$ = &temp;
    }
    | VarDec LB INT RB {
        Node temp, lb, i, rb;
        lb.show = "LB";
        rb.show = "RB";
        i.show = "INT "+$2;
        temp.subNode.push_back($1);
        temp.subNode.push_back(&lb);
        temp.subNode.push_back(&i);
        temp.subNode.push_back(&rb);
        temp.show = STMT("VarDec");
        $$ = &temp;
    }
	;
FunDec : ID LP VarList RP {
        Node temp, id, lp, rp;
        id.show = "ID: " + $1;
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(&id);
        temp.subNode.push_back(&lp);
        temp.subNode.push_back($3);
        temp.subNode.push_back(&rp);
        temp.show = STMT("FunDec");
        $$ = &temp;
    }
    | ID LP RP {
        Node temp, id, lp, rp;
        id.show = "ID: " + $1;
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(&id);
        temp.subNode.push_back(&lp);
        temp.subNode.push_back(&rp);
        temp.show = STMT("FunDec");
        $$ = &temp;
    }
	;
VarList : ParamDec COMMA VarList {
        Node temp comma;
        comma.show ="COMMA";
        temp.subNode.push_back($1);
        temp.subNode.push_back(&comma);
        temp.subNode.push_back($3);
        temp.show = STMT("VarList");
        $$ = &temp;
    }
    | ParamDec {
        Node temp;
        temp.subNode.push_back($1);
        temp.show = STMT("VarList");
        $$ = &temp;
    }
	;
ParamDec : Specifier VarDec
	;
CompSt : LC DefList StmtList RC
	;
StmtList : Stmt StmtList
    | $
	;
Stmt : Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
	;
DefList : Def DefList
    | $
	;
Def : Specifier DecList SEMI
	;
DecList : Dec
    | Dec COMMA DecList
	;
Dec : VarDec
    | VarDec ASSIGN Exp
	;
Exp : Exp ASSIGN Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp LT Exp
    | Exp LE Exp
    | Exp GT Exp
    | Exp GE Exp
    | Exp NE Exp
    | Exp EQ Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp MUL Exp
    | Exp DIV Exp
    | LP Exp RP
    | MINUS Exp
    | NOT Exp
    | ID LP Args RP
    | ID LP RP
    | Exp LB Exp LB
    | Exp DOT ID
    | ID
    | INT
    | FLOAT
    | CHAR
	;
Args : Exp COMMA Args
    | Exp
	;
%%
 
 
void yyerror(const char *s){
    fprintf(stderr, "%s\n", s);
}



int main(){
    yyparse();
}

