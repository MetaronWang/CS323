#include "node.hpp"
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

int tempNum = 0;
int constNum = 0;
int labelNum = 0;
int varNum = 0;

map<string, string> varSet;
map<string, string> constSet;

string new_label(){
    string l = "l"+to_string(labelNum);
    labelNum++;
    return l;
}

bool getConst(string value) {
    map<string, string>::iterator it = constSet.find(value);
    if (it != constSet.end()) {
        return true;
    } else {
        return false;
    }
}

string translate_exp(Node *exp, string varName);

string translate_cond(Node *exp, string labelTrue, string labelFalse);

string calculateMath(Node *exp, string varName, string operation) {
    int tempNumKeep1 = tempNum;
    tempNum++;
    int tempNumKeep2 = tempNum;
    tempNum++;
    string result1 = translate_exp(&exp->subNode[0], "t" + to_string(tempNumKeep1));
    string result2 = translate_exp(&exp->subNode[2], "t" + to_string(tempNumKeep2));
    tempNum = tempNumKeep1;
    string output;
    if (result1.empty()) {
        result1 = exp->subNode[0].value;
    } else {
        output += result1;
        result1 = "t" + to_string(tempNumKeep1);
    }
    if (result2.empty()) {
        result2 = exp->subNode[2].value;
    } else {
        output += result2;
        result2 = "t" + to_string(tempNumKeep2);
    }
    string operateSym;
    if (operation == "PLUS") { operateSym = "+"; }
    else if (operation == "MINUS") { operateSym = "-"; }
    else if (operation == "MUL") { operateSym = "*"; }
    else if (operation == "DIV") { operateSym = "/"; }
    output += varName + " := " + result1 + " " + operateSym + " " + result2 + "\n";
    return output;
}

string getLogicOp(string operationName) {
    string operation;
    if (operationName == "LT") {
        operation = "<";
    } else if (operationName == "LE") {
        operation = "<=";
    } else if (operationName == "GT") {
        operation = ">";
    } else if (operationName == "GE") {
        operation = ">=";
    } else if (operationName == "NE") {
        operation = "==";
    } else if (operationName == "EQ") {
        operation = "!=";
    }
    return operation;
}

string calculateLogic(Node *exp, string varName, string operation) {
    string label_1 = new_label();
    labelNum++;
    string label_2 = new_label();
    labelNum++;
    string output = varName + " := #0"+"\n";
    output += translate_cond(exp,label_1,label_2);
    output += "LABEL "+label_1+"\n"+varName+" :=#1"+"\nLABEL "+label_2+"\n";
}

string translate_cond(Node *exp, string labelTrue, string labelFalse) {
    int size = exp->subNode.size();
    switch (size) {
        case 2: {
            return translate_cond(&exp->subNode[1], labelFalse, labelTrue);
        }
        case 3: {
            if (exp->subNode[1].type == "AND") {
                string label = new_label();
                labelNum++;
                string result1 = translate_cond(&exp->subNode[0], label, labelFalse);
                string result2 = translate_cond(&exp->subNode[2], labelTrue, labelFalse);
                return result1 + "LABEL " + label + ":\n" + result2;
            } else if (exp->subNode[1].type == "OR") {
                string label = new_label();
                labelNum++;
                string result1 = translate_cond(&exp->subNode[0], labelTrue, label);
                string result2 = translate_cond(&exp->subNode[2], labelTrue, labelFalse);
                return result1 + "LABEL " + label + ":\n" + result2;
            } else if (exp->subNode[1].type == "LT" || exp->subNode[1].type == "LE" ||
                       exp->subNode[1].type == "GT" || exp->subNode[1].type == "GE" ||
                       exp->subNode[1].type == "NE" || exp->subNode[1].type == "EQ") {
                string op = getLogicOp(exp->subNode[0].type);
                int tempNumKeep1 = tempNum;
                tempNum++;
                int tempNumKeep2 = tempNum;
                tempNum++;
                string result1 = translate_exp(&exp->subNode[0], "t" + to_string(tempNumKeep1));
                string result2 = translate_exp(&exp->subNode[2], "t" + to_string(tempNumKeep2));
                tempNum = tempNumKeep1;
                string output;
                if (result1.empty()) {
                    string value = exp->subNode[0].value;
                    if (value[0] == '#') {
                        if (getConst(value)) {
                            result1 = constSet[value];
                        } else {
                            result1 = "c" + to_string(constNum);
                            output += "c" + to_string(constNum) + " := " + value + "\n";
                            constNum++;
                            constSet[value] = result1;
                        }
                    } else {
                        result1 = value;
                    }
                } else {
                    output += result1;
                    result1 = "t" + to_string(tempNumKeep1);
                }
                if (result2.empty()) {
                    string value = exp->subNode[0].value;
                    if (value[0] == '#') {
                        if (getConst(value)) {
                            result2 = constSet[value];
                        } else {
                            result2 = "c" + to_string(constNum);
                            output += "c" + to_string(constNum) + " := " + value + "\n";
                            constNum++;
                            constSet[value] = result2;
                        }
                    } else {
                        result2 = value;
                    }
                } else {
                    output += result2;
                    result2 = "t" + to_string(tempNumKeep1);
                }
                output += "IF " + result1 + " " + op + " " + result2 + "\n" + "GOTO " + labelFalse + "\n";
                return output;
            } else {
                int tempNumKeep = tempNum;
                tempNum++;
                string result = translate_exp(exp, "t" + to_string(tempNumKeep));
                string output;
                if (result.empty()) {
                    if (result.empty()) {
                        string value = exp->subNode[0].value;
                        if (value[0] == '#') {
                            if (getConst(value)) {
                                result = constSet[value];
                            } else {
                                result = "c" + to_string(constNum);
                                output += "c" + to_string(constNum) + " := " + value + "\n";
                                constNum++;
                                constSet[value] = result;
                            }
                        } else {
                            result = value;
                        }
                    } else {
                        output += result;
                        result = "t" + to_string(tempNumKeep);
                    }
                }
                output += "IF " + result + " != #0 GOTO " + labelTrue + "\n" + "GOTO " + labelFalse + "\n";
                return output;
            }
        }
        default: {
            int tempNumKeep = tempNum;
            tempNum++;
            string result = translate_exp(exp, "t" + to_string(tempNumKeep));
            string output;
            if (result.empty()) {
                if (result.empty()) {
                    string value = exp->subNode[0].value;
                    if (value[0] == '#') {
                        if (getConst(value)) {
                            result = constSet[value];
                        } else {
                            result = "c" + to_string(constNum);
                            output += "c" + to_string(constNum) + " := " + value + "\n";
                            constNum++;
                            constSet[value] = result;
                        }
                    } else {
                        result = value;
                    }
                } else {
                    output += result;
                    result = "t" + to_string(tempNumKeep);
                }
            }
            output += "IF " + result + " != #0 GOTO " + labelTrue + "\n" + "GOTO " + labelFalse + "\n";
            return output;
        }
    }
}

string translate_exp(Node *exp, string varName) {
    int size = exp->subNode.size();
    switch (size) {
        case 1: {
            if (exp->subNode[0].type == "ID") {
                string name = exp->subNode[0].show.substr(4);
                exp->value = varSet[name];
            } else if (exp->subNode[0].type == "INT") {
                exp->value = "#" + exp->subNode[0].show.substr(5);
            }
            return "";
        }
        case 2: {
            if (exp->subNode[0].type == "MINUS") {
                int tempNumKeep = tempNum;
                tempNum++;
                string result = translate_exp(&exp->subNode[1], "t" + to_string(tempNumKeep));
                tempNum = tempNumKeep;
                if (result == "") {
                    return varName + " := #0 - " + exp->subNode[1].value + "\n";
                } else {
                    return varName + " := #0 - t" + to_string(tempNumKeep) + "\n";
                }
            } else if (exp->subNode[0].type == "NOT") {
                return calculateLogic(exp, varName,exp->subNode[0].type);
            } else {
                return "ERROR\n";
            }
        }
        case 3: {
            if (exp->subNode[1].type == "PLUS" || exp->subNode[1].type == "MINUS" ||
                exp->subNode[1].type == "MUL" || exp->subNode[1].type == "DIV") {
                return calculateMath(exp, varName, exp->subNode[1].type);
            } else if (exp->subNode[1].type == "AND" || exp->subNode[1].type == "OR" ||
                       exp->subNode[1].type == "LT" || exp->subNode[1].type == "LE" ||
                       exp->subNode[1].type == "GT" || exp->subNode[1].type == "GE" ||
                       exp->subNode[1].type == "NE" || exp->subNode[1].type == "EQ") {
                return calculateLogic(exp, varName, exp->subNode[1].type);
            } else if (exp->subNode[1].type == "ASSIGN") {
                string name = exp->subNode[0].subNode[0].show.substr(4);
                string symbol;
                symbol = varSet[name];
                int tempNumKeep = tempNum;
                tempNum++;
                string result = translate_exp(&exp->subNode[2], "t" + to_string(tempNumKeep));
                tempNum = tempNumKeep;
                string output;
                if (result.empty()) {
                    output += symbol + " := " + exp->subNode[2].value + "\n";
                } else {
                    output += result;
                    output += symbol + " := " + "t" + to_string(tempNumKeep) + "\n";
                }
                output += varName + " := " + symbol + "\n";
                return output;
            } else if (exp->subNode[0].type == "LP" && exp->subNode[2].type == "RP") {
                return translate_exp(&exp->subNode[1], varName);
            } else {
                return "test\n";
            }
        }
        case 4: {
            if (exp->subNode[0].type == "ID" && exp->subNode[1].type == "LP" &&
                exp->subNode[2].type == "Args" && exp->subNode[3].type == "RP") {
                return "test\n";
            }
        }
        default: {
            return "";
        }
    }
}

string translate_stmt(Node *stmt) {
    int size = stmt->subNode.size();
    switch (size) {
        case 1: {
            return "test\n";
        }
        case 2: {
            int tempNumKeep = tempNum;
            tempNum++;
            string result = translate_exp(&stmt->subNode[0], "t" + to_string(tempNumKeep));
            tempNum = tempNumKeep;
            //单独一个变量作为一个stmt可以不管
            return result;
        }
        case 3: {
            int tempNumKeep = tempNum;
            tempNum++;
            string result = translate_exp(&stmt->subNode[1], "t" + to_string(tempNumKeep));
            tempNum = tempNumKeep;
            string output;
            if (result.empty()) {
                output = "RETURN " + stmt->subNode[1].value + "\n";
            } else {
                output += result;
                output += "RETURN t" + to_string(tempNumKeep);
            }
        }
        case 5: {//If or While
            if(stmt->subNode[0].type == "IF"){
                string label_1 = new_label();
                string label_2 = new_label();
                string code_1 = translate_cond(&stmt->subNode[2],label_1, label_2) + "LABEL "+label_1+"\n";
                string code_2 = translate_stmt(&stmt->subNode[4])+"LABEL "+label_2+"\n";
                return code_1+code_2;
            }else{
                string label_1 = new_label();
                string label_2 = new_label();
                string label_3 = new_label();
                string code_1 = "LABEL "+label_1+"\n"+translate_cond(&stmt->subNode[2],label_2,label_3);
                string code_2 = "LABEL "+label_2+"\n"+translate_stmt(&stmt->subNode[4])+"GOTO "+label_1+"\n";
                return code_1+code_2+"LABEL "+label_3;
            }
        }
        case 7: {
            string label_1 = new_label();
            string label_2 = new_label();
            string label_3 = new_label();
            string code_1 = translate_cond(&stmt->subNode[2],label_1, label_2) + "LABEL "+label_1+"\n";
            string code_2 = translate_stmt(&stmt->subNode[4])+"GOTO "+label_3+"\nLABEL "+label_2+"\n";
            string code_3 = translate_stmt(&stmt->subNode[6])+"LABEL "+label_3+"\n";
            return code_1+code_2+code_3;
        }
        default: {
            return "ERROR\n";
        }
    }
}

string decVar(Node dec) {
    string name = dec.subNode[0].subNode[0].show.substr(4);
    varSet[name] = "v" + to_string(varNum);
    varNum++;
    if (dec.subNode.size() > 1) {
        string symbol;
        symbol = varSet[name];
        int tempNumKeep = tempNum;
        tempNum++;
        string result = translate_exp(&dec.subNode[2], "t" + to_string(tempNumKeep));
        tempNum = tempNumKeep;
        string output;
        if (result.empty()) {
            output += symbol + " := " + dec.subNode[2].value + "\n";
        } else {
            output += result;
            output += symbol + " := " + "t" + to_string(tempNumKeep) + "\n";
        }
        return output;
    } else {
        return "";
    }
}

void traversalNode(Node node) {
    int size = node.subNode.size();
    for (int i = 0; i < size; i++) {
        if (node.subNode[i].type == "Stmt") {
            cout << translate_stmt(&node.subNode[i]);
        } else if (node.subNode[i].type == "Dec") {
            cout << decVar(node.subNode[i]);
        } else {
            traversalNode(node.subNode[i]);
        }
    }
}

void generateIR(Node program) {
    traversalNode(program);
}