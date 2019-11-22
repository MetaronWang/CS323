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
    ScopeInfo *parentScope = nullptr;
    vector<ScopeInfo> childList;
};

ScopeInfo root;
map<string, FuncInfo> funcSet;
map<string, StructInfo> structSet;
map<int, string> typeMap;
map<string, int> types;

int speciferAnalysis(Node specifer, ScopeInfo *scope);

void compStAnalysis(Node compSt, ScopeInfo *scope, int type);

void initType() {
    typeMap[0] = "int";
    typeMap[1] = "float";
    typeMap[2] = "char";
    typeMap[3] = "void";
    typeMap[4] = "bool";
    types["int"] = 0;
    types["float"] = 1;
    types["char"] = 2;
    types["void"] = 3;
    types["bool"] = 4;
}

VarInfo *getVar(string name, ScopeInfo *scope) {
    map<string, VarInfo>::iterator it;
    it = scope->varSet.find(name);
    if (it != scope->varSet.end()) {
        return &(it->second);
    } else {
        if (scope->parentScope != nullptr) {
            return getVar(name, scope->parentScope);
        } else {
            return nullptr;
        }
    }
}

bool findVarInScope(string name, ScopeInfo *scope) {
    map<string, VarInfo>::iterator it;
    it = scope->varSet.find(name);
    if (it != scope->varSet.end()) {
        return true;
    } else {
        if (scope->parentScope != nullptr) {
            return findVarInScope(name, scope->parentScope);
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

void defListAnalysis(Node defList, ScopeInfo *scope) {
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
            bool exist = findVarInScope(temp.name, scope);
            if (!exist) {
                scope->varSet[temp.name] = temp;
            } else {
                errList.push_back("Error type 3");
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
}

int *expAnalysis(Node exp, ScopeInfo *scope) {
    int size = exp.subNode.size();
    int returnArray[2] = {-1, 0};
    switch (size) {
        case 1: {
            if (exp.subNode[0].type == "ID") {
                VarInfo *var = getVar(exp.subNode[0].show.substr(4), scope);
                if (var == nullptr) {
                    errList.push_back("Error type 1");
                    returnArray[0] = -1;
                    returnArray[1] = 0;
                } else {
                    returnArray[0] = var->type;
                    returnArray[1] = var->array;
                }
            } else if (exp.subNode[0].type == "INT") {
                returnArray[0] = 0;
                returnArray[1] = 0;
            } else if (exp.subNode[0].type == "FLOAT") {
                returnArray[0] = 1;
                returnArray[1] = 0;
            } else if (exp.subNode[0].type == "CHAR") {
                returnArray[0] = 2;
                returnArray[1] = 0;
            } else {
                returnArray[0] = -1;
                returnArray[1] = 0;
            }
            break;
        }
        case 2: {
            int *type = expAnalysis(exp.subNode[1], scope);
            if (type[0] == -1) {
                returnArray[0] = -1;
                returnArray[1] = 0;
            } else {
                if (exp.subNode[0].type == "MINUS") {
                    if (type[0] < 2 && type[1] == 0) {
                        returnArray[0] = type[0];
                        returnArray[1] = type[1];
                    } else {
                        if (type[1] == 1) {
                            errList.push_back("Error type 7");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 18: Only int and float have minus");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    }
                } else if (exp.subNode[0].type == "NOT") {
                    if (type[0] == 4 && type[1] == 0) {
                        returnArray[0] = type[0];
                        returnArray[1] = type[1];
                    } else {
                        if (type[1] == 1) {
                            errList.push_back("Error type 7");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 18: Only bool have not");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    }
                }
            }
            break;
        }
        case 3: {
            if (exp.subNode[0].type == "Exp" && exp.subNode[2].type == "Exp") {
                int *type1 = expAnalysis(exp.subNode[0], scope);
                int *type2 = expAnalysis(exp.subNode[2], scope);
                if (exp.subNode[1].type == "AND" || exp.subNode[1].type == "OR") {
                    if (type1[0] == 4 && type2[0] == 4) {
                        if (type1[1] == 0 && type2[1] == 0) {
                            returnArray[0] = 4;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 7");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    } else {
                        errList.push_back("Error type 18: Only bool have " + exp.subNode[1].type);
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                } else if (exp.subNode[1].type == "LT" || exp.subNode[1].type == "LE" ||
                           exp.subNode[1].type == "GT" || exp.subNode[1].type == "GE" ||
                           exp.subNode[1].type == "PLUS" || exp.subNode[1].type == "MINUS" ||
                           exp.subNode[1].type == "MUL" || exp.subNode[1].type == "DIV") {
                    if (type1[0] < 2 && type2[0] < 2) {
                        if (type1[1] == 0 && type2[1] == 0) {
                            returnArray[0] = 4;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 7");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    }
                } else if (exp.subNode[1].type == "ASSIGN") {
                    if (type2[1] == 3) {
                        errList.push_back("Error type 6");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    } else if (type1[0] == type2[0] && type1[1] == type2[1]) {
                        returnArray[0] = 3;
                        returnArray[1] = 0;
                    } else if (type1[0] > 4 && type2[0] > 4) {
                        map<int, string>::iterator itn;
                        map<string, StructInfo>::iterator its;
                        string name1, name2;
                        StructInfo struct1, struct2;
                        itn = typeMap.find(type1[0]);
                        if (itn == typeMap.end()) {
                            return returnArray;
                        } else {
                            name1 = itn->second;
                            its = structSet.find(name1);
                            if (its == structSet.end()) {
                                return returnArray;
                            } else {
                                struct1 = its->second;
                            }
                        }
                        itn = typeMap.find(type2[0]);
                        if (itn == typeMap.end()) {
                            return returnArray;
                        } else {
                            name2 = itn->second;
                            its = structSet.find(name2);
                            if (its == structSet.end()) {
                                return returnArray;
                            } else {
                                struct2 = its->second;
                            }
                        }
                        if (struct1.varSet.size() == struct2.varSet.size()) {
                            for (int i = 0; i < struct1.varSet.size(); i++) {
                                if (struct1.varSet[i].type != struct2.varSet[i].type ||
                                    struct1.varSet[i].array != struct2.varSet[i].array) {
                                    errList.push_back("Error type 5");
                                    returnArray[0] = -1;
                                    returnArray[1] = 0;
                                    return returnArray;
                                }
                            }
                            returnArray[0] = 3;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 5");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    } else {
                        errList.push_back("Error type 5");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                }
            } else if (exp.subNode[0].type == "LP" && exp.subNode[2].type == "RP") {
                return expAnalysis(exp.subNode[1], scope);
            } else if (exp.subNode[0].type == "ID") {
                FuncInfo *func = getFunc(exp.subNode[0].show.substr(4));
                if (func != nullptr) {
                    if (func->argSet.size() != 0) {
                        errList.push_back("Error type 9");
                    }
                    returnArray[0] = func->returnType;
                    returnArray[1] = 0;

                } else {
                    VarInfo *var = getVar(exp.subNode[0].show.substr(4), scope);
                    if (var != nullptr) {
                        errList.push_back("Error type 2");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    } else {
                        errList.push_back("Error type 11");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                }
            } else if (exp.subNode[2].type == "ID") {
                int *type = expAnalysis(exp.subNode[0], scope);
                if (type[0] == -1) {
                    returnArray[0] = -1;
                    returnArray[1] = 0;
                } else {
                    if (type[0] < 4) {
                        errList.push_back("Error type 13");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }else{

                    }
                }
            }
            break;
        }
        case 4: {

            break;
        }
    }
    return returnArray;
}

void returnAnalysis(Node exp, ScopeInfo *scope, int type) {

}

void stmtAnalysis(Node stmt, ScopeInfo *scope, int type) {
    int size = stmt.subNode.size();
    switch (size) {
        case 1: {//CompSt
            compStAnalysis(stmt.subNode[0], scope, type);
            break;
        }
        case 2: {//Exp SEMI
            expAnalysis(stmt.subNode[0], scope);
            break;
        }
        case 3: {//RETURN Exp SEMI
            returnAnalysis(stmt.subNode[1], scope, type);
            break;
        }
        case 5: {//IF / WHILE
            returnAnalysis(stmt.subNode[2], scope, 4);
            ScopeInfo child;
            child.parentScope = scope;
            scope->childList.push_back(child);
            stmtAnalysis(stmt.subNode[4], &(scope->childList[scope->childList.size() - 1]), type);
            break;
        }
        case 7: {//IF-ELSE
            returnAnalysis(stmt.subNode[2], scope, 4);
            ScopeInfo child1;
            child1.parentScope = scope;
            scope->childList.push_back(child1);
            stmtAnalysis(stmt.subNode[4], &(scope->childList[scope->childList.size() - 1]), type);
            ScopeInfo child2;
            child2.parentScope = scope;
            scope->childList.push_back(child2);
            stmtAnalysis(stmt.subNode[4], &(scope->childList[scope->childList.size() - 1]), type);
            break;
        }
    }
}

void stmtListAnalysis(Node stmtList, ScopeInfo *scope, int type) {
    int size = stmtList.subNode.size();
    while (size > 0) {
        stmtAnalysis(stmtList.subNode[0], scope, type);
        stmtList = stmtList.subNode[1];
        size = stmtList.subNode.size();
    }
}

void compStAnalysis(Node compSt, ScopeInfo *scope, int type) {
    Node defList = compSt.subNode[1];
    Node stmtList = compSt.subNode[2];
    defListAnalysis(defList, scope);
    stmtListAnalysis(stmtList, scope, type);
}

void funcAnalysis(Node func, Node compSt, ScopeInfo *scope, int type) {
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
        while (size1 > 0) {
            int type = speciferAnalysis(varList.subNode[0].subNode[0], scope);
            VarInfo temp = createVar(varList.subNode[0].subNode[1], type);
            map<string, VarInfo>::iterator it = f.argSet.find(temp.name);
            if (it == f.argSet.end()) {
                f.argSet[temp.name] = temp;
            } else {
                errList.push_back("Error type 3");
            }
            if (size1 > 1) {
                varList = varList.subNode[2];
                size1 = varList.subNode.size();
            } else {
                size1 = 0;
                break;
            }

        }
    }
    funcSet[f.name] = f;
    compStAnalysis(compSt, scope, f.returnType);
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
        speciferAnalysis(extDef.subNode[0], scope);
    } else {
        if (extDef.subNode[1].type == "FunDec") {
            ScopeInfo child;
            child.parentScope = scope;
            child.parentScope = scope;
            scope->childList.push_back(child);
            funcAnalysis(extDef.subNode[1], extDef.subNode[2],
                         &(scope->childList[scope->childList.size() - 1]),
                         speciferAnalysis(extDef.subNode[0], scope));
        } else {
            extDecListAnalysis(extDef.subNode[1], scope);
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
    int size = scope.childList.size();
    string tab(num, ' ');
    cout << tab << scope.varSet.size() << endl;
    for (int i = 0; i < size; i++) {
        printScope(scope.childList[i], num + 1);
    }
}

void printProgram(ScopeInfo scope, int num) {
    cout << "Scope" << endl;
    printScope(scope, num);
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
            itv++;
        }
        itf++;
    }
}

void generateGrammerTree(Node program) {
    initType();
    extDefListAnalysis(program.subNode[0], &root);
    if (errList.size() > 0) {
        errOut();
    }
    printProgram(root, 0);
}