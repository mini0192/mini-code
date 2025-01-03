#ifndef FUNCTIONAREA_H
#define FUNCTIONAREA_H

#include "stack.h"
#include "../function.h"

class FunctionArea : public Stack<Function>{
private:
    static FunctionArea* instance;
    FunctionArea() : Stack<Function>() {}

public:
    static FunctionArea* getInstance() {
        if(instance == nullptr) {
            instance = new FunctionArea();
        }
        return instance;
    }

    Function findByName(std::string name) {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return this->elements[i];
        }
        return Function();
    }

    void push(Function data) {
        if (topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }
};

FunctionArea* FunctionArea::instance = nullptr;

#endif