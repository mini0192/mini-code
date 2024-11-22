#include <iostream>
#include <memory>

#include "../header/token.h"
#include "variableAreaImpl.h"
#include "functionAreaImpl.h"

#pragma once

#define SYSTEMVAR "SYSTEMVAR_"

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

    int systemVarCount;

    VariableArea variableArea;
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

    bool checkSystemVar(const std::string& str) {
        const std::string prefix = SYSTEMVAR;
        return str.find(prefix) == 0;
    }

public:
    Execute() :
        VAR_NAME_FLAG(false),
        STRDATA_FLAG(false),
        NUM_FLAG(false),
        ALU_FLAG(ALU_STATELESS),
        systemVarCount(0)
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
            break;
        }

        case TOK_PARAMETER: {
            break;
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
            Variable newVar;
            newVar.setType(VAR_BOOL);
            newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
            newVar.setDataNum(true);
            variableArea.push(newVar);
            break;
        }
        case TOK_FALSE: {
            Variable newVar;
            newVar.setType(VAR_BOOL);
            newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
            newVar.setDataNum(false);
            variableArea.push(newVar);
            break;
        }

        case TOK_OUT: {
            Variable var = variableArea.pop();
            if(!checkSystemVar(var.getName())) throw SyntaxError("No element to run \"out\".");
            if(var.getType() == VAR_STR) std::cout << var.getDataStr();
            if(var.getType() == VAR_NUM) std::cout << var.getDataNum();
            break;
        }
        case TOK_NEXT: {
            std::cout << std::endl;
            break;
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
            Variable var = variableArea.pop();
            if(!checkSystemVar(var.getName())) throw SyntaxError("The variable is not initialized. [It is not a system variable (" + var.getName() + ")]");
            if(var.getType() != VAR_NUM && var.getType() != VAR_BOOL) throw SyntaxError("Types do not match. Note: The variable type is not \"num\" or \"bool\"");

            Variable newVar;
            newVar.setType(VAR_BOOL);
            newVar.setName(VAR_NAME_REG);

            int data = var.getDataNum();
            if(data != 0 && data != 1) throw SyntaxError("The bool data type can only store 0 or 1.");

            newVar.setDataNum(data);
            variableArea.push(newVar);

            VAR_NAME_FLAG = false;
            break;
        }
        case TOK_TYPE_NUM: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Variable name is missing.");
            Variable var = variableArea.pop();
            std::cout << var.getName() << std::endl;
            if(!checkSystemVar(var.getName())) throw SyntaxError("The variable is not initialized. [It is not a system variable (" + var.getName() + ")]");
            if(var.getType() != VAR_NUM && var.getType() != VAR_BOOL) throw SyntaxError("Types do not match. Note: The variable type is not \"num\" or \"bool\"");

            Variable newVar;
            newVar.setType(VAR_NUM);
            newVar.setName(VAR_NAME_REG);

            newVar.setDataNum(var.getDataNum());
            variableArea.push(newVar);

            VAR_NAME_FLAG = false;
            break;
        }
        case TOK_TYPE_STR: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Variable name is missing.");
            Variable var = variableArea.pop();
            if(!checkSystemVar(var.getName())) throw SyntaxError("The variable is not initialized. [It is not a system variable (" + var.getName() + ")]");
            if(var.getType() != VAR_STR) throw SyntaxError("Types do not match. Note: The variable type is not \"str\"");

            Variable newVar;
            newVar.setType(VAR_STR);
            newVar.setName(VAR_NAME_REG);
            newVar.setDataStr(var.getDataStr());
            variableArea.push(newVar);

            VAR_NAME_FLAG = false;
            break;
        }

        case TOK_STR: {
            Variable* var = variableArea.findByName(token->getValue());
            if(var) {
                if(var->getType() == VAR_STR) {
                    Variable newVar;
                    newVar.setType(VAR_STR);
                    newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
                    newVar.setDataStr(var->getDataStr());
                    variableArea.push(newVar);
                } else {
                    Variable newVar;
                    newVar.setType(VAR_NUM);
                    newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
                    newVar.setDataNum(var->getDataNum());
                    variableArea.push(newVar);
                }
                break;
            }
            VAR_NAME_REG = token->getValue();
            VAR_NAME_FLAG = true;
            break;
        }

        case TOK_STRDATA: {
            Variable newVar;
            newVar.setType(VAR_STR);
            newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
            newVar.setDataStr(token->getValue());
            variableArea.push(newVar);
            break;
        }

        case TOK_NUMBER: {
            Variable newVar;
            newVar.setType(VAR_NUM);
            newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
            newVar.setDataNum(std::stoi(token->getValue()));
            variableArea.push(newVar);
            break;
        }

        default: 
            break;
        }
        return 0;
    }
};
