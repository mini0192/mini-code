#pragma once

typedef enum {
    TOK_UNKNOWN,
    TOK_EOF,
    TOK_SIGN,
    TOK_STR,
    TOK_STRDATA,
    TOK_NUMBER,
} TokenType;

typedef struct {
    TokenType type;
    char value[100];
} Token;

Token getNextToken(const char **src) {
    Token token;
    token.type = TOK_UNKNOWN;
    token.value[0] = '\0';

    // 공백 제거
    while(isspace(**src)) {
        (*src)++;
    }
    
    // 문장이 끝났다면
    if(**src == '\0') {
        token.type = TOK_EOF;
        return token;
    }

    // 숫자라면
    if(isdigit(**src)) {
        int i = 0;
        while (isdigit(**src)) {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        token.type = TOK_NUMBER;
        return token;
    }

    // 영어라면
    if(isalpha(**src)) {
        int i = 0;
        while(isalpha(**src)) {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        token.type = TOK_STR;
        return token;
    }

    // 문자열이라면
    if(**src == '"') {
        (*src)++;
        int i = 0;
        while(**src != '"' && **src != '\0') {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        if(**src == '"') {
            (*src)++;
            token.type = TOK_STRDATA;
        }
        return token;
    }

    // 특수 문자라면
    if(ispunct(**src)) {
        token.type = TOK_SIGN;
        token.value[0] = **src;
        token.value[1] = '\0';
        (*src)++;
        return token;
    }

    token.value[0] = **src;
    token.value[1] = '\0';
    token.type = TOK_UNKNOWN;
    (*src)++;

    return token;
}