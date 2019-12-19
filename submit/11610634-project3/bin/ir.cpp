#include "node.hpp"
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>

int tempNum = 0;
int constNum = 0;
int labelNum = 0;
int varNum = 0;

map<string, string> varSet;
map<string, string> constSet;

string translate_exp(Node *exp, string varName);

string decVar(Node dec);

string translate_cond(Node *exp, string labelTrue, string labelFalse);

string translate_args(Node *args, vector<string> *argList);

string new_label() {
    string l = "l" + to_string(labelNum);
    labelNum++;
    return l;
}

string new_temp() {
    string t = "t" + to_string(tempNum);
    tempNum++;
    return t;
}

bool getConst(string value) {
    map<string, string>::iterator it = constSet.find(value);
    if (it != constSet.end()) {
        return true;
    } else {
        return false;
    }
}

vector<string> split(const string &str, const string &pattern) {
    vector<string> res;
    if (str == "")
        return res;
    //在字符串末尾也加入分隔符，方便截取最后一段
    string strs = str + pattern;
    size_t pos = strs.find(pattern);
    while (pos != string::npos) {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos + pattern.size(), strs.size());
        pos = strs.find(pattern);
    }
    return res;
}

string trim(string s) {
    if (s.empty()) {
        return s;
    }
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

int calculate(vector<string> elements, string value) {
    int res = 0, num = 0;
    char op = '+';
    stack<int> st;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i][0] == 't') {
            elements[i] = value;
        }
        if (elements[i][0] == '#') {
            num = stoi(elements[i].substr(1));
        }
        if ((!elements[i].empty() && elements[i][0] < '0') || i == elements.size() - 1) {
            if (op == '+') st.push(num);
            if (op == '-') st.push(-num);
            if (op == '*' || op == '/') {
                int tmp = (op == '*') ? st.top() * num : st.top() / num;
                st.pop();
                st.push(tmp);
            }
            op = elements[i][0];
            num = 0;
        }
    }
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    return res;
}

string calculateMath(Node *exp, string varName, string operation) {
    string t1 = new_temp();
    string t2 = new_temp();
    string result1 = translate_exp(&exp->subNode[0], t1);
    string result2 = translate_exp(&exp->subNode[2], t2);

    string output;
    if (result1.empty()) {
        result1 = exp->subNode[0].value;
    } else {
        output += result1;
        result1 = t1;
    }
    if (result2.empty()) {
        result2 = exp->subNode[2].value;
    } else {
        output += result2;
        result2 = t2;
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
        operation = "!=";
    } else if (operationName == "EQ") {
        operation = "==";
    }
    return operation;
}

string traversalNode(Node *node);

string calculateLogic(Node *exp, string varName, string operation) {
    string label_1 = new_label();
    labelNum++;
    string label_2 = new_label();
    labelNum++;
    string output = varName + " := #0" + "\n";
    output += translate_cond(exp, label_1, label_2);
    output += "LABEL " + label_1 + " :\n" + varName + " :=#1" + "\nLABEL " + label_2 + " :\n";
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
                return result1 + "LABEL " + label + " :\n" + result2;
            } else if (exp->subNode[1].type == "OR") {
                string label = new_label();
                labelNum++;
                string result1 = translate_cond(&exp->subNode[0], labelTrue, label);
                string result2 = translate_cond(&exp->subNode[2], labelTrue, labelFalse);
                return result1 + "LABEL " + label + " :\n" + result2;
            } else if (exp->subNode[1].type == "LT" || exp->subNode[1].type == "LE" ||
                       exp->subNode[1].type == "GT" || exp->subNode[1].type == "GE" ||
                       exp->subNode[1].type == "NE" || exp->subNode[1].type == "EQ") {
                string op = getLogicOp(exp->subNode[1].type);
                string t1 = new_temp();
                string t2 = new_temp();
                string result1 = translate_exp(&exp->subNode[0], t1);
                string result2 = translate_exp(&exp->subNode[2], t2);
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
//                            constSet[value] = result1;
                        }
                    } else {
                        result1 = value;
                    }
                } else {
                    output += result1;
                    result1 = t1;
                }
                if (result2.empty()) {
                    string value = exp->subNode[2].value;
                    if (value[0] == '#') {
                        if (getConst(value)) {
                            result2 = constSet[value];
                        } else {
                            result2 = "c" + to_string(constNum);
                            output += "c" + to_string(constNum) + " := " + value + "\n";
                            constNum++;
//                            constSet[value] = result2;
                        }
                    } else {
                        result2 = value;
                    }
                } else {
                    output += result2;
                    result2 = t2;
                }
                output += "IF " + result1 + " " + op + " " + result2 + " GOTO " + labelTrue + "\n" + "GOTO " +
                          labelFalse + "\n";
                return output;
            } else {
                string t = new_temp();
                string result = translate_exp(exp, t);
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
//                                constSet[value] = result;
                            }
                        } else {
                            result = value;
                        }
                    } else {
                        output += result;
                        result = t;
                    }
                }
                output += "IF " + result + " != #0 GOTO " + labelTrue + "\n" + "GOTO " + labelFalse + "\n";
                return output;
            }
        }
        default: {
            string t = new_temp();
            string result = translate_exp(exp, t);
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
//                            constSet[value] = result;
                        }
                    } else {
                        result = value;
                    }
                } else {
                    output += result;
                    result = t;
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
                string t = new_temp();
                string result = translate_exp(&exp->subNode[1], t);

                if (result == "") {
                    return varName + " := #0 - " + exp->subNode[1].value + "\n";
                } else {
                    return varName + " := #0 - " + t + "\n";
                }
            } else if (exp->subNode[0].type == "NOT") {
                return calculateLogic(exp, varName, exp->subNode[0].type);
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
                string t = new_temp();
                string result = translate_exp(&exp->subNode[2], t);

                string output;
                if (result.empty()) {
                    output += symbol + " := " + exp->subNode[2].value + "\n";
                } else {
                    output += result;
                    output += symbol + " := " + t + "\n";
                }
                output += varName + " := " + symbol + "\n";
                return output;
            } else if (exp->subNode[0].type == "LP" && exp->subNode[2].type == "RP") {
                return translate_exp(&exp->subNode[1], varName);
            } else if (exp->subNode[0].type == "ID" && exp->subNode[1].type == "LP") {
                string name = exp->subNode[0].show.substr(4);
                if (name == "read") {
                    return "READ " + varName + "\n";
                } else {
                    return varName + " := CALL " + name + "\n";
                }
            } else {
                return "ERROR\n";
            }
        }
        case 4: {
            if (exp->subNode[0].type == "ID" && exp->subNode[1].type == "LP" &&
                exp->subNode[2].type == "Args" && exp->subNode[3].type == "RP") {
                string name = exp->subNode[0].show.substr(4);
                if (name == "write") {
                    string t = new_temp();
                    string result = translate_exp(&exp->subNode[2].subNode[0], t);
                    string output;
                    if (result.empty()) {
                        return "WRITE " + exp->subNode[2].subNode[0].value + "\n";
                    } else {
                        return result + "WRITE " + t + "\n";
                    }
                } else {
                    vector<string> argList;
                    string code_1 = translate_args(&exp->subNode[2], &argList);
                    string code_2;
                    for (int i = argList.size() - 1; i >= 0; i--) {
                        code_2 += "ARG " + argList[i] + "\n";
                    }
                    return code_1 + code_2 + varName + " := CALL " + name + "\n";
                }
            }
        }
        default: {
            return "";
        }
    }
}

string translate_args(Node *args, vector<string> *argList) {
    int size = args->subNode.size();
    switch (size) {
        case 1: {
            string t = new_temp();
            string result = translate_exp(&args->subNode[0], t);
            string output;
            if (result.empty()) {
                argList->push_back(args->subNode[0].value);
                return "";
            } else {
                argList->push_back(t);
                return result;
            }
        }
        case 3: {
            string t = new_temp();
            string result = translate_exp(&args->subNode[0], t);
            string output;
            if (result.empty()) {
                argList->push_back(args->subNode[0].value);
                return translate_args(&args->subNode[2], argList);
            } else {
                argList->push_back(t);
                return result + translate_args(&args->subNode[2], argList);
            }
        }
    }
}

string translate_stmt(Node *stmt) {
    int size = stmt->subNode.size();
    switch (size) {
        case 1: {
            return traversalNode(&stmt->subNode[0]);
        }
        case 2: {
            string t = new_temp();
            string result = translate_exp(&stmt->subNode[0], t);

            //单独一个变量作为一个stmt可以不管
            return result;
        }
        case 3: {
            string t = new_temp();
            string result = translate_exp(&stmt->subNode[1], t);

            string output;
            if (result.empty()) {
                output = "RETURN " + stmt->subNode[1].value + "\n";
            } else {
                output += result;
                output += "RETURN " + t + "\n";
            }
            return output;
        }
        case 5: {//If or While
            if (stmt->subNode[0].type == "IF") {
                string label_1 = new_label();
                string label_2 = new_label();
                string code_1 = translate_cond(&stmt->subNode[2], label_1, label_2) + "LABEL " + label_1 + " :\n";
                string code_2 = translate_stmt(&stmt->subNode[4]) + "LABEL " + label_2 + " :\n";
                return code_1 + code_2;
            } else {
                string label_1 = new_label();
                string label_2 = new_label();
                string label_3 = new_label();
                string code_1 = "LABEL " + label_1 + " :\n" + translate_cond(&stmt->subNode[2], label_2, label_3);
                string code_2 =
                        "LABEL " + label_2 + " :\n" + translate_stmt(&stmt->subNode[4]) + "GOTO " + label_1 + "\n";
                return code_1 + code_2 + "LABEL " + label_3 + " :\n";
            }
        }
        case 7: {
            string label_1 = new_label();
            string label_2 = new_label();
            string label_3 = new_label();
            string code_1 = translate_cond(&stmt->subNode[2], label_1, label_2) + "LABEL " + label_1 + " :\n";
            string code_2 = translate_stmt(&stmt->subNode[4]) + "GOTO " + label_3 + "\nLABEL " + label_2 + " :\n";
            string code_3 = translate_stmt(&stmt->subNode[6]) + "LABEL " + label_3 + " :\n";
            return code_1 + code_2 + code_3;
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
        string t = new_temp();
        string result = translate_exp(&dec.subNode[2], t);

        string output;
        if (result.empty()) {
            output += symbol + " := " + dec.subNode[2].value + "\n";
        } else {
            output += result;
            output += symbol + " := " + t + "\n";
        }
        return output;
    } else {
        return "";
    }
}

string traversalNode(Node *node) {
    int size = node->subNode.size();
    string output;
    for (int i = 0; i < size; i++) {
        if (node->subNode[i].type == "Stmt") {
            output += translate_stmt(&node->subNode[i]);
        } else if (node->subNode[i].type == "Dec") {
            output += decVar(node->subNode[i]);
        } else {
            output += traversalNode(&node->subNode[i]);
        }
    }
    return output;
}

string translate_varList(Node *varList) {
    int size = varList->subNode.size();
    string output;
    switch (size) {
        case 1: {
            Node varDec = varList->subNode[0].subNode[1];
            string name = varDec.subNode[0].show.substr(4);
            string symbol = "v" + to_string(varNum);
            varNum++;
            varSet[name] = symbol;
            output += "PARAM " + symbol + "\n";
            return output;
        }
        default: {
            Node varDec = varList->subNode[0].subNode[1];
            string name = varDec.subNode[0].show.substr(4);
            string symbol = "v" + to_string(varNum);
            varNum++;
            varSet[name] = symbol;
            output += "PARAM " + symbol + "\n";
            output += translate_varList(&varList->subNode[2]);
            return output;
        }
    }
}

string translate_extDef(Node *extDef) {
    if (extDef->subNode[1].type == "FunDec") {
        string name = extDef->subNode[1].subNode[0].show.substr(4);
        string output = "FUNCTION " + name + " :\n";
        if (extDef->subNode[1].subNode.size() > 3) {
            output += translate_varList(&extDef->subNode[1].subNode[2]);
        }
        output += traversalNode(&extDef->subNode[2]);
        return output;
    } else {
        return "";
    }
}

string translate_program(Node program) {
    int size = program.subNode.size();
    string output;
    for (int i = 0; i < size; i++) {
        if (program.subNode[i].type == "ExtDef") {
            output += translate_extDef(&program.subNode[i]);
        } else {
            output += translate_program(program.subNode[i]);
        }
    }
    return output;
}

//删除从未使用过或仅用于传递值的temp
vector<string> delete_type1(vector<string> irs) {
    for (int i = 0; i < irs.size(); i++) {
        vector<string> exps = split(irs[i], ":=");
        if (exps.size() > 1) {
            string left = trim(exps[0]);
            string right = trim(exps[1]);
            if ((left[0] == 't'||left[0] == 'v')) {
                bool used = false;
                vector<int> changedPos;
                int temp = (left[0] == 'v')?0:(i+1);
                for (int j = temp; j < irs.size(); j++) {
                    vector<string> checkedExps = split(irs[j], ":=");
                    if (checkedExps.size() > 1) {
                        string checkedLeft = trim(checkedExps[0]);
                        string checkedRight = trim(checkedExps[1]);
                        if (checkedLeft == left && left[0] == 't') {//临时变量被重用
                            break;
                        } else {
                            if (checkedRight.find(left) != string::npos) {//含有变量
                                if (checkedRight == left) {//直接使用了
                                    changedPos.push_back(j);
                                } else {
                                    used = true;
                                }
                            }
                        }
                    } else if (irs[j].find(left) != string::npos
                               && irs[j].substr(0, 8) != "FUNCTION") {
                        used = true;
                        break;
                    }
                }
                if (!used) {
                    if (changedPos.size() == 1) {
                        int j = changedPos[0];
                        string checkedLeft = trim(split(irs[j], ":=")[0]);
                        irs[i] = checkedLeft + " := " + right;
                        vector<string>::iterator it = irs.begin();
                        for (int k = 0; k < j; k++) it++;
                        it = irs.erase(it);
                    } else if(right.substr(0,4)!="CALL") {
                        vector<string>::iterator it = irs.begin();
                        for (int j = 0; j < i; j++) it++;
                        it = irs.erase(it);
                    }
                }
            }
        }
    }
    return irs;
}

//删除可以通过关联值直接进行定义而不需要计算的temp
vector<string> delete_type2(vector<string> irs) {
    for (int i = 0; i < irs.size(); i++) {
        vector<string> exps = split(irs[i], ":=");
        if (exps.size() > 1) {
            string left = trim(exps[0]);
            string right = trim(exps[1]);
            if ((left[0] == 't') && right[0] == '#' && split(right, " ").size() <= 1) {
                bool used = false;
                vector<int> changedPos;
                for (int j = i + 1; j < irs.size(); j++) {
                    vector<string> checkedExps = split(irs[j], ":=");
                    if (checkedExps.size() > 1) {
                        string checkedLeft = trim(checkedExps[0]);
                        string checkedRight = trim(checkedExps[1]);
                        if (checkedRight.find(left) != string::npos) {//含有变量
                            vector<string> elements = split(checkedRight, " ");
                            bool pureNum = true;
                            for (auto &element : elements) {
                                if (!(element[0] == '#' || element == "+" || element == "-" || element == "*" ||
                                      element == "/" || element == left)) {
                                    pureNum = false;
                                    break;
                                }
                            }
                            if (pureNum) {//直接使用了
                                changedPos.push_back(j);
                            } else {
                                used = true;
                            }
                        }
                        if (checkedLeft == left) {//变量被重用
                            break;
                        }
                    } else if (irs[j].find(left) != string::npos
                               && irs[j].substr(0, 4) != "CALL"
                               && irs[j].substr(0, 8) != "FUNCTION") {
                        used = true;
                        break;
                    }
                }

                if (changedPos.size() > 0) {
                    for (int j:changedPos) {
                        j = changedPos[0];
                        string value = trim(split(irs[i], ":=")[1]);
                        string checkedRight = trim(split(irs[j], ":=")[1]);
                        int result = calculate(split(checkedRight, " "), value);
                        string checkedLeft = trim(split(irs[j], ":=")[0]);
                        irs[j] = checkedLeft + " := #" + to_string(result);
                    }
                }
            }
        }
    }
    return irs;
}

//删除可以直接计算得出的值
vector<string> delete_type3(vector<string> irs) {
    int size = irs.size();
    for (int i = 0; i < size; i++) {
        vector<string> exps = split(irs[i], ":=");
        if (exps.size() > 1) {
            string checkedLeft = trim(exps[0]);
            string checkedRight = trim(exps[1]);
            vector<string> elements = split(checkedRight, " ");
            bool pureNum = true;
            for (auto &element : elements) {
                if (!(element[0] == '#' || element == "+" || element == "-" || element == "*" ||
                      element == "/")) {
                    pureNum = false;
                    break;
                }
            }
            if (pureNum) {//是一个完整的计算式
                int result = calculate(elements, "");
                irs[i] = checkedLeft + " := #" + to_string(result);
            }
        }
    }
    return irs;
}

vector<string> delete_type4(vector<string> irs) {
    for (int i = 0; i < irs.size() - 1; i++) {
        vector<string> exps = split(irs[i], ":=");
        if (exps.size() > 1) {
            string left = trim(exps[0]);
            string right = trim(exps[1]);
            vector<string> elements = split(right, " ");
            bool pureNum = true;
            int num = 0;
            for (auto &element : elements) {
                if (!(element[0] == '#' || element == "+" || element == "-" || element == "*" ||
                      element == "/" || element == left)) {
                    pureNum = false;
                    break;
                }
                if (element == left) {
                    num++;
                }
            }
            if (pureNum && (num < 2)) {
                vector<string> expsChecked = split(irs[i + 1], ":=");
                if (expsChecked.size() > 1) {
                    string leftChecked = trim(expsChecked[0]);
                    string rightChecked = trim(expsChecked[1]);
                    if (leftChecked == left) {
                        vector<string> elementsChecked = split(rightChecked, " ");
                        bool pureNumChecked = true;
                        int numChecked = 0;
                        for (auto &element : elementsChecked) {
                            if (!(element[0] == '#' || element == "+" || element == "-" || element == "*" ||
                                  element == "/" || element == left)) {
                                pureNumChecked = false;
                                break;
                            }
                            if (element == left) {
                                numChecked++;
                            }
                        }
                        if (pureNumChecked && numChecked < 2) {
                            string op = "Null";
                            bool canBeMerged = true;
                            for (int j = 0; j < elements.size(); j++) {
                                if (elements[j] == left) {
                                    if (j != 0) {
                                        if (elements[j - 1] == "*" || elements[j - 1] == "/") {
                                            canBeMerged = false;
                                            break;
                                        }
                                    }
                                    if (j != elements.size() - 1) {
                                        if (elements[j + 1] == "*" || elements[j + 1] == "/") {
                                            canBeMerged = false;
                                            break;
                                        }
                                    }
                                    if (j == 0) {
                                        op = "+";
                                        elements.erase(elements.begin());
                                        break;
                                    } else {
                                        op = elements[j - 1];
                                        auto it = elements.begin();
                                        for (int k = 0; k < j - 1; k++) it++;
                                        auto itTemp = it++;
                                        elements.erase(itTemp);
                                        elements.erase(it);
                                        break;
                                    }
                                }
                            }
                            int result = calculate(elements, "");
                            if (!canBeMerged) {
                                continue;
                            }
                            string opc = "Null";
                            canBeMerged = true;
                            for (int j = 0; j < elementsChecked.size(); j++) {
                                if (elementsChecked[j] == left) {
                                    if (j != 0) {
                                        if (elementsChecked[j - 1] == "*" || elementsChecked[j - 1] == "/") {
                                            canBeMerged = false;
                                            break;
                                        }
                                    }
                                    if (j != elementsChecked.size() - 1) {
                                        if (elementsChecked[j + 1] == "*" || elementsChecked[j + 1] == "/") {
                                            canBeMerged = false;
                                            break;
                                        }
                                    }
                                    if (j == 0) {
                                        opc = "+";
                                        elementsChecked.erase(elementsChecked.begin());
                                        break;
                                    } else {
                                        opc = elementsChecked[j - 1];
                                        auto it = elementsChecked.begin();
                                        for (int k = 0; k < j - 1; k++) it++;
                                        auto itTemp = it++;
                                        elementsChecked.erase(itTemp);
                                        elementsChecked.erase(it);
                                        break;
                                    }
                                }
                            }
                            if (!canBeMerged) {
                                continue;
                            }
                            string output = left + " := ";
                            if (opc != "+" && opc != "-") {
                                output += "#" + to_string(calculate(elementsChecked, ""));
                            } else {
                                if (opc == "+") {
                                    result += calculate(elementsChecked, "");
                                } else {
                                    result -= calculate(elementsChecked, "");
                                }
                                if (op != "+" && op != "-") {
                                    output += "#" + to_string(result);
                                } else {
                                    if (opc == op) {
                                        output += left + " + #" + to_string(result);
                                    } else {
                                        output += "#" + to_string(result) + " - " + left;
                                    }
                                }
                            }
                            irs[i + 1] = output;
                            auto it = irs.begin();
                            for (int j = 0; j < i; j++) it++;
                            irs.erase(it);
                            i--;
                        }
                    }
                }
            }
        }
    }
    return irs;
}

vector<string> add_all_const(vector<string> irs){
    for (int i = 0; i < irs.size(); i++) {
        if(irs[i].substr(0,8) == "FUNCTION"){
            for(auto & it : constSet){
                irs.insert(irs.begin()+i+1,it.second+" := "+it.first);
            }
        }
    }
    return irs;
}

void generateIR(Node program) {
    string output = translate_program(program);
//    cout << output;
    vector<string> irs = split(output, "\n");
//    irs = add_all_const(irs);
    irs = delete_type1(irs);
    irs = delete_type3(irs);
    irs = delete_type1(irs);
    irs = delete_type4(irs);
    irs = delete_type1(irs);
    for (const auto &ir : irs) {
        cout << ir << endl;
    }
}