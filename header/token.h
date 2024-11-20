#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "error.h"

#pragma once

enum TokenType {
    TOK_TYPE_NUM,
    TOK_TYPE_STR,
    TOK_TYPE_BOOL,
    TOK_VAR,

    TOK_OUT,
    TOK_IN,

    TOK_SIGN,
    TOK_STRDATA,
    TOK_NUMBER,
    TOK_STR,

    TOK_UNKNOWN,
    TOK_EOF,
};

class Token {
private:
    TokenType type;
    std::shared_ptr<Token> nextToken;
    std::string value;

public:
    Token() :
        type(TOK_UNKNOWN),
        nextToken(nullptr),
        value("")
    {}

    void clear() {
        type = TOK_UNKNOWN;
        nextToken = NULL;
        value.clear();
    }

    TokenType getType() {
        return type;
    }

    void setType(TokenType type) {
        this->type = type;
    }

    std::shared_ptr<Token> getNextToken() {
        return nextToken;
    }

    void setNextToken(std::shared_ptr<Token> nextToken) {
        this->nextToken = nextToken;
    } 

    std::string getValue() {
        return value;
    }

    void setValue(std::string value) {
        this->value = value;
    }
};

void tokenPrint(const std::shared_ptr<Token> token) {
    if(token->getNextToken()) {
        tokenPrint(token->getNextToken());
    }
    std::cout << "Type: " << token->getType() << ", Value: " << token->getValue() << std::endl;
}


std::shared_ptr<Token> getToken(std::stringstream& ss) {
    std::shared_ptr<Token> token = std::make_shared<Token>();
    std::string word;
    ss >> word;

    if(word == "") {
        throw SyntaxError("That syntax is incorrect.");
    }

    if(word == "num") {
        token->setType(TOK_TYPE_NUM);
        token->setNextToken(getToken(ss));

        return token;
    }

    if(word == "str") {
        token->setType(TOK_TYPE_STR);
        token->setNextToken(getToken(ss));

        return token;
    }
    
    if(word == "bool") {
        token->setType(TOK_TYPE_BOOL);
        token->setNextToken(getToken(ss));

        return token;
    }

    if(word == "out") {
        token->setType(TOK_OUT);
        token->setNextToken(getToken(ss));

        return token;
    }

    if(word == "in") {
        token->setType(TOK_IN);
        token->setNextToken(getToken(ss));

        return token;
    }

    if (word.front() == '"' && word.back() == '"') {
        token->setType(TOK_STRDATA);
        token->setValue(word.substr(1, word.length() - 2));

        return token;
    }

    std::stringstream numStream(word);
    int intValue;
    float floatValue;

    if (numStream >> intValue && numStream.eof()) {
        token->setType(TOK_NUMBER);
        token->setValue(std::to_string(intValue));

        return token;
    }

    token->setType(TOK_STR);
    token->setValue(word);
}

std::shared_ptr<Token> getNextToken(std::string src) {
    std::stringstream ss(src);
    std::string part;

    std::shared_ptr<Token> token = getToken(ss);
    tokenPrint(token);
    return token;
}