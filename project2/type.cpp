#include "node.hpp"
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#pragma once
using namespace std;

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
    map<string, VarInfo> argSet;
};

struct ScopeInfo {
    map<string, VarInfo> varSet;
    ScopeInfo *parentScope;
    vector<ScopeInfo> childList;
};

ScopeInfo root;
map<string, FuncInfo> funcSet;
map<string, StructInfo> structSet;
map<int, string> typeMap;
map<string, int> types;

int speciferAnalysis(Node specifer, ScopeInfo *scope);

void initType() {
    typeMap[0] = "int";
    typeMap[1] = "float";
    typeMap[2] = "char";
    types["int"] = 0;
    types["float"] = 1;
    types["char"] = 2;
}

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

VarInfo createVar(Node varDec, int type) {
    VarInfo var;
    while (varDec.subNode.size() > 1) {
        varDec = varDec.subNode[0];
    }
    var.name = varDec.subNode[0].show.substr(4);
    var.type = type;
    if (varDec.subNode.size() > 1) {
        var.array = true;
        var.dimension = 1;
    } else {
        var.array = false;
        var.dimension = 0;
    }
    return var;
}

void createStruct(Node defList, string name, ScopeInfo *scope) {
    StructInfo s;
    s.name = name;
    int size1 = defList.subNode.size();
    while (size1 > 0) {
        Node def = defList.subNode[0];
        int type = speciferAnalysis(def.subNode[0], scope);
        if (type < 0) {
            break;
        }
        Node decList = def.subNode[1];
        int size2 = decList.subNode.size();
        while (size2 > 0) {
            VarInfo temp = createVar(decList.subNode[0].subNode[0], type);
            int size = s.varSet.size();
            bool exist = false;
            for (int i = 0; i < size; i++) {
                if (s.varSet[i].name == temp.name) {
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                s.varSet.push_back(temp);
            } else {
                errList.push_back("Error type 15");
            }
            if (size2 > 1) {
                decList = decList.subNode[2];
                size2 = decList.subNode.size();
            } else {
                break;
            }
        }
        if (size1 > 1) {
            defList = defList.subNode[1];
            size1 = defList.subNode.size();
        } else {
            break;
        }
    }
    structSet[name] = s;
    int index = types.size();
    types[name] = index;
    typeMap[index] = name;
}

int structAnalysis(Node structSpecifier, ScopeInfo *scope) {
    int size = structSpecifier.subNode.size();
    if (size == 2) {
        map<string, int>::iterator it =
                types.find(structSpecifier.subNode[1].show.substr(4));
        if (it == types.end()) {
            errList.push_back("Error type 17");
            return -1;
        } else {
            return it->second;
        }
    } else {
        map<string, int>::iterator it =
                types.find(structSpecifier.subNode[1].show.substr(4));
        if (it != types.end()) {
            errList.push_back("Error type 16");
            return -1;
        } else {
            createStruct(structSpecifier.subNode[3],
                         structSpecifier.subNode[1].show.substr(4), scope);
            return types.size();
        }
    }
}

void funcAnalysis(Node func, Node coompSt, ScopeInfo *scope, int type) {
    // cout<<22<<endl;
    FuncInfo f;
    f.returnType = type;
    f.name = func.subNode[0].show.substr(4);
    map<string, FuncInfo>::iterator it = funcSet.find(f.name);
    if (it != funcSet.end()) {
        errList.push_back("Error type 4");
        return;
    }
    int size = func.subNode.size();
    if (size > 3) {
        Node varList = func.subNode[2];
        int size1 = varList.subNode.size();
        while (size1 > 1) {
            int type = speciferAnalysis(varList.subNode[0].subNode[0], scope);
            VarInfo temp = createVar(varList.subNode[0].subNode[1], type);
            map<string, VarInfo>::iterator it = f.argSet.find(temp.name);
            if (it == f.argSet.end()) {
                f.argSet[temp.name] = temp;
            } else {
                errList.push_back("Error type 3");
            }
            varList = varList.subNode[2];
            size1 = varList.subNode.size();
        }
    }
    funcSet[f.name] = f;
}

void extDecListAnalysis(Node ExtDecList, ScopeInfo *scope) {

}

int speciferAnalysis(Node specifer, ScopeInfo *scope) {
    if (specifer.subNode[0].type == "TYPE") {
        string type = specifer.subNode[0].show.substr(6);
        map<string, int>::iterator it = types.find(type);
        if (it == types.end()) {
            errList.push_back("Error Type 17");
            return -1;
        } else {
            return it->second;
        }
    } else {
        ScopeInfo child;
        scope->childList.push_back(child);
        return structAnalysis(specifer.subNode[0],
                              &(scope->childList[scope->childList.size() - 1]));
    }
}

void extDefAnalysis(Node extDef, ScopeInfo *scope) {
    int size = extDef.subNode.size();
    if (size == 2) {
        // cout<<2<<endl;
        speciferAnalysis(extDef.subNode[0], scope);
    } else {
        if (extDef.subNode[1].type == "FunDec") {
            // cout<<3<<endl;
            ScopeInfo child;
            scope->childList.push_back(child);
            funcAnalysis(extDef.subNode[1], extDef.subNode[2],
                         &(scope->childList[scope->childList.size() - 1]),
                         speciferAnalysis(extDef.subNode[0], scope));
        } else {
            extDecListAnalysis(extDef.subNode[1], scope);
        }
    }
}

void SetScope(Node node, ScopeInfo *parent) {
    int size = node.subNode.size();
    bool LC = false;
    for (int i = 0; i < size; i++) {
        if (node.subNode[i].type == "LC") {
            LC = true;
            ScopeInfo child;
            parent->childList.push_back(child);
        } else if (node.subNode[i].type == "RC") {
            LC = false;
        }
        if (LC == true) {
            SetScope(node.subNode[i],
                     &(parent->childList[parent->childList.size() - 1]));
        } else {
            SetScope(node.subNode[i], parent);
        }
    }
}

void extDefListAnalysis(Node extDefList, ScopeInfo *scope) {
    int size = extDefList.subNode.size();
    while (size > 0) {
        extDefAnalysis(extDefList.subNode[0], scope);
        if (size > 1) {
            extDefList = extDefList.subNode[1];
            size = extDefList.subNode.size();
        } else {
            size = -1;
        }
    }
}

void printScope(ScopeInfo scope, int num) {
    // int size = scope.childList.size();
    // for (int i = 0; i < size; i++) {
    //   string tab(num, ' ');
    //   cout << tab << scope.varSet.size() << endl;
    //   printScope(scope.childList[i], num + 1);
    // }
    cout << "struct" << endl;
    map<string, StructInfo>::iterator its = structSet.begin();
    while (its != structSet.end()) {
        cout << its->first << endl;
        for (int i = 0; i < its->second.varSet.size(); i++) {
            VarInfo varInfo = its->second.varSet[i];
            cout << "  " << varInfo.name << ":" << varInfo.type << endl;
        }
        its++;
    }
    cout << "func" << endl;
    map<string, FuncInfo>::iterator itf = funcSet.begin();
    while (itf != funcSet.end()) {
        map<string, VarInfo>::iterator itv = itf->second.argSet.begin();
        cout << itf->first << endl;
        while (itv != itf->second.argSet.end()) {
            cout << "  " << itv->second.name << ":" << itv->second.type << endl;
        }
        itf++;
    }
}

void generateGrammerTree(Node program) {
    initType();
    ScopeInfo parent;
    extDefListAnalysis(program.subNode[0], &parent);
    printScope(parent, 0);
}