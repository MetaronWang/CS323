#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <map>
#include <vector>

#pragma once
using namespace std;

vector<string> errList;

struct VarInfo {
    string name;
    int type;
    bool array;
    int dimension;
};

struct StructInfo {
    string name;
    vector<VarInfo> varSet;
};

struct FuncInfo {
    string name;
    int returnType;
    vector<VarInfo> argSet;
};

struct ScopeInfo {
    map<string, VarInfo> varSet;
    ScopeInfo *parentScope = nullptr;
    vector<ScopeInfo> childList;
};

struct Node {
    vector<Node> subNode;
    string show;
    string type;
    ScopeInfo *scopeInfo;
};


void errOut() {
    int size = errList.size();
    for (int i = 0; i < size; i++) {
        cout << errList[i] << endl;
    }
}

Node createNode(string s, string type) {
    Node node;
    node.show = s;
    node.type = type;
    return node;
}