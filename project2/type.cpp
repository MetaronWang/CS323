#include <iostream>
#include <map>
#include <CS323/project2/node.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#pragma once
using namespace std;

map<int, string> TypeMap;

struct VarInfo {
  string name;
  int type;
  bool array;
  int dimension;
};

struct StructInfo {
  string name;
  vector<VarInfo> varList;
};

struct FuncInfo {
  string name;
  int returnType;
  vector<VarInfo> argList;
};

struct ScopeInfo {
  map<string, VarInfo> varSet;
  ScopeInfo *parentScope;
  vector<ScopeInfo> childList;
};

ScopeInfo root;
map<string, FuncInfo> funcSet;
map<string, StructInfo> structSet;

VarInfo *getVar(string name, ScopeInfo scope) {
  map<string, VarInfo>::iterator it;
  it = scope.varSet.find(name);
  if (it != scope.varSet.end()) {
    return &(it->second);
  } else {
    if (scope.parentScope != nullptr) {
      return getVar(name, *(scope.parentScope));
    } else {
      return nullptr;
    }
  }
}

bool checkScope(string name, ScopeInfo scope) {
  map<string, VarInfo>::iterator it;
  it = scope.varSet.find(name);
  if (it != scope.varSet.end()) {
    return true;
  } else {
    if (scope.parentScope != nullptr) {
      return checkScope(name, *(scope.parentScope));
    } else {
      return false;
    }
  }
}

FuncInfo *getFunc(string name) {
  map<string, FuncInfo>::iterator it;
  it = funcSet.find(name);
  if (it != funcSet.end()) {
    return &(it->second);
  } else {
    return nullptr;
  }
}

bool checkFunc(string name) {
  map<string, FuncInfo>::iterator it;
  it = funcSet.find(name);
  if (it != funcSet.end()) {
    return true;
  } else {
    return false;
  }
}

StructInfo *getStruct(string name) {
  map<string, StructInfo>::iterator it;
  it = structSet.find(name);
  if (it != structSet.end()) {
    return &(it->second);
  } else {
    return nullptr;
  }
}

bool checkStruct(string name) {
  map<string, StructInfo>::iterator it;
  it = structSet.find(name);
  if (it != structSet.end()) {
    return true;
  } else {
    return false;
  }
}

void analyzeGrammer(Node node, ScopeInfo scope){

}

void SetScope(Node node, ScopeInfo parent) {
  int size = node.subNode.size();
  bool LC = false;
  for (int i = 0; i < size; i++) {
    if (node.subNode[i].type == "LC") {
      LC = true;
    } else if (node.subNode[i].type == "RC") {
      LC = false;
    } else {
      if (LC) {
        ScopeInfo child;
        SetScope(node.subNode[i], child);
        parent.childList.push_back(child);
      } else {
      }
    }
  }
}

void generateGrammerTree(Node program) {}