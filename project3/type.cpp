#include "node.hpp"
#include "ir.cpp"
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#pragma once
using namespace std;

int speciferAnalysis(Node *specifer, ScopeInfo *scope);

void compStAnalysis(Node *compSt, ScopeInfo *scope, int type);

int *expAnalysis(Node *exp, ScopeInfo *scope);

VarInfo createVar(Node *varDec, int type);

string getLineFromShow(string show) {
    int size = show.size();
    int start = show.rfind("(");
    int end = show.rfind(")");
    int length = end - start;
    if (length > 0) {
        length--;
    }
    return show.substr(start + 1, length);
}

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
    FuncInfo read;
    read.name = "read";
    read.returnType = 0;
    FuncInfo write;
    write.name = "write";
    write.returnType = 3;
    VarInfo writeInt;
    writeInt.name = "output";
    writeInt.array = false;
    writeInt.dimension = 0;
    writeInt.type = 0;
    write.argSet.push_back(writeInt);
    funcSet[read.name] = read;
    funcSet[write.name] = write;
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

bool findVarInThisScope(string name, ScopeInfo *scope) {
    map<string, VarInfo>::iterator it;
    it = scope->varSet.find(name);
    if (it != scope->varSet.end()) {
        return true;
    } else {
        return false;
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

void setScopeInfo(Node *node, ScopeInfo *scope) {
    node->scopeInfo = scope;
    int size = node->subNode.size();
    for (int i = 0; i < size; i++) {
        setScopeInfo(&(node->subNode[i]), scope);
    }
}

bool structEqual(int type1, int type2) {
    map<int, string>::iterator itn;
    map<string, StructInfo>::iterator its;
    string name1, name2;
    StructInfo struct1, struct2;
    itn = typeMap.find(type1);
    if (itn == typeMap.end()) {
        return false;
    } else {
        name1 = itn->second;
        its = structSet.find(name1);
        if (its == structSet.end()) {
            return false;
        } else {
            struct1 = its->second;
        }
    }
    itn = typeMap.find(type2);
    if (itn == typeMap.end()) {
        return false;
    } else {
        name2 = itn->second;
        its = structSet.find(name2);
        if (its == structSet.end()) {
            return false;
        } else {
            struct2 = its->second;
        }
    }
    if (struct1.varSet.size() == struct2.varSet.size()) {
        for (int i = 0; i < struct1.varSet.size(); i++) {
            if (struct1.varSet[i].array != struct2.varSet[i].array) {
                return false;
            } else if (struct1.varSet[i].type <= 4 || struct2.varSet[i].type <= 4) {
                if (struct1.varSet[i].type != struct2.varSet[i].type) {
                    return false;
                }
            } else {
                if (!structEqual(struct1.varSet[i].type, struct2.varSet[i].type)) {
                    return false;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

VarInfo createVar(Node *varDec, int type) {
    VarInfo var;
    var.array = false;
    var.dimension = 0;
    while (varDec->subNode.size() > 1) {
        varDec = &varDec->subNode[0];
        var.array = true;
        var.dimension += 1;
    }
    var.name = varDec->subNode[0].show.substr(4);
    var.type = type;
    return var;
}

void createStruct(Node *defList, string name, ScopeInfo *scope) {
    StructInfo s;
    s.name = name;
    int size1 = defList->subNode.size();
    while (size1 > 0) {
        Node *def = &defList->subNode[0];
        int type = speciferAnalysis(&def->subNode[0], scope);
        if (type < 0) {
            break;
        }
        Node *decList = &def->subNode[1];
        int size2 = decList->subNode.size();
        while (size2 > 0) {
            VarInfo temp = createVar(&decList->subNode[0].subNode[0], type);
            int size = s.varSet.size();
            bool exist = false;
            for (int i = 0; i < size; i++) {
                if (s.varSet[i].name == temp.name) {
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                if (decList->subNode[0].subNode.size() > 1) {
                    int *type1 = expAnalysis(&decList->subNode[0].subNode[2], scope);
                    if (type1[0] == temp.type && type1[1] == temp.array) {
                        s.varSet.push_back(temp);
                    } else {
                        errList.push_back(
                                "Error type 5 at Line " + getLineFromShow(decList->subNode[0].subNode[2].show) +
                                ": unmatching types on both sides of assignment operator (=)");
                    }
                } else {
                    s.varSet.push_back(temp);
                };
            } else {
                errList.push_back("Error type 16 at Line " + getLineFromShow(defList->subNode[0].subNode[0].show) +
                                  ": The field has existed");
            }
            if (size2 > 1) {
                decList = &decList->subNode[2];
                size2 = decList->subNode.size();
            } else {
                break;
            }
        }
        if (size1 > 1) {
            defList = &defList->subNode[1];
            size1 = defList->subNode.size();
        } else {
            break;
        }
    }
    structSet[name] = s;
    int index = types.size();
    types[name] = index;
    typeMap[index] = name;
}

int structAnalysis(Node *structSpecifier, ScopeInfo *scope) {
    int size = structSpecifier->subNode.size();
    if (size == 2) {
        map<string, int>::iterator it =
                types.find(structSpecifier->subNode[1].show.substr(4));
        if (it == types.end()) {
            errList.push_back("Error type 17 at Line " + getLineFromShow(structSpecifier->show) +
                              ": The Struct hasn't been defined");
            return -1;
        } else {
            return it->second;
        }
    } else {
        map<string, int>::iterator it =
                types.find(structSpecifier->subNode[1].show.substr(4));
        if (it != types.end()) {
            errList.push_back("Error type 15 at Line " + getLineFromShow(structSpecifier->show) +
                              ": redefine the same structure type");
            return -1;
        } else {
            createStruct(&structSpecifier->subNode[3],
                         structSpecifier->subNode[1].show.substr(4), scope);
            return types.size();
        }
    }
}

void defListAnalysis(Node *defList, ScopeInfo *scope) {
    int size1 = defList->subNode.size();
    while (size1 > 0) {
        Node *def = &defList->subNode[0];
        int type = speciferAnalysis(&def->subNode[0], scope);
        if (type < 0) {
            break;
        }
        Node *decList = &def->subNode[1];
        int size2 = decList->subNode.size();
        while (size2 > 0) {
            VarInfo temp = createVar(&decList->subNode[0].subNode[0], type);
            bool exist = findVarInThisScope(temp.name, scope);
            if (!exist) {
                if (decList->subNode[0].subNode.size() > 1) {
                    int *type1 = expAnalysis(&decList->subNode[0].subNode[2], scope);
                    if (type1[0] == temp.type && type1[1] == temp.array) {
                        scope->varSet[temp.name] = temp;
                    } else if (temp.type == 1 && type1[0] == 0 && type1[1] == temp.array) {
                        scope->varSet[temp.name] = temp;
                    } else {
                        errList.push_back(
                                "Error type 5 at Line " + getLineFromShow(decList->subNode[0].subNode[2].show) +
                                ": unmatching types on both sides of assignment operator (=)");
                    }
                } else {
                    scope->varSet[temp.name] = temp;
                };
            } else {
                errList.push_back("Error type 3 at Line " + getLineFromShow(decList->subNode[0].subNode[0].show) +
                                  ": variable is redefined in the same scope");
            }
            if (size2 > 1) {
                decList = &decList->subNode[2];
                size2 = decList->subNode.size();
            } else {
                break;
            }
        }
        if (size1 > 1) {
            defList = &defList->subNode[1];
            size1 = defList->subNode.size();
        } else {
            break;
        }
    }
}

vector<int *> argsAnalysis(Node *args, ScopeInfo *scope) {
    vector<int *> argTypes;
    int size = args->subNode.size();
    while (size > 0) {
        argTypes.push_back(expAnalysis(&args->subNode[0], scope));
        if (size > 1) {
            args = &args->subNode[2];
            size = args->subNode.size();
        } else {
            break;
        }
    }
    return argTypes;
}

bool checkLeftValue(Node *exp) {
    int size = exp->subNode.size();
    switch (size) {
        case 1: {
            if (exp->subNode[0].type == "ID") {
                return true;
            } else {
                return false;
            }
            break;
        }
        case 3: {
            if (exp->subNode[1].type == "Exp" || exp->subNode[1].type == "DOT") {
                return true;
            } else {
                return false;
            }
            break;
        }
        case 4: {
            if (exp->subNode[0].type == "Exp") {
                return true;
            } else {
                return false;
            }
            break;
        }
        default: {
            return false;
        }
    }
}

int *expAnalysis(Node *exp, ScopeInfo *scope) {
    int size = exp->subNode.size();
    int *returnArray = new int[2];
    returnArray[0] = -1;
    returnArray[1] = 0;
    switch (size) {
        case 1: {
            if (exp->subNode[0].type == "ID") {
                VarInfo *var = getVar(exp->subNode[0].show.substr(4), scope);
                if (var == nullptr) {
                    errList.push_back("Error type 1 at Line " + getLineFromShow(exp->show) +
                                      ": variable is used without definition");
                    returnArray[0] = -1;
                    returnArray[1] = 0;
                } else {
                    returnArray[0] = var->type;
                    returnArray[1] = var->array;
                }
            } else if (exp->subNode[0].type == "INT") {
                returnArray[0] = 0;
                returnArray[1] = 0;
            } else if (exp->subNode[0].type == "FLOAT") {
                returnArray[0] = 1;
                returnArray[1] = 0;
            } else if (exp->subNode[0].type == "CHAR") {
                returnArray[0] = 2;
                returnArray[1] = 0;
            } else {
                returnArray[0] = -1;
                returnArray[1] = 0;
            }
            break;
        }
        case 2: {
            int *type = expAnalysis(&exp->subNode[1], scope);
            if (type[0] == -1) {
                returnArray[0] = -1;
                returnArray[1] = 0;
            } else {
                if (exp->subNode[0].type == "MINUS") {
                    if (type[0] < 2 && type[1] == 0) {
                        returnArray[0] = type[0];
                        returnArray[1] = type[1];
                    } else {
                        if (type[1] == 1) {
                            errList.push_back("Error type 7 at Line " + getLineFromShow(exp->subNode[1].show) +
                                              ": unmatching operands, such as adding an integer to a structure variable");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 7 at Line " + getLineFromShow(exp->subNode[1].show) +
                                              ": unmatching operands, such as adding an integer to a structure variable");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    }
                } else if (exp->subNode[0].type == "NOT") {
                    if (type[0] == 4 && type[1] == 0) {
                        returnArray[0] = type[0];
                        returnArray[1] = type[1];
                    } else {
                        if (type[1] == 1) {
                            errList.push_back("Error type 7 at Line " + getLineFromShow(exp->subNode[1].show) +
                                              ": unmatching operands, such as adding an integer to a structure variable");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 7 at Line " + getLineFromShow(exp->subNode[1].show) +
                                              ": unmatching operands, such as adding an integer to a structure variable");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    }
                }
            }
            break;
        }
        case 3: {
            if (exp->subNode[0].type == "Exp" && exp->subNode[2].type == "Exp") {
                int *type1 = expAnalysis(&exp->subNode[0], scope);
                int *type2 = expAnalysis(&exp->subNode[2], scope);
                if (exp->subNode[1].type == "AND" || exp->subNode[1].type == "OR") {
                    if (type1[0] == 4 && type2[0] == 4) {
                        if (type1[1] == 0 && type2[1] == 0) {
                            returnArray[0] = 4;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 7 at Line " + getLineFromShow(exp->subNode[0].show) +
                                              ": unmatching operands, such as adding an integer to a structure variable");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    } else {
                        errList.push_back(
                                "Error type 7 at Line " + getLineFromShow(exp->subNode[0].show) +
                                ": unmatching operands, such as adding an integer to a structure variable");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                } else if (exp->subNode[1].type == "LT" || exp->subNode[1].type == "LE" ||
                           exp->subNode[1].type == "GT" || exp->subNode[1].type == "GE" ||
                           exp->subNode[1].type == "NE" || exp->subNode[1].type == "EQ") {
                    if (type1[0] < 2 && type2[0] < 2) {
                        if (type1[1] == 0 && type2[1] == 0) {
                            returnArray[0] = 4;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 7 at Line " + getLineFromShow(exp->subNode[0].show) +
                                              ": unmatching operands, such as adding an integer to a structure variable");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    } else {
                        errList.push_back(
                                "Error type 7 at Line " + getLineFromShow(exp->subNode[0].show) +
                                ": unmatching operands, such as adding an integer to a structure variable");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                } else if (exp->subNode[1].type == "PLUS" || exp->subNode[1].type == "MINUS" ||
                           exp->subNode[1].type == "MUL" || exp->subNode[1].type == "DIV") {
                    if (type1[0] < 2 && type2[0] < 2) {
                        if (type1[1] == 0 && type2[1] == 0) {
                            if (type1[0] == 1 || type2[0] == 1) {
                                returnArray[0] = 1;
                            } else {
                                returnArray[0] = 0;
                            }
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 7 at Line " + getLineFromShow(exp->subNode[0].show) +
                                              ": unmatching operands, such as adding an integer to a structure variable");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    } else {
                        errList.push_back(
                                "Error type 7 at Line " + getLineFromShow(exp->subNode[0].show) +
                                ": unmatching operands, such as adding an integer to a structure variable");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                } else if (exp->subNode[1].type == "ASSIGN") {
                    if (!checkLeftValue(&exp->subNode[0])) {
                        errList.push_back("Error type 6 at Line " + getLineFromShow(exp->subNode[0].show) +
                                          ": rvalue on the left side of assignment operator");
                    } else if (type2[1] == 3) {
                        errList.push_back("Error type 5 at Line " + getLineFromShow(exp->subNode[2].show) +
                                          ": unmatching types on both sides of assignment operator (=)");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    } else if (type1[0] == type2[0] && type1[1] == type2[1]) {
                        returnArray[0] = 3;
                        returnArray[1] = 0;
                    } else if (type1[0] == 1 && type2[0] == 0 && type1[1] == type2[1]) {
                        returnArray[0] = 3;
                        returnArray[1] = 0;
                    }else if (type1[0] == 0 && type2[0] == 4 && type1[1] == type2[1]) {
                        returnArray[0] = 3;
                        returnArray[1] = 0;
                    } else if (type1[0] > 4 && type2[0] > 4) {
                        if (structEqual(type1[0], type2[0])) {
                            returnArray[0] = 3;
                            returnArray[1] = 0;
                        } else {
                            errList.push_back("Error type 5 at Line " + getLineFromShow(exp->subNode[0].show) +
                                              ": unmatching types on both sides of assignment operator (=)");
                            returnArray[0] = -1;
                            returnArray[1] = 0;
                        }
                    } else {
                        errList.push_back("Error type 5 at Line " + getLineFromShow(exp->subNode[0].show) +
                                          ": unmatching types on both sides of assignment operator (=)");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                }
            } else if (exp->subNode[0].type == "LP" && exp->subNode[2].type == "RP") {
                return expAnalysis(&exp->subNode[1], scope);
            } else if (exp->subNode[0].type == "ID") {
                FuncInfo *func = getFunc(exp->subNode[0].show.substr(4));
                if (func != nullptr) {
                    if (func->argSet.size() != 0) {
                        errList.push_back("Error type 9 at Line " + getLineFromShow(exp->show) +
                                          ": the function’s arguments mismatch the declared parameters (either types or numbers, or both)");
                    }
                    returnArray[0] = func->returnType;
                    returnArray[1] = 0;

                } else {
                    VarInfo *var = getVar(exp->subNode[0].show.substr(4), scope);
                    if (var == nullptr) {
                        errList.push_back("Error type 2 at Line " + getLineFromShow(exp->show) +
                                          ": function is invoked without definition");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    } else {
                        errList.push_back("Error type 11 at Line " + getLineFromShow(exp->show) +
                                          ": applying function invocation operator (foo(...)) on non-function names");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                }
            } else if (exp->subNode[2].type == "ID") {
                int *type = expAnalysis(&exp->subNode[0], scope);
                if (type[0] == -1) {
                    returnArray[0] = -1;
                    returnArray[1] = 0;
                } else {
                    if (type[0] < 4 || type[1] == 1) {
                        errList.push_back("Error type 13 at Line " + getLineFromShow(exp->subNode[0].show) +
                                          " accessing member of non-structure variable (i.e., misuse the dot operator)");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    } else {
                        string field = exp->subNode[2].show.substr(4);
                        StructInfo structInfo = structSet.find(typeMap.find(type[0])->second)->second;
                        for (int i = 0; i < structInfo.varSet.size(); i++) {
                            if (structInfo.varSet[i].name == field) {
                                returnArray[0] = structInfo.varSet[i].type;
                                returnArray[1] = structInfo.varSet[i].array;
                                return returnArray;
                            }
                        }
                        errList.push_back("Error type 14 at Line " + getLineFromShow(exp->subNode[0].show) +
                                          ": accessing an undefined structure member");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                }
            }
            break;
        }
        case 4: {
            if (exp->subNode[0].type == "ID") {
                FuncInfo *func = getFunc(exp->subNode[0].show.substr(4));
                if (func != nullptr) {
                    vector<int *> args = argsAnalysis(&exp->subNode[2], scope);
                    int argSize = args.size();
                    if (argSize != func->argSet.size()) {
                        errList.push_back("Error type 9 at Line " + getLineFromShow(exp->subNode[2].show) +
                                          ": the function’s arguments mismatch the declared parameters (either types or numbers, or both)");
                    } else {
                        for (int i = 0; i < argSize; i++) {
                            if (args[i][0] != func->argSet[i].type || args[i][1] != func->argSet[i].array) {
                                errList.push_back("Error type 9 at Line " + getLineFromShow(exp->subNode[2].show) +
                                                  ": the function’s arguments mismatch the declared parameters (either types or numbers, or both)");
                                break;
                            }
                        }
                    }
                    returnArray[0] = func->returnType;
                    returnArray[1] = 0;
                } else {
                    VarInfo *var = getVar(exp->subNode[0].show.substr(4), scope);
                    if (var == nullptr) {
                        errList.push_back("Error type 2 at Line " + getLineFromShow(exp->show) +
                                          ": function is invoked without definition");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    } else {
                        errList.push_back("Error type 11 at Line " + getLineFromShow(exp->show) +
                                          ": applying function invocation operator (foo(...)) on non-function names");
                        returnArray[0] = -1;
                        returnArray[1] = 0;
                    }
                }
            } else if (exp->subNode[0].type == "Exp") {
                int *type = expAnalysis(&exp->subNode[0], scope);
                if (type[1] == 1) {
                    int *type1 = expAnalysis(&exp->subNode[2], scope);
                    if (type1[0] == 0 && type1[1] == 0) {
                        returnArray[0] = type[0];
                        returnArray[1] = 0;
                    } else {
                        errList.push_back("Error Type 12 at Line " + getLineFromShow(exp->subNode[2].show) +
                                          ": array indexing with non-integer type expression");
                        returnArray[0] = type[0];
                        returnArray[1] = 0;
                    }
                } else {
                    errList.push_back("Error type 10 at Line " + getLineFromShow(exp->subNode[0].show) +
                                      " applying indexing operator ([...]) on non-array type variables");
                    returnArray[0] = -1;
                    returnArray[1] = 0;
                }
            }
            break;
        }
    }
    return returnArray;
}

void stmtAnalysis(Node *stmt, ScopeInfo *scope, int type) {
    int size = stmt->subNode.size();
    switch (size) {
        case 1: {//CompSt
            compStAnalysis(&stmt->subNode[0], scope, type);
            break;
        }
        case 2: {//Exp SEMI
            expAnalysis(&stmt->subNode[0], scope);
            break;
        }
        case 3: {//RETURN Exp SEMI
            int *returnType = expAnalysis(&stmt->subNode[1], scope);
            if (type != returnType[0]) {
                errList.push_back("Error type 8 at Line " + getLineFromShow(stmt->subNode[1].show) +
                                  ": the function’s return value type mismatches the declared type");
            }
            break;
        }
        case 5: {//IF / WHILE
            int *returnType = expAnalysis(&stmt->subNode[2], scope);
            if (4 != returnType[0]) {
                errList.push_back("Error type 18 at Line " + getLineFromShow(stmt->subNode[2].show) +
                                  ": Only Bool can be used in the if()/while()");
            }
            ScopeInfo child;
            child.parentScope = scope;
            scope->childList.push_back(child);
            setScopeInfo(&(stmt->subNode[4]), &(scope->childList[scope->childList.size() - 1]));
            stmtAnalysis(&stmt->subNode[4], &(scope->childList[scope->childList.size() - 1]), type);
            break;
        }
        case 7: {//IF-ELSE
            int *returnType = expAnalysis(&stmt->subNode[2], scope);
            if (4 != returnType[0]) {
                errList.push_back("Error type 18 at Line " + getLineFromShow(stmt->subNode[2].show) +
                                  ": Only Bool can be used in the if()/while()");
            }
            ScopeInfo child1;
            child1.parentScope = scope;
            scope->childList.push_back(child1);
            setScopeInfo(&(stmt->subNode[4]), &(scope->childList[scope->childList.size() - 1]));
            stmtAnalysis(&stmt->subNode[4], &(scope->childList[scope->childList.size() - 1]), type);
            ScopeInfo child2;
            child2.parentScope = scope;
            scope->childList.push_back(child2);
            setScopeInfo(&(stmt->subNode[6]), &(scope->childList[scope->childList.size() - 1]));
            stmtAnalysis(&stmt->subNode[6], &(scope->childList[scope->childList.size() - 1]), type);
            break;
        }
    }
}

void stmtListAnalysis(Node *stmtList, ScopeInfo *scope, int type) {
    int size = stmtList->subNode.size();
    while (size > 0) {
        stmtAnalysis(&stmtList->subNode[0], scope, type);
        if (size > 1) {
            stmtList = &stmtList->subNode[1];
            size = stmtList->subNode.size();
        } else {
            break;
        }

    }
}

void compStAnalysis(Node *compSt, ScopeInfo *scope, int type) {
    Node *defList = &compSt->subNode[1];
    Node *stmtList;
    if (defList->type == "DefList") {
        defListAnalysis(defList, scope);
        stmtList = &compSt->subNode[2];
    } else {
        stmtList = &compSt->subNode[1];
    }
    if (stmtList->type == "StmtList")
        stmtListAnalysis(stmtList, scope, type);
}

void funcAnalysis(Node *func, Node *compSt, ScopeInfo *scope, int type) {
    FuncInfo f;
    f.returnType = type;
    f.name = func->subNode[0].show.substr(4);
    map<string, FuncInfo>::iterator it = funcSet.find(f.name);
    if (it != funcSet.end()) {
        errList.push_back("Error type 4 at Line " + getLineFromShow(func->show) +
                          ": function is redefined (in the global scope, since we don’t have nested function)");
        return;
    }
    int size = func->subNode.size();
    if (size > 3) {
        Node *varList = &func->subNode[2];
        int size1 = varList->subNode.size();
        while (size1 > 0) {
            int type = speciferAnalysis(&varList->subNode[0].subNode[0], scope);
            VarInfo temp = createVar(&varList->subNode[0].subNode[1], type);
            int argSize = f.argSet.size();
            bool exist = false;
            for (int i = 0; i < argSize; i++) {
                if (f.argSet[i].name == temp.name) {
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                f.argSet.push_back(temp);
                scope->varSet[temp.name] = temp;
            } else {
                errList.push_back("Error type 3 at Line " + getLineFromShow(func->subNode[2].show) +
                                  ": variable is redefined in the same scope");
            }
            if (size1 > 1) {
                varList = &varList->subNode[2];
                size1 = varList->subNode.size();
            } else {
                size1 = 0;
                break;
            }

        }
    }
    funcSet[f.name] = f;
    compStAnalysis(compSt, scope, f.returnType);
}

void extDecListAnalysis(Node *extDecList, ScopeInfo *scope, int type) {
    int size = extDecList->subNode.size();
    while (size > 0) {
        VarInfo temp = createVar(&extDecList->subNode[0], type);
        bool exist = findVarInThisScope(temp.name, scope);
        if (!exist) {
            scope->varSet[temp.name] = temp;
        } else {
            errList.push_back("Error type 3 at Line " + getLineFromShow(extDecList->subNode[0].show) +
                              ": variable is redefined in the same scope");
        }
        if (size > 1) {
            extDecList = &extDecList->subNode[2];
            size = extDecList->subNode.size();
        } else {
            break;
        }
    }
}

int speciferAnalysis(Node *specifer, ScopeInfo *scope) {
    if (specifer->subNode[0].type == "TYPE") {
        string type = specifer->subNode[0].show.substr(6);
        map<string, int>::iterator it = types.find(type);
        if (it == types.end()) {
            errList.push_back("Error Type 17 at Line " + getLineFromShow(specifer->show) +
                              ": Use the struct as the type without definition.");
            return -1;
        } else {
            return it->second;
        }
    } else {
        ScopeInfo child;
        scope->childList.push_back(child);
        return structAnalysis(&specifer->subNode[0],
                              &(scope->childList[scope->childList.size() - 1]));
    }
}

void extDefAnalysis(Node *extDef, ScopeInfo *scope) {
    int size = extDef->subNode.size();
    if (size == 2) {
        speciferAnalysis(&extDef->subNode[0], scope);
    } else {
        if (extDef->subNode[1].type == "FunDec") {
            ScopeInfo child;
            child.parentScope = scope;
            scope->childList.push_back(child);
            setScopeInfo(extDef, &(scope->childList[scope->childList.size() - 1]));
            funcAnalysis(&extDef->subNode[1], &extDef->subNode[2],
                         &(scope->childList[scope->childList.size() - 1]),
                         speciferAnalysis(&extDef->subNode[0], scope));
        } else {
            int type = speciferAnalysis(&extDef->subNode[0], scope);
            extDecListAnalysis(&extDef->subNode[1], scope, type);
        }
    }
}

void extDefListAnalysis(Node *extDefList, ScopeInfo *scope) {
    int size = extDefList->subNode.size();
    while (size > 0) {
        extDefAnalysis(&extDefList->subNode[0], scope);
        if (size > 1) {
            extDefList = &extDefList->subNode[1];
            size = extDefList->subNode.size();
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

void printProgram(Node node, int num) {
    int size = node.subNode.size();
    string tab(num, ' ');
    cout << tab << node.show << " " << node.scopeInfo->varSet.size() << endl;
    for (int i = 0; i < size; i++) {
        printProgram(node.subNode[i], num + 2);
    }
}

void generateGrammerTree(Node program) {
    initType();
    if (errList.size() > 0) {
        errOut();
        return;
    }
    setScopeInfo(&program, &root);
    extDefListAnalysis(&program.subNode[0], &root);
    if (errList.size() > 0) {
        errOut();
        return;
    }
    generateIR(program);
//    printProgram(program, 0);
}

