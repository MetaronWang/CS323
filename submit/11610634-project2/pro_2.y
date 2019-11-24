%{
#include "lex.yy.c"
#include "stdlib.h"
#include "stdio.h"
// #include "node.hpp"
#include "queue"
#include "stack"
#include "iostream"
#include "string"
#include "vector"
#include "type.cpp"
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
        program.type = "Program";
    }
	;
ExtDefList 
    : ExtDef ExtDefList {
        Node temp = createNode(addLine("ExtDefList", @$.first_line), "ExtDefList"); 
        temp.subNode.push_back($1);
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        $$ = temp;
    }
    | 
    {
        Node temp = createNode(addLine("ExtDefList", @$.first_line), "ExtDefList");         
        $$ = temp;
    }
	;
ExtDef 
    : 
    Specifier ExtDecList error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \';\'";
        errList.push_back(e);
    }
    |
    Specifier error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \';\'";
        errList.push_back(e);
    }
    |
    Specifier ExtDecList SEMI {
        Node temp = createNode( addLine("ExtDef", @$.first_line),"ExtDef");
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back(createNode("SEMI","SEMI"));
        $$ = temp;
    }
    | Specifier SEMI {
        Node temp = createNode( addLine("ExtDef", @$.first_line),"ExtDef");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("SEMI","SEMI")); 
        $$ = temp;
    }
    | Specifier FunDec CompSt {
        Node temp = createNode( addLine("ExtDef", @$.first_line),"ExtDef");
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back($3);
        $$ = temp;
    }
	;
ExtDecList 
    : VarDec {
        Node temp = createNode(addLine("ExtDecList", @$.first_line),"ExtDecList");
        temp.subNode.push_back($1);
        $$ = temp;
    }
    | VarDec COMMA ExtDecList {
        Node temp = createNode(addLine("ExtDecList", @$.first_line),"ExtDecList");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("COMMA","COMMA"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
	;
Specifier 
    : TYPE {
        Node temp = createNode( addLine("Specifier", @$.first_line),"Specifier");
        temp.subNode.push_back(createNode("TYPE: "+$1.show, "TYPE"));
        $$ = temp;
    }
    | StructSpecifier {
        Node temp = createNode( addLine("Specifier", @$.first_line),"Specifier");
        temp.subNode.push_back($1);
        $$ = temp;
    }
	;
StructSpecifier 
    : STRUCT ID LC DefList RC {
        Node temp = createNode( addLine("StructSpecifier", @$.first_line),"StructSpecifier");
        temp.subNode.push_back(createNode("STRUCT","STRUCT"));
        temp.subNode.push_back(createNode("ID: "+$2.show, "ID"));
        temp.subNode.push_back(createNode("LC","LC"));
        temp.subNode.push_back($4);
        temp.subNode.push_back(createNode("RC","RC"));
        $$ = temp;
    }
    | STRUCT LEXERR LC DefList RC {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$2.show;
        errList.push_back(e);
    }
    | STRUCT ID {
        Node temp = createNode( addLine("StructSpecifier", @$.first_line),"StructSpecifier");
        temp.subNode.push_back(createNode("STRUCT","STRUCT"));
        temp.subNode.push_back(createNode("ID: "+$2.show,"ID"));
        $$ = temp;
    }
    | STRUCT LEXERR {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$2.show;
        errList.push_back(e);
    }
	;
VarDec 
    :
    ID {
        Node temp = createNode(addLine("VarDec", @$.first_line),"VarDec");
        temp.subNode.push_back(createNode("ID: "+$1.show, "ID"));
        $$ = temp;
    }
    | LEXERR {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$1.show;
        errList.push_back(e);
    }
    | VarDec LB INT RB {
        Node temp = createNode(addLine("VarDec", @$.first_line), "VarDec");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("LB","LB"));
        temp.subNode.push_back(createNode("INT: "+$3.show,"INT"));
        temp.subNode.push_back(createNode("RB","RB"));
        $$ = temp;
    }
	;
FunDec 
    : ID LP error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing Right Parentheses \')\'";
        errList.push_back(e);
    }
    | ID LP VarList error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing Right Parentheses \')\'";
        errList.push_back(e);
    }
    |
    ID LP VarList RP {
        Node temp = createNode( addLine("FunDec", @$.first_line), "FunDec");
        temp.subNode.push_back(createNode("ID: "+$1.show, "ID"));
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RP","RP"));
        $$ = temp;
    }
    | LEXERR LP VarList RP {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$1.show;
        errList.push_back(e);
    }
    | ID LP RP {
        Node temp = createNode( addLine("FunDec", @$.first_line), "FunDec");
        temp.subNode.push_back(createNode("ID: "+$1.show, "ID"));
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back(createNode("RP","RP"));
        $$ = temp;
    }
    | LEXERR LP RP {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$1.show;
        errList.push_back(e);
    }
	;
VarList 
    : ParamDec COMMA VarList {
        Node temp = createNode(addLine("VarList", @$.first_line),"VarList");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("COMMA","COMMA"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | ParamDec {
        Node temp = createNode(addLine("VarList", @$.first_line),"VarList");
        temp.subNode.push_back($1);
        $$ = temp;
    }
	;
ParamDec 
    : Specifier VarDec{
        Node temp = createNode(addLine("ParamDec", @$.first_line),"ParamDec");
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        $$ = temp;
    }
	;
CompSt 
    : LC DefList StmtList error{
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing Right Curly Braces \'}\'";
        errList.push_back(e);
    }
    |
    LC DefList StmtList RC {
        Node temp = createNode(addLine("CompSt", @$.first_line),"CompSt");
        temp.subNode.push_back(createNode("LC", "LC"));
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        if (! $3.subNode.empty())
            temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RC","RC"));
        $$ = temp;
    }
	;
StmtList 
    : Stmt StmtList {
        Node temp = createNode(addLine("StmtList", @$.first_line),"StmtList");
        temp.subNode.push_back($1);
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        $$ = temp;
    }
    | 
    {
        Node temp = createNode(addLine("StmtList", @$.first_line),"StmtList");
        $$ = temp;
    }
	;
Stmt 
    : Exp error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \';\'";
        errList.push_back(e);
    }
    |
    Exp SEMI {
        Node temp = createNode(addLine("Stmt", @$.first_line),"Stmt");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("SEMI","SEMI"));
        $$ = temp;
    }
    | CompSt {
        Node temp = createNode(addLine("Stmt", @$.first_line),"Stmt");
        temp.subNode.push_back($1);
        $$ = temp;
    }
    |RETURN Exp error{
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \';\'";
        errList.push_back(e);
    }
    | RETURN Exp SEMI {
        Node temp = createNode(addLine("Stmt", @$.first_line),"Stmt");
        temp.subNode.push_back(createNode("RETURN","RETURN"));
        temp.subNode.push_back($2);
        temp.subNode.push_back(createNode("SEMI","SEMI"));
        $$ = temp;
    }
    | IF LP Exp RP Stmt {
        Node temp = createNode(addLine("Stmt", @$.first_line),"Stmt");
        temp.subNode.push_back(createNode("IF","IF"));
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RP","RP"));
        temp.subNode.push_back($5);
        $$ = temp;
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        Node temp = createNode(addLine("Stmt", @$.first_line),"Stmt");
        temp.subNode.push_back(createNode("IF","IF"));
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RP","RP"));
        temp.subNode.push_back($5);
        temp.subNode.push_back(createNode("ELSE","ELSE"));
        temp.subNode.push_back($7);
        $$ = temp;
    }
    | WHILE LP Exp RP Stmt {
        Node temp = createNode(addLine("Stmt", @$.first_line),"Stmt");
        temp.subNode.push_back(createNode("WHILE","WHILE"));
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RP","RP"));
        temp.subNode.push_back($5);
        $$ = temp;
    }
	;
DefList 
    : Def DefList {
        Node temp = createNode(addLine("DefList", @$.first_line), "DefList");
        temp.subNode.push_back($1);
        if (! $2.subNode.empty())
            temp.subNode.push_back($2);
        $$ = temp;
    }
    | 
    {
        Node temp = createNode(addLine("DefList", @$.first_line), "DefList");
        $$ = temp;
    }
	;
Def 
    :
    Specifier DecList error{
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing semicolon \';\'";
        errList.push_back(e);
    }
    |Specifier DecList SEMI {
        Node temp = createNode(addLine("Def", @$.first_line),"Def");
        temp.subNode.push_back($1);
        temp.subNode.push_back($2);
        temp.subNode.push_back(createNode("SEMI","SEMI"));
        $$ = temp;
    }
	;
DecList 
    : Dec {
        Node temp = createNode(addLine("DecList", @$.first_line),"DecList");
        temp.subNode.push_back($1);
        $$ = temp;
    }
    | Dec COMMA DecList {
        Node temp = createNode(addLine("DecList", @$.first_line),"DecList");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("COMMA","COMMA"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
	;
Dec 
    : VarDec {
        Node temp = createNode(addLine("Dec", @$.first_line),"Dec");
        temp.subNode.push_back($1);
        $$ = temp;
    }
    | VarDec ASSIGN Exp {
        Node temp = createNode(addLine("Dec", @$.first_line),"Dec");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("ASSIGN","ASSIGN"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
	;
Exp 
    :
    ID LP Args error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing Right Parentheses \')\'";
        errList.push_back(e);
    }
    | ID LP error {
        string e = "Error type B at Line "+to_string(@$.first_line)+": Missing Right Parentheses \')\'";
        errList.push_back(e);
    }
    | LEXERR LP Args error {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$1.show;
        errList.push_back(e);
    }
    | Exp ASSIGN Exp {
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("ASSIGN","ASSIGN"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp LEXERR Exp {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$2.show;
        errList.push_back(e);
    }
    | Exp AND Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("AND","AND"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp OR Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("OR","OR"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp LT Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("LT","LT"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp LE Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("LE","LE"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp GT Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("GT","GT"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp GE Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("GE","GE"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp NE Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("NE","NE"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp EQ Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("EQ","EQ"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp PLUS Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("PLUS","PLUS"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp MINUS Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("MINUS","MINUS"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp MUL Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("MUL","MUL"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp DIV Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("DIV","DIV"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | LP Exp RP{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back($2);
        temp.subNode.push_back(createNode("RP","RP"));
        $$ = temp;
    }
    | MINUS Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("MINUS","MINUS"));
        temp.subNode.push_back($2);
        $$ = temp;
    }
    | NOT Exp{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("NOT","NOT"));
        temp.subNode.push_back($2);
        $$ = temp;
    }
    | ID LP Args RP{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("ID: "+$1.show, "ID"));
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RP","RP"));
        $$ = temp;
    }
    | LEXERR LP Args RP {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$1.show;
        errList.push_back(e);
    }
    | ID LP RP{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("ID: "+$1.show, "ID"));
        temp.subNode.push_back(createNode("LP","LP"));
        temp.subNode.push_back(createNode("RP","RP"));
        $$ = temp;
    }
    | LEXERR LP RP {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$1.show;
        errList.push_back(e);
    }
    | Exp LB Exp RB{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("LB","LB"));
        temp.subNode.push_back($3);
        temp.subNode.push_back(createNode("RB","RB"));
        $$ = temp;
    }
    | Exp DOT ID{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("DOT","DOT"));
        temp.subNode.push_back(createNode("ID: "+$3.show, "ID"));
        $$ = temp;
    } 
    | Exp DOT LEXERR {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$3.show;
        errList.push_back(e);
    }
    | ID{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("ID: "+$1.show, "ID"));
        $$ = temp;
    }
    | INT{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("INT: "+$1.show, "INT"));
        $$ = temp;
    }
    | FLOAT{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("FLOAT: "+$1.show, "FLOAT"));
        $$ = temp;
    }
    | CHAR{
        Node temp = createNode(addLine("Exp", @$.first_line),"Exp");
        temp.subNode.push_back(createNode("CHAR: "+$1.show, "CHAR"));
        $$ = temp;
    }
    | LEXERR {
        string e = "Error type A at Line "+to_string(@$.first_line)+": unknown lexeme "+$1.show;
        errList.push_back(e);
    } 
	;
Args 
    : Exp COMMA Args{
        Node temp = createNode(addLine("Args", @$.first_line),"Args");
        temp.subNode.push_back($1);
        temp.subNode.push_back(createNode("COMMA","COMMA"));
        temp.subNode.push_back($3);
        $$ = temp;
    }
    | Exp {
        Node temp = createNode(addLine("Args", @$.first_line),"Args");
        temp.subNode.push_back($1);
        $$ = temp;
    }
	;
%%
 
 
void yyerror(const char *s){
    // fprintf(stderr, "%s\n", s);
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

int main(int argc, char** argv){
    if(argc>1){
        string s = argv[1];
        int size = s.size();
        s = s.substr(0, size-4);
        string in = s+".spl";
        string out = s+".out";
        freopen(in.c_str(), "r", stdin);
        freopen(out.c_str(), "w", stdout);
        freopen(out.c_str(), "w", stderr);
        cout<<"";
    }else{
        freopen("test/test_2_b04.spl", "r", stdin);
    }
    yyparse();
    if (errList.empty()){
        //output(program,0);
        generateGrammerTree(program);
    }
    else
        errOut();

}

