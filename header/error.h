#include<stdio.h>
#include<stdlib.h>

#pragma once

// 오류
void error(const char *errorMessage) {
    printf("\n");
    printf("%s\n", errorMessage);
    exit(1);
}

/**
 * 변수를 찾을 수 없음
 */
void notFoundVarError(char *name) {
    char message[256];
    sprintf(message, "Variable Error: Variable '%s' not found.", name);
    error(message);
}

void conflictVariable(char *name) {
    char message[256];
    sprintf(message, "Variable Error: Variable name '%s' conflict.", name);
    error(message);
}

void syntaxError() {
    error("SyntaxError: Uninterpretable");
}