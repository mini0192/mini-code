#ifndef TEMPORARYAREA_H
#define TEMPORARYAREA_H

#include "stack.h"
#include "../variable.h"

class TemporaryArea : public Stack<Variable>{
private:
    static TemporaryArea* instance;
    TemporaryArea() : Stack<Variable>() {}

public:
    static TemporaryArea* getInstance() {
        if(instance == nullptr) {
            instance = new TemporaryArea();
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
        topIndex = bottomIndex;
        Variable funcData = findByIndex(bottomIndex);
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
};

TemporaryArea* TemporaryArea::instance = nullptr;

#endif