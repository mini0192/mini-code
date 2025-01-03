#ifndef CONFIG_H
#define CONFIG_H

#include "../dataArea/variable.h"

bool isNumber(const std::string& s) {
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) return false;
    }
    return true;
}

bool isBoolType(Variable var) {
    if(!var.isValid()) return false;
    if(var.getType() != VAR_NUM && var.getType() != VAR_BOOL) return false;

    int data = var.getDataNum();
    if(data != 0 && data != 1) return false;
    return true;
}

bool isNumType(Variable var) {
    if(!var.isValid()) return false;
    if(var.getType() != VAR_NUM && var.getType() != VAR_BOOL) return false;
    return true;
}

bool isStrType(Variable var) {
    if(!var.isValid()) return false;
    if(var.getType() != VAR_STR) return false;
    return true;
}

#endif