#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#pragma once
using namespace std;

vector<string> errList;

struct Node{
    vector<Node> subNode;
    string show;
};


Node createNode(string s){
    Node node;
    node.show = s;
    return node;
}
