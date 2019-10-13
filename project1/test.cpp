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

void output(Node node){
    int size = node.subNode.size();
    cout<<node.show<<endl;
    cout<<size<<endl;
    cout<<(*node.subNode.front()).subNode.size()<<endl;
    
}


int main()
{
    Node temp;
    Node semi;
    semi.show = "SEMI";
    temp.subNode.push_back(&semi);
    temp.show = STMT("ExtDef");
    output(temp);
}