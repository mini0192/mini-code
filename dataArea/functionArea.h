#include <iostream>
#include <vector>
#include <memory>

#include "../token/token.h"

#pragma once

class Token;  // 전방 선언

class FunctionData {
private:
    std::string name;
    std::vector<std::shared_ptr<Token>> lines;

public:
    FunctionData() : name("") {}

    void pushLine(std::shared_ptr<Token> line) {
        lines.push_back(line);
    }

    int getLineSize() const {
        return lines.size();
    }

    std::shared_ptr<Token> getLine(int index) const {
        if (index < 0 || index >= lines.size()) {
            throw std::out_of_range("Index out of range");
        }
        return lines[index];
    }

    void setName(const std::string& name) {
        this->name = name;
    }

    std::string getName() const {
        return name;
    }

    bool isWriting() const {
        return !name.empty();
    }
};


class FunctionArea {
protected:
    int maxSize;
    FunctionData* elements;
    int topIndex;

    void resize() {
        maxSize *= 2;
        FunctionData* newElements = new FunctionData[maxSize];
        for (int i = 0; i <= topIndex; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    FunctionArea() :
        maxSize(10),
        topIndex(0),
        elements(new FunctionData[maxSize])
    {}

    ~FunctionArea() {
        delete[] elements;
    }

    void push(FunctionData data) {
        if (topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }

    FunctionData findByIndex(int index) {
        return elements[index];
    }

    FunctionData pop() {
        return elements[--topIndex];
    }

    FunctionData* findByName(std::string name) {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
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