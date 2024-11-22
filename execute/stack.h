#include <iostream>
#include <string>

template<typename T>
class Stack {
protected:
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
    Stack() :
        maxSize(10),
        topIndex(0),
        elements(new T[maxSize])
    {}

    ~Stack() {
        delete[] elements;
    }

    void push(T data) {
        if (topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }

    T findByIndex(int index) {
        return elements[index];
    }

    virtual T pop() {
        return elements[--topIndex];
    }

    virtual T* findByName(std::string name) = 0;

    bool isEmpty() {
        return topIndex <= 0;
    }

    int size() {
        return topIndex;
    }
};