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

void errOut(){
    int size = errList.size();
    for (int i=0;i<size;i++){
        cout<<errList[i]<<endl;
    }
}

Node createNode(string s, string type){
    Node node;
    node.show = s;
    node.type = type;
    return node;
}