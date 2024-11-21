#include <iostream>
#include <vector>
#include <memory>
#include "../header/token.h"

#pragma once

#include <iostream>
#include <vector>
#include <memory>

class Token;  // 전방 선언

class FunctionData {
private:
    std::string name;
    std::vector<std::shared_ptr<Token>> lines;

public:
    FunctionData() : name("") {}

    void clear() {
        lines.clear();
        name.clear();
    }

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


class FunctionArea : public Stack<FunctionData> {
public:
    using Stack::Stack;
    using Stack::push;
    using Stack::pop;
    using Stack::isEmpty;
    using Stack::size;

    FunctionArea() : Stack() {}
    ~FunctionArea() {}

    FunctionData* findByName(std::string name) override {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
        }
        return nullptr;
    }
};