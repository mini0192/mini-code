#include <iostream>

#include "dataArea.h"

#pragma once

DataArea dataArea;

enum VariableType {
    VAR_NUM,
    VAR_STR,
    VAR_BOOL,

    FUNCTION_DATA,
    VAR_NOT,
};

class Variable {
private:
    std::string name;
    VariableType VAR_TYPE;
    int pointer;

public:
    Variable() {}
    Variable(std::string name, int pointer, VariableType type) :
        name(name),
        pointer(pointer),
        VAR_TYPE(type)
    {}

    std::string getName() {
        return name;
    }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getDataStr() {
        return dataArea.getStr(pointer);
    }

    void setDataStr(std::string data) {
        if(VAR_TYPE != VAR_STR) throw SyntaxError("Types do not match. Note: The variable type is not \"str\"");
        pointer = dataArea.pushStr(data);
    }

    int getDataNum() {
        return dataArea.getNumber(pointer);
    }

    void setDataNum(int data) {
        if(VAR_TYPE != VAR_NUM && VAR_TYPE != VAR_BOOL) throw SyntaxError("Types do not match. Note: The variable type is not \"num\" or \"bool\"");
        pointer = dataArea.pushNumber(data);
    }

    int getDataFunc() {
        return dataArea.getNumber(pointer);
    }

    void setDataFunc(int data) {
        if(VAR_TYPE != FUNCTION_DATA) throw SyntaxError("Types do not match. Note: The variable type is not \"num\" or \"bool\"");
        pointer = dataArea.pushNumber(data);
    }

    VariableType getType() {
        return VAR_TYPE;
    }

    void setType(VariableType type) {
        this->VAR_TYPE = type;
    }
};

class VariableArea {
private:
    int maxSize;
    Variable* elements;
    int topIndex;
    int bottomIndex;

    void resize() {
        maxSize *= 2;
        Variable* newElements = new Variable[maxSize];
        for (int i = 0; i <= topIndex; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    VariableArea() :
        maxSize(10),
        topIndex(0),
        bottomIndex(0),
        elements(new Variable[maxSize])
    {}

    ~VariableArea() {
        delete[] elements;
    }

    void callFunction() {
        Variable funcData;
        funcData.setType(FUNCTION_DATA);
        funcData.setDataFunc(bottomIndex);
        push(funcData);

        bottomIndex = topIndex;
    }

    void doneFunction() {
        topIndex = bottomIndex - 1;
        Variable funcData = findByIndex(bottomIndex - 1);
        bottomIndex = funcData.getDataFunc();
    }

    void push(Variable data) {
        if (findByName(data.getName())) throw SyntaxError("Duplicate variable name.");
        if (topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }

    Variable findByIndex(int index) {
        return elements[index];
    }

    Variable pop() {
        return elements[--topIndex];
    }

    Variable* findByName(std::string name) {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
        }
        return nullptr;
    }

    bool isEmpty() {
        return topIndex <= 0;
    }

    int size() {
        return topIndex;
    }
};