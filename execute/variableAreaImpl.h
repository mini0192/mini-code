#include <iostream>
#include "stack.h"

#pragma once

enum VariableType {
    VAR_NUM,
    VAR_STR,
    VAR_BOOL,
    VAR_NOT,
};

class Variable {
private:
    std::string name;
    VariableType type;
    int pointer;

public:
    Variable() {}

    Variable(std::string name, int pointer, VariableType type) :
        name(name),
        pointer(pointer),
        type(type)
    {}

    std::string getName() {
        return name;
    }

    void setName(std::string name) {
        this->name = name;
    }

    int getPointer() {
        return pointer;
    }

    void setPointer(int pointer) {
        this->pointer = pointer;
    }

    VariableType getType() {
        return type;
    }

    void setType(VariableType type) {
        this->type = type;
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

    Variable* findByName(std::string name) override {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
        }
        return nullptr;
    }
};