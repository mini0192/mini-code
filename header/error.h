#include<stdio.h>
#include<stdlib.h>

#pragma once

// 오류
void error(const char *errorMessage) {
    printf("Error: %s\n", errorMessage);
    exit(1);
}

/**
 * 변수를 찾을 수 없음
 */
void notFoundVarError(char *name) {
    char *message;
    sprintf(message, "Variable '%s' not found.", name);
    error(message);
}

/**
 * 문법 오류
 */
void syntaxError(char *errorMessage) {
    char *message;
    sprintf(message, "Syntax Error %s", errorMessage);
    error(message);
}

/**
 * 파일 오픈 오류
 */
void fileError(char *errorMessage) {
    char *message;
    sprintf(message, "File Error %s", errorMessage);
    error(message);
}