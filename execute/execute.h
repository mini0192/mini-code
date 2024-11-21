#include <iostream>
#include <memory>

#include "../header/token.h"
#include "variableAreaImpl.h"
#include "dataAreaImpl.h"
#include "functionAreaImpl.h"

#pragma once

enum ALUType {
    ALU_STATELESS,
    ALU_ADD,
    ALU_SUB,
    ALU_DIV,
    ALU_MUL,
};

class Execute {
private:
    std::string VAR_NAME_REG;
    bool VAR_NAME_FLAG;

    std::string STRDATA_REG;
    bool STRDATA_FLAG;

    int NUM_REG;
    bool NUM_FLAG;

    int ALU_REG;
    ALUType ALU_FLAG;

    VariableArea variableArea;
    DataArea dataArea;

    FunctionArea functionArea;
    FunctionData functionData;

    int handleCalculation(int num1, int num2) {
        if(ALU_FLAG == ALU_STATELESS) throw SyntaxError("Unable to understand the syntax.");
        if(ALU_FLAG == ALU_ADD) return num1 + num2;
        if(ALU_FLAG == ALU_SUB) return num1 - num2;
        if(ALU_FLAG == ALU_DIV) return num1 / num2;
        if(ALU_FLAG == ALU_MUL) return num1 * num2;
        ALU_FLAG = ALU_STATELESS;
    }

    bool isNumber(const std::string& s) {
        for (char const &ch : s) {
            if (std::isdigit(ch) == 0) return false;
        }
        return true;
    }

public:
    Execute() :
        VAR_NAME_FLAG(false),
        STRDATA_FLAG(false),
        NUM_FLAG(false),
        ALU_FLAG(ALU_STATELESS)
    {}

    int execute(std::shared_ptr<Token> token) {
        if(functionData.isWriting()) {
            functionData.pushLine(token);
            if(token->getType() == TOK_DONE) {
                functionArea.push(functionData);
                functionData.clear();
            }
            return 0;
        }

        if(token->getNextToken()->getType() != TOK_EOF) {
            if(execute(token->getNextToken()) == -1) return -1;
        }

        switch (token->getType())
        {
        case TOK_FUNCTION: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Function name is missing.");
            functionData.setName(VAR_NAME_REG);
            VAR_NAME_FLAG = false;
            break;
        }

        case TOK_CALL: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Function name is missing.");
            FunctionData* nextFunction = functionArea.findByName(VAR_NAME_REG);
            for(int i = 0; i < nextFunction->getLineSize(); i++) {
                execute(nextFunction->getLine(i));
            }
        }

        case TOK_ADD: {
            ALU_FLAG = ALU_ADD;
            break;
        }
        case TOK_SUB: {
            ALU_FLAG = ALU_SUB;
            break;
        }
        case TOK_DIV: {
            ALU_FLAG = ALU_DIV;
            break;
        }
        case TOK_MUL: {
            ALU_FLAG = ALU_MUL;
            break;
        }

        case TOK_TRUE: {
            if(NUM_FLAG) throw ProgramError("NUM_REG is already in use.");
            NUM_REG = 1;
            NUM_FLAG = true;
            break;
        }
        case TOK_FALSE: {
            if(NUM_FLAG) throw ProgramError("NUM_REG is already in use.");
            NUM_REG = 0;
            NUM_FLAG = true;
            break;
        }

        case TOK_OUT: {
            if(STRDATA_FLAG) {
                std::cout << STRDATA_REG;
                STRDATA_FLAG = false;
                break;
            }
            if(NUM_FLAG) {
                std::cout << NUM_REG;
                NUM_FLAG = false;
                break;
            }
            throw SyntaxError("No element to run \"out\".");
        }
        case TOK_IN: {
            std::string data;
            std::cin >> data;

            if(isNumber(data)) {
                if(!NUM_FLAG) {
                    NUM_REG = std::stoi(data);
                    NUM_FLAG = true;
                } else {
                    NUM_REG = handleCalculation(std::stoi(token->getValue()), NUM_REG);
                }
            } else {
                if(STRDATA_FLAG) throw ProgramError("STRDATA_REG is already in use.");

                STRDATA_REG = data;
                STRDATA_FLAG = true;
            }
            break;
        }
        case TOK_IF: {
            if(!NUM_FLAG) throw SyntaxError("Condition does not exist.");
            NUM_FLAG = false;
            if(NUM_REG != 1) return -1;
            break;
        }

        case TOK_TYPE_BOOL: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Variable name is missing.");
            if(!NUM_FLAG) throw SyntaxError("Variable not initialized.");

            Variable newVar;
            newVar.setType(VAR_BOOL);
            newVar.setName(VAR_NAME_REG);
            VAR_NAME_FLAG = false;

            if(NUM_FLAG) {
                if(NUM_REG != 0 && NUM_REG != 1) throw SyntaxError("The bool data type can only store 0 or 1.");
                int pointer = dataArea.pushNumber(NUM_REG);
                newVar.setPointer(pointer);
                NUM_FLAG = false;
            }

            variableArea.push(newVar);
            break;
        }
        case TOK_TYPE_NUM: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Variable name is missing.");
            if(!NUM_FLAG) throw SyntaxError("Variable not initialized.");

            Variable newVar;
            newVar.setType(VAR_NUM);
            newVar.setName(VAR_NAME_REG);
            VAR_NAME_FLAG = false;

            int pointer = dataArea.pushNumber(NUM_REG);
            newVar.setPointer(pointer);
            NUM_FLAG = false;

            variableArea.push(newVar);
            break;
        }
        case TOK_TYPE_STR: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Variable name is missing.");
            if(!STRDATA_FLAG) throw SyntaxError("Variable not initialized.");

            Variable newVar;
            newVar.setType(VAR_STR);
            newVar.setName(VAR_NAME_REG);
            VAR_NAME_FLAG = false;

            int pointer = dataArea.pushStr(STRDATA_REG);
            newVar.setPointer(pointer);
            STRDATA_FLAG = false;

            variableArea.push(newVar);
            break;
        }

        case TOK_STR: {
            Variable* var = variableArea.findByName(token->getValue());
            if(var) {
                int pointer = var->getPointer();
                if(var->getType() == VAR_STR) {
                    if(STRDATA_FLAG) throw ProgramError("STRDATA_REG is already in use.");
                    STRDATA_REG = dataArea.getStr(pointer);
                    STRDATA_FLAG = true;
                } else {
                    if(!NUM_FLAG) {
                        NUM_REG = dataArea.getNumber(pointer);
                        NUM_FLAG = true;
                    } else {
                        NUM_REG = handleCalculation(dataArea.getNumber(pointer), NUM_REG);
                    }
                }
                break;
            }

            VAR_NAME_REG = token->getValue();
            VAR_NAME_FLAG = true;
            break;
        }

        case TOK_STRDATA: {
            if(STRDATA_FLAG) throw ProgramError("STRDATA_REG is already in use.");

            STRDATA_REG = token->getValue();
            STRDATA_FLAG = true;
            break;
        }

        case TOK_NUMBER: {
            if(!NUM_FLAG) {
                NUM_REG = std::stoi(token->getValue());
                NUM_FLAG = true;
            } else {
                NUM_REG = handleCalculation(std::stoi(token->getValue()), NUM_REG);
            }
            break;
        }

        default: 
            break;
        }
        return 0;
    }
};
