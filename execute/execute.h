#include <iostream>
#include <memory>
#include <stack>

#include "../header/token.h"
#include "variableAreaImpl.h"
#include "dataAreaImpl.h"

#pragma once

class Execute {
private:
    std::string STR_REG;
    bool STR_FLAG;

    int NUM_REG;
    bool NUM_FLAG;

    int ALU_REG;

    VariableArea<Variable> variable;
    DataArea data;

public:
    void execute(std::shared_ptr<Token> token) {
        if (token->getType() == TOK_OUT) {
            execute(token->getNextToken());
            if(STR_FLAG) {
                std::cout << STR_REG;
                return;
            }
            if(NUM_FLAG) {
                std::cout << NUM_REG;
                return;
            }
        }
        if (token->getType() == TOK_STRDATA) {
            STR_REG = token->getValue();
        }
        return;
    }
};
