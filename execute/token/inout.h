#ifndef EXEINOUT_H
#define EXEINOUT_H

#include <iostream>
#include <memory>

#include "../../dataArea/variable.h"
#include "../config.h"

void next() {
    std::cout << std::endl;
}

void out(Variable var) {
    if(!var.isValid()) throw SyntaxError("No element to run \"out\".");
    if(var.getType() == VAR_STR) std::cout << var.getDataStr();
    if(var.getType() == VAR_NUM) std::cout << var.getDataNum();
}

Variable in() {
    std::string data;
    std::cin >> data;

    Variable newVar;
    if(isNumber(data)) {
        newVar.setType(VAR_NUM);
        newVar.setDataNum(std::stoi(data));
        return newVar;
    }

    newVar.setType(VAR_STR);
    newVar.setDataStr(data);
    return newVar;
}

#endif