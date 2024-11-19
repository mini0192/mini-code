#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <sstream>
#include <queue>
#include <cstdlib>

#include "error.h"

#pragma once

enum TokenType {
    TOK_VAR,
    TOK_OUT,
    TOK_IN,
    TOK_UNKNOWN,
    TOK_EOF,
    TOK_SIGN,
    TOK_STRDATA,
    TOK_NUMBER,
};

class Token {
public:
    TokenType type;
    TokenType valueType;
    std::string value;

    Token() {
        type = TOK_UNKNOWN;
        value = "";
    }

    void clear() {
        type = TOK_UNKNOWN;
        value.clear();
    }
};

void tokenPrint(const Token token) {
    std::cout << "Type: " << token.type << ", ValueType:" << token.valueType << ", Value: " << token.value << std::endl;
}


Token getToken(std::stringstream& ss) {
    Token token;

    std::string word;
    ss >> word;

    if(word == "") {
        throw SyntaxError("That syntax is incorrect.");
    }

    if(word == "out") {
        token.type = TOK_OUT;
        
        Token nextToken = getToken(ss);
        token.valueType = nextToken.type;
        token.value = nextToken.value;

        return token;
    }

    if(word == "in") {
        token.type = TOK_IN;

        Token nextToken = getToken(ss);
        token.valueType = nextToken.type;
        token.value = nextToken.value;

        return token;
    }

    if (word.front() == '"' && word.back() == '"') {
        token.type = TOK_STRDATA;
        token.value = word.substr(1, word.length() - 2);
        return token;
    }

    std::stringstream numStream(word);
    int intValue;
    float floatValue;

    if (numStream >> intValue && numStream.eof()) {
        token.type = TOK_NUMBER;
        token.value = std::to_string(intValue);
        std::cout << "GOOD" << std::endl;
        return token;
    }

    token.type = TOK_VAR;
    Token nextToken = getToken(ss);
    token.valueType = nextToken.type;
    token.value = nextToken.value;
    
    return token;
}

Token getNextToken(std::string src) {

    std::stringstream ss(src);
    std::string part;

    Token token = getToken(ss);
    tokenPrint(token);
    return token;
}