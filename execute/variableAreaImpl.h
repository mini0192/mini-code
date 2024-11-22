#include <iostream>
#include "stack.h"
#include "dataAreaImpl.h"

#pragma once

DataArea dataArea;

enum VariableType {
    VAR_NUM,
    VAR_STR,
    VAR_BOOL,
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

    int getDataNum() {
        return dataArea.getNumber(pointer);
    }

    void setDataStr(std::string data) {
        if(VAR_TYPE != VAR_STR) throw SyntaxError("Types do not match. Note: The variable type is not \"str\"");
        pointer = dataArea.pushStr(data);
    }

    void setDataNum(int data) {
        if(VAR_TYPE != VAR_NUM && VAR_TYPE != VAR_BOOL) throw SyntaxError("Types do not match. Note: The variable type is not \"num\" or \"bool\"");
        pointer = dataArea.pushNumber(data);
    }

    VariableType getType() {
        return VAR_TYPE;
    }

    void setType(VariableType type) {
        this->VAR_TYPE = type;
    }
};

class VariableArea : public Stack<Variable> {
public:
    using Stack::Stack;
    using Stack::push;
    using Stack::pop;
    using Stack::isEmpty;
    using Stack::size;

    VariableArea() : Stack() {}
    ~VariableArea() {}

    Variable pop() override {
        return elements[--topIndex];
    }

    Variable* findByName(std::string name) override {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
        }
        return nullptr;
    }
};