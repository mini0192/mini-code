#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include "../token/token.h"

class Token;

class Function {
private:
    std::string name;
    std::vector<std::shared_ptr<Token>> lines;

public:
    Function() : name("") {}

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

#endif