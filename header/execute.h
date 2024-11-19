#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "token.h"
#include "error.h"

#pragma once

constexpr int MAX_VAR_NAME = 50;
constexpr int MAX_VARS = 10;

class Var {
public:
    std::string name;
    int value;

    Var(const std::string& name, int value) : name(name), value(value) {}
};

std::vector<Var> vars;  // 가변 크기의 변수 목록
int varCount = 0;

bool isData = false;
bool isStr = false;
int data1 = 0;
int data2 = 0;
std::string str;  // 문자열을 처리하기 위한 변수

/**
 * 이름으로 변수 찾기
 */
int getVarIndex(const std::string& name) {
    for (int i = 0; i < varCount; i++) {
        if (vars[i].name == name) {
            return i;
        }
    }
    return -1;
}

void execute(std::vector<Token> token);

void strFunc(Token* token) {
    if (token->value == "out") {
        execute(++token);
        if (isStr) {
            std::cout << str;
            isStr = false;
            return;
        }
        if (isData) {
            std::cout << data1;
            isData = false;
            return;
        }
    }

    if (token->value == "in") {
        std::cin >> data1;
        isData = true;
        return;
    }

    if (token->value == "next") {
        std::cout << std::endl;
        return;
    }

    if (token->value == "var") {
        std::string name = (++token)->value;
        if (getVarIndex(name) != -1) conflictVariable(name);
        execute(++token);

        vars.push_back(Var(name, isData ? data1 : 0));
        isData = false;
        varCount++;
        return;
    }

    if (token->value == "set") {
        std::string name = (++token)->value;
        int index = getVarIndex(name);
        if (index == -1) notFoundVarError(name);

        execute(++token);
        if (isData) {
            vars[index].value = data1;
            isData = false;
        } else {
            syntaxError();
        }
        return;
    }

    int index = getVarIndex(token->value);
    if (index != -1) {
        if (!isData) {
            data1 = vars[index].value;
            isData = true;
            execute(++token);
            return;
        }

        if (isData) {
            data2 = vars[index].value;
            return;
        }
    }
}

void signFunc(std::vector<Token> token) {
    if (isData && token->value == "+") {
        execute(++token);
        data1 += data2;
        return;
    }

    if (isData && token->value == "-") {
        execute(++token);
        data1 -= data2;
        return;
    }

    if (isData && token->value == "*") {
        execute(++token);
        data1 *= data2;
        return;
    }

    if (isData && token->value == "/") {
        execute(++token);
        if (data2 != 0) {
            data1 /= data2;
        } else {
            std::cerr << "Error: Division by zero!" << std::endl;
            exit(1);
        }
        return;
    }
}

void strdataFunc(Token* token) {
    str = token->value;
    isStr = true;
    return;
}

void numberFunc(Token* token) {
    if (!isData) {
        data1 = std::stoi(token->value);  // std::stoi로 문자열을 정수로 변환
        isData = true;
        execute(++token);
        return;
    }

    if (isData) {
        data2 = std::stoi(token->value);
        return;
    }
}

void execute(Token* token) {
    if (token->type == TOK_VAR) {
        strFunc(token);
        return;
    }

    if (token->type == TOK_SIGN) {
        signFunc(token);
        return;
    }

    if (token->type == TOK_STRDATA) {
        strdataFunc(token);
        return;
    }

    if (token->type == TOK_NUMBER) {
        numberFunc(token);
        return;
    }
    return;
}
