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
    string type;
};


Node createNode(string s, string type){
    Node node;
    node.show = s;
    node.type = type;
    return node;
}