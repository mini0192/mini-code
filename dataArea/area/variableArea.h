#ifndef VARIABLEAREA_H
#define VARIABLEAREA_H

#include "dataArea.h"
#include "stack.h"

#include "../variable.h"

extern DataArea dataArea;

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
    }

    Variable* findByName(std::string name) override {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
        }
        return nullptr;
    }

    void push(Variable data) override {
        if (findByName(data.getName())) throw SyntaxError("Duplicate variable name.");
        if (topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }

    Variable pop() override {
        Variable data = elements[--topIndex];
        return data;
    }
};

VariableArea* VariableArea::instance = nullptr;

#endif