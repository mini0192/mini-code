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

template <typename T>
class VariableArea {
private:
    int maxSize;
    T* elements;
    int topIndex;

    void resize() {
        maxSize *= 2;
        T* newElements = new T[maxSize];
        for (int i = 0; i <= topIndex; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    VariableArea() :
        maxSize(10),
        topIndex(-1),
        elements(new T[maxSize])
    {}

    ~VariableArea() {
        delete[] elements;
    }

    void push(T data) {
        if(topIndex >= maxSize) {
            resize();
        }
        elements[++topIndex] = data;
    }

    T pop() {
        return elements[topIndex--];
    }

    T get(int index) {
        return elements[index];
    }

    bool isEmpty() {
        return topIndex < 0;
    }

    int size() {
        return topIndex + 1;
    }
};