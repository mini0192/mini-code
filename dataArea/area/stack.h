#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
protected:
    int maxSize;
    T* elements;
    int topIndex;
    int bottomIndex;

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
        bottomIndex(0),
        elements(new T[maxSize])
    {}

    ~Stack() {
        delete[] elements;
    }

    virtual T* findByName(std::string name) = 0;
    virtual void push(T data) = 0;
    virtual T pop() = 0;

    T findByIndex(int index) {
        return elements[index];
    }

    bool isEmpty() {
        return topIndex <= 0;
    }

    int size() {
        return topIndex;
    }
};

#endif