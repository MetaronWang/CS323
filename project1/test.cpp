#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string>
#include <queue>
#include <iostream>
#include "node.hpp"
#include <vector>
using namespace std;
int lines = 10;
string lp = "(";
string rp = ")";
queue<string> ast;
#define STMT(s) s + lp + to_string(lines) + rp

int main()
{
    Node temp;
    Node semi;
    semi.show = "SEMI";
    temp.subNode.push_back(&semi);
    temp.show = STMT("ExtDef");
    cout<< temp.subNode[0]->show << endl;
}