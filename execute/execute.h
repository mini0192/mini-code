#include <iostream>
#include <memory>

#include "../header/token.h"
#include "variableAreaImpl.h"
#include "functionAreaImpl.h"
#include "temporaryAreaImpl.h"

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
    TemporaryArea temporaryArea;
    FunctionArea functionArea;
    FunctionData functionData;

    int handleNumberCalculation(int num1, int num2) {
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
                functionData = FunctionData();
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
                if(execute(nextFunction->getLine(i)) == -2) break;;
            }
            break;
        }
        case TOK_PARAMETER: {
            variableArea.callFunction();
            break;
        }
        case TOK_STOP: {
            variableArea.doneFunction();
            return -2;
        }
        case TOK_DONE: {
            variableArea.doneFunction();
            break;
        }
        case TOK_GIVE: {
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
            temporaryArea.push(newVar);
            break;
        }
        case TOK_FALSE: {
            Variable newVar;
            newVar.setType(VAR_BOOL);
            newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
            newVar.setDataNum(false);
            temporaryArea.push(newVar);
            break;
        }

        case TOK_OUT: {
            Variable var = temporaryArea.pop();
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
                Variable newVar;
                newVar.setType(VAR_NUM);
                newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
                newVar.setDataNum(std::stoi(data));
                temporaryArea.push(newVar);
            } else {
                Variable newVar;
                newVar.setType(VAR_STR);
                newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
                newVar.setDataStr(token->getValue());
                temporaryArea.push(newVar);
            }
            break;
        }
        case TOK_IF: {
            Variable var = temporaryArea.pop();
            if(!checkSystemVar(var.getName())) throw SyntaxError("No element to run \"out\".");
            if(var.getType() == VAR_STR) throw SyntaxError("The \"true\" and \"false\" values ​​of \"str \"are unknown.");
            if(NUM_REG != 1) return -1;
            break;
        }

        case TOK_TYPE_BOOL: {
            if(!VAR_NAME_FLAG) throw SyntaxError("Missing variable name or duplicate variable name..");
            Variable var = temporaryArea.pop();
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
            if(!VAR_NAME_FLAG) throw SyntaxError("Missing variable name or duplicate variable name..");
            Variable var = temporaryArea.pop();
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
            if(!VAR_NAME_FLAG) throw SyntaxError("Missing variable name or duplicate variable name..");
            Variable var = temporaryArea.pop();
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
                    temporaryArea.push(newVar);
                } else {
                    if(ALU_FLAG == ALU_STATELESS) {
                        Variable newVar;
                        newVar.setType(VAR_NUM);
                        newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
                        newVar.setDataNum(var->getDataNum());
                        temporaryArea.push(newVar);
                    } else {
                        Variable newVar;
                        newVar.setType(VAR_NUM);
                        newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));

                        Variable lastVar = temporaryArea.pop();
                        if(lastVar.getType() == VAR_STR) throw SyntaxError("Strings and numbers cannot be operated on.");
                        int aluRetn = handleNumberCalculation(lastVar.getDataNum(), var->getDataNum());

                        newVar.setDataNum(aluRetn);
                        temporaryArea.push(newVar);
                        
                        ALU_FLAG = ALU_STATELESS;
                    }
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
            temporaryArea.push(newVar);
            break;
        }

        case TOK_NUMBER: {
            if(ALU_FLAG == ALU_STATELESS) {
                Variable newVar;
                newVar.setType(VAR_NUM);
                newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));
                newVar.setDataNum(std::stoi(token->getValue()));
                temporaryArea.push(newVar);
            } else {
                Variable newVar;
                newVar.setType(VAR_NUM);
                newVar.setName(SYSTEMVAR + std::to_string(systemVarCount++));

                Variable var = temporaryArea.pop();
                if(var.getType() == VAR_STR) throw SyntaxError("Strings and numbers cannot be operated on.");
                int aluRetn = handleNumberCalculation(var.getDataNum(), std::stoi(token->getValue()));

                newVar.setDataNum(aluRetn);
                temporaryArea.push(newVar);
                
                ALU_FLAG = ALU_STATELESS;
            }
            break;
        }

        default: 
            break;
        }
        return 0;
    }
};
