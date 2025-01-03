#ifndef VARIABLEAREA_H
#define VARIABLEAREA_H

#include "stack.h"
#include "../variable.h"

class VariableArea : public Stack<Variable> {
private:
    static VariableArea* instance;
    VariableArea() : Stack<Variable>() {}

public:
    static VariableArea* getInstance() {
        if(instance == nullptr) {
            instance = new VariableArea();
        }
        return instance;
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
        funcData.clear();
    }

    Variable findByName(std::string name) override {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return this->elements[i];
        }
        return Variable();
    }

    void push(Variable data) override {
        Variable checker = findByName(data.getName());
        if (checker.isValid()) throw SyntaxError("Duplicate variable name.");
        if (topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }
};

VariableArea* VariableArea::instance = nullptr;

#endif