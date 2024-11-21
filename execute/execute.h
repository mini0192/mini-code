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

    std::string STRDATA_REG;
    bool STRDATA_FLAG;

    int NUM_REG;
    bool NUM_FLAG;

    int ALU_REG;

    VariableArea variableArea;
    DataArea dataArea;

public:
    Execute() :
        STR_FLAG(false),
        STRDATA_FLAG(false),
        NUM_FLAG(false)
    {}

    void execute(std::shared_ptr<Token> token) {
        if(token->getNextToken()->getType() != TOK_EOF) execute(token->getNextToken());

        switch (token->getType())
        {
        case TOK_OUT: {
            if(STRDATA_FLAG) {
                std::cout << STRDATA_REG;
                STR_FLAG = false;
                break;
            }
            if(NUM_FLAG) {
                std::cout << NUM_REG;
                NUM_FLAG = false;
                break;
            }
            std::cout << "ERROR" << std::endl;
            break;
        }

        case TOK_TYPE_NUM: {
            if(!STR_FLAG) {
                std::cout << "ERROR" << std::endl;
                break;
            }

            Variable newVar;
            newVar.setType(VAR_NUM);
            newVar.setName(STR_REG);
            STR_FLAG = false;

            if(NUM_FLAG) {
                int pointer = dataArea.pushNumber(NUM_REG);
                newVar.setPointer(pointer);
                NUM_FLAG = false;
            }

            variableArea.push(newVar);
            break;
        }

        case TOK_STR: {
            if(STR_FLAG) {
                std::cout << "ERROR" << std::endl;
                break;
            }
            STR_REG = token->getValue();
            STR_FLAG = true;
            break;
        }

        case TOK_STRDATA: {
            if(STRDATA_FLAG) {
                std::cout << "ERROR" << std::endl;
                break;
            }
            STRDATA_REG = token->getValue();
            STRDATA_FLAG = true;
            break;
        }

        case TOK_NUMBER: {
            if(!NUM_FLAG) {
                NUM_REG = std::stoi(token->getValue());
                NUM_FLAG = true;
            }
            break;
        }

        default: 
            break;
        }
        return;
    }
};
