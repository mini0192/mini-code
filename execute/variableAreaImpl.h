#include <iostream>

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

class VariableArea {
private:
    int maxSize;
    Variable* elements;
    int topIndex;

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
        elements(new Variable[maxSize])
    {}

    ~VariableArea() {
        delete[] elements;
    }

    void push(Variable data) {
        if(findByName(data.getName())) throw SyntaxError("Variable name is duplicated.");
        if(topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }

    Variable pop() {
        return elements[--topIndex];
    }

    Variable* findByName(std::string name) {
        for(int i = 0; i < topIndex; i++) {
            if(elements[i].getName() == name) return &elements[i];
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