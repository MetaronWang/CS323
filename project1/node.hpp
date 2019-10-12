#include <iostream>
#include <stdio.h>
#include <string>
#include<stdlib.h> 
#include <vector>
using namespace std;
class ProgramNode;
class ExtDefListNode;
class ExtDefNode;
class ExtDecListNode;
class SpecifierNode;
class StructSpecifierNode;
class VarDecNode;
class FunDecNode;
class VarListNode;
class ParamDecNode;
class CompStNode;
class StmtListNode;
class StmtNode;
class DefListNode;
class DefNode;
class DecListNode;
class DecNode;
class ExpNode;
class ArgsNode;

class Node
{
public:
    vector<Node*> subNode;
    string show;
};

class ProgramNode
{
public:
    ExtDefListNode *extDefList;
};

class ExtDefListNode
{
public:
    ExtDefNode *extDefNode;
    ExtDefListNode *extDefListNode;
};

class ExtDefNode
{
public:
    SpecifierNode *specifierNode;
    ExtDecListNode *extDecListNode;
    FunDecNode *funDecNode;
    CompStNode *compStNode;
};

class ExtDecListNode
{
public:
    VarDecNode *varDecNode;
};

class SpecifierNode
{
public:
    StructSpecifierNode *structSpecifierNode;
};

class StructSpecifierNode
{
public:
    DefListNode *defListNode;
};

class VarDecNode
{
public:
    VarDecNode *varDecNode;
};

class FunDecNode
{
public:
    VarListNode *varListNode;
};

class VarListNode
{
public:
    ParamDecNode *paramDecNode;
    VarListNode *varListNode;
};

class ParamDecNode
{
public:
    SpecifierNode *specifierNode;
    VarDecNode *varDecNode;
};

class CompStNode
{
public:
    DefListNode *defListNode;
    StmtListNode *stmtListNode;
};

class StmtListNode
{
public:
    StmtNode *stmtNode;
    StmtListNode *stmtListNode;
};

class StmtNode
{
public:
    ExpNode *expNode;
    CompStNode *compStNode;
    StmtNode *stmtNode1;
    StmtNode *stmtNode2;
};

class DefListNode
{
public:
    DefNode *defNode;
    DefListNode *defListNode;
};

class DefNode
{
public:
    SpecifierNode *specifierNode;
    DecListNode *decListNode;
};

class DecListNode
{
public:
    DecNode *decNode;
    DecListNode *decListNode;
};

class DecNode
{
public:
    VarDecNode *varDecNode;
    ExpNode *expNode;
};

class ExpNode
{
public:
    ExpNode *expNode1;
    ExpNode *expNode2;
    ArgsNode *argsNode;
};

class ArgsNode
{
public:
    ExpNode *expNode;
    ArgsNode *argsNode;
};