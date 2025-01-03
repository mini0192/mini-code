#ifndef VARIABLE_H
#define VARIABLE_H

#include "area/dataArea.h"

enum VariableType {
    VAR_NUM,
    VAR_STR,
    VAR_BOOL,

    FUNCTION_DATA,
    VAR_NOT,
};

class Variable {
private:
    DataArea* dataArea;
    std::string name;
    VariableType VAR_TYPE;
    int pointer;

public:
    Variable() :
        dataArea(DataArea::getInstance()),
        VAR_TYPE(VAR_NOT)
    {}

    bool isValid() {
        if(VAR_TYPE == VAR_NOT) return false;
        return true;
    }

    std::string getName() {
        return name;
    }

    void setName(std::string name) {
        this->name = name;
    }

    std::string getDataStr() {
        return dataArea->getStr(pointer);
    }

    void setDataStr(std::string data) {
        if(VAR_TYPE != VAR_STR) throw SyntaxError("Types do not match. Note: The variable type is not \"str\"");
        pointer = dataArea->pushStr(data);
    }

    int getDataNum() {
        return dataArea->getNumber(pointer);
    }

    void setDataNum(int data) {
        if(VAR_TYPE != VAR_NUM && VAR_TYPE != VAR_BOOL) throw SyntaxError("Types do not match. Note: The variable type is not \"num\" or \"bool\"");
        pointer = dataArea->pushNumber(data);
    }

    int getDataFunc() {
        return dataArea->getNumber(pointer);
    }

    void setDataFunc(int data) {
        if(VAR_TYPE != FUNCTION_DATA) throw SyntaxError("Types do not match. Note: The variable type is not \"num\" or \"bool\"");
        pointer = dataArea->pushNumber(data);
    }

    VariableType getType() {
        return VAR_TYPE;
    }

    void setType(VariableType type) {
        this->VAR_TYPE = type;
    }

    int clear() {
        dataArea->clearData(pointer);
    }
};

#endif