#include <iostream>
#include <memory>

#include "../token/token.h"

#include "../dataArea/area/variableArea.h"
#include "../dataArea/area/functionArea.h"
#include "../dataArea/area/temporaryArea.h"

#include "../dataArea/variable.h"
#include "../dataArea/function.h"

#include "token/inout.h"
#include "config.h"

#pragma once

#define SYSTEMVAR "SYSTEMVAR_"

enum ALUType {
    ALU_STATELESS,
    ALU_ADD,
    ALU_SUB,
    ALU_DIV,
    ALU_MUL,
    ALU_EQUAL,
};

class Execute {
private:
    std::string STRDATA_REG;
    bool STRDATA_FLAG;

    int NUM_REG;
    bool NUM_FLAG;

    int ALU_REG;
    ALUType ALU_FLAG;

    VariableArea* variableArea;
    TemporaryArea* temporaryArea;
    FunctionArea* functionArea;
    Function function;

    int calculator(int data1, int data2) {
        if(ALU_FLAG == ALU_ADD) return data2 + data1;
        if(ALU_FLAG == ALU_SUB) return data2 - data1;
        if(ALU_FLAG == ALU_DIV) return data2 / data1;
        if(ALU_FLAG == ALU_MUL) return data2 * data1;
        if(ALU_FLAG == ALU_EQUAL) return data2 == data1;
    }

    bool checkSystemVar(const std::string& str) {
        const std::string prefix = SYSTEMVAR;
        return str.find(prefix) == 0;
    }

public:
    Execute() :
        variableArea(VariableArea::getInstance()),
        temporaryArea(TemporaryArea::getInstance()),
        functionArea(FunctionArea::getInstance()),

        STRDATA_FLAG(false),
        NUM_FLAG(false),
        ALU_FLAG(ALU_STATELESS)
    {}

    int execute(std::shared_ptr<Token> token) {
        if(function.isWriting()) {
            function.pushLine(token);
            if(token->getType() == TOK_DONE) {
                functionArea->push(function);
                function = Function();
            }
            return 0;
        }

        if(token->getNextToken()->getType() != TOK_EOF) {
            if(execute(token->getNextToken()) == -1) return -1;
        }

        switch (token->getType())
        {
        case TOK_FUNCTION: {
            function.setName(token->getValue());
            break;
        }
        case TOK_CALL: {
            Function nextFunction = functionArea->findByName(token->getValue());

            for(int i = 0; i < nextFunction.getLineSize(); i++) {
                if(execute(nextFunction.getLine(i)) == -2) break;;
            }
            break;
        }
        case TOK_PARAMETER: {
            variableArea->callFunction();
            break;
        }
        case TOK_STOP: {
            variableArea->doneFunction();
            return -2;
        }
        case TOK_DONE: {
            variableArea->doneFunction();
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
        case TOK_EQUAL: {
            ALU_FLAG = ALU_EQUAL;
            break;
        }

        case TOK_TRUE: {
            Variable newVar;
            newVar.setType(VAR_BOOL);
            newVar.setDataNum(true);
            temporaryArea->push(newVar);
            break;
        }
        case TOK_FALSE: {
            Variable newVar;
            newVar.setType(VAR_BOOL);
            newVar.setDataNum(false);
            temporaryArea->push(newVar);
            break;
        }

        case TOK_OUT: {
            Variable var = temporaryArea->pop();
            out(var);
            var.clear();
            break;
        }
        case TOK_NEXT: {
            next();
            break;
        }
        case TOK_IN: {
            Variable newVar = in();
            temporaryArea->push(newVar);
            break;
        }
        case TOK_IF: {
            Variable var = temporaryArea->pop();
            if(!var.isValid()) throw SyntaxError("No element to run \"if\".");

            if(!checkSystemVar(var.getName())) throw SyntaxError("No element to run \"if\".");
            if(var.getType() == VAR_STR) throw SyntaxError("The \"true\" and \"false\" values ​​of \"str \"are unknown.");
            if(var.getDataNum() < 1) return -1;
            var.clear();
            break;
        }

        case TOK_TYPE_BOOL: {
            Variable var = temporaryArea->pop();
            
            if(!isBoolType(var)) throw SyntaxError("Types do not match. Note: The variable type is not \"bool\"");
            var.setName(token->getValue());
            variableArea->push(var);
            break;
        }
        case TOK_TYPE_NUM: {
            Variable var = temporaryArea->pop();
            
            if(!isNumType(var)) throw SyntaxError("Types do not match. Note: The variable type is not \"num\"");
            var.setName(token->getValue());
            variableArea->push(var);
            break;
        }
        case TOK_TYPE_STR: {
            Variable var = temporaryArea->pop();

            if(!isStrType(var)) throw SyntaxError("Types do not match. Note: The variable type is not \"str\"");
            var.setName(token->getValue());
            variableArea->push(var);
            break;
        }

        case TOK_STR: {
            Variable var = variableArea->findByName(token->getValue());
            if(var.isValid()) {
                if(ALU_FLAG == ALU_STATELESS) {
                    temporaryArea->push(var);
                    break;
                } else {
                    Variable targetVar = temporaryArea->pop();
                    if(targetVar.getType() == VAR_STR) throw SyntaxError("Strings and numbers cannot be operated on.");
                    int aluRtn = calculator(var.getDataNum(), targetVar.getDataNum());
                    targetVar.clear();

                    Variable newVar;
                    newVar.setType(VAR_NUM);
                    ALU_FLAG = ALU_STATELESS;
                    
                    newVar.setDataNum(aluRtn);
                    temporaryArea->push(newVar);
                }
            }
            break;
        }

        case TOK_STRDATA: {
            Variable newVar;
            newVar.setType(VAR_STR);
            newVar.setDataStr(token->getValue());
            temporaryArea->push(newVar);
            break;
        }

        case TOK_NUMBER: {
            if(ALU_FLAG == ALU_STATELESS) {
                Variable newVar;
                newVar.setType(VAR_NUM);

                newVar.setDataNum(std::stoi(token->getValue()));
                temporaryArea->push(newVar);
            } else {
                Variable var = temporaryArea->pop();
                if(var.getType() == VAR_STR) throw SyntaxError("Strings and numbers cannot be operated on.");
                int aluRtn = calculator(var.getDataNum(), std::stoi(token->getValue()));
                var.clear();

                Variable newVar;
                newVar.setType(VAR_NUM);
                ALU_FLAG = ALU_STATELESS;
                
                newVar.setDataNum(aluRtn);
                temporaryArea->push(newVar);
            }
            break;
        }

        default: 
            break;
        }
        return 0;
    }
};
