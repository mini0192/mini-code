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

    TOK_TRUE,
    TOK_FALSE,

    TOK_ADD,
    TOK_SUB,
    TOK_DIV,
    TOK_MUL,

    TOK_EOF,
};

std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case TOK_TYPE_NUM:
        return "TOK_TYPE_NUM";
    case TOK_TYPE_STR:
        return "TOK_TYPE_STR";
    case TOK_TYPE_BOOL:
        return "TOK_TYPE_BOOL";
    
    case TOK_VAR:
        return "TOK_VAR";
    case TOK_OUT:
        return "TOK_OUT";
    case TOK_IN:
        return "TOK_IN";

    case TOK_SIGN:
        return "TOK_SIGN";
    case TOK_STRDATA:
        return "TOK_STRDATA";
    case TOK_NUMBER:
        return "TOK_NUMBER";
    case TOK_STR:
        return "TOK_STR";

    case TOK_TRUE:
        return "TOK_TRUE";
    case TOK_FALSE:
        return "TOK_FALSE";

    case TOK_ADD:
        return "TOK_ADD";
    case TOK_SUB:
        return "TOK_SUB";
    case TOK_DIV:
        return "TOK_DIV";
    case TOK_MUL:
        return "TOK_MUL";

    case TOK_EOF:
        return "TOK_EOF";
    default:
        return "UNKNOWN";
    }
}

class Token {
private:
    TokenType type;
    std::shared_ptr<Token> nextToken;
    std::string value;

public:
    Token() :
        type(TOK_EOF),
        nextToken(nullptr),
        value("")
    {}

    void clear() {
        type = TOK_EOF;
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
    std::cout << "Type: " << tokenTypeToString(token->getType()) << ", Value: " << token->getValue() << std::endl;
}


std::shared_ptr<Token> getToken(std::stringstream& ss) {
    std::shared_ptr<Token> token = std::make_shared<Token>();
    std::string word;
    ss >> word;

    if (word == "") {
        return token;
    }

    else if (word == "+") {
        token->setType(TOK_ADD);
    } else if (word == "-") {
        token->setType(TOK_SUB);
    } else if (word == "/") {
        token->setType(TOK_DIV);
    } else if (word == "*") {
        token->setType(TOK_MUL);
    }
    
    else if (word == "true") {
        token->setType(TOK_TRUE);
    } else if (word == "false") {
        token->setType(TOK_FALSE);
    }
    
    else if (word == "num") {
        token->setType(TOK_TYPE_NUM);
    } else if (word == "str") {
        token->setType(TOK_TYPE_STR);
    } else if (word == "bool") {
        token->setType(TOK_TYPE_BOOL);
    }
    
    else if (word == "out") {
        token->setType(TOK_OUT);
    } else if (word == "in") {
        token->setType(TOK_IN);
    }
    
    else if (word.front() == '"') {
        token->setType(TOK_STRDATA);
        std::string data;

        while(true) {
            data += word;
            if(word.back() == '"') break;
            data += " ";
            ss >> word;
        }

        token->setValue(data.substr(1, data.length() - 2));
    }
    
    else if(token->getType() == TOK_EOF) {
        std::stringstream numStream(word);
        int intValue;
        float floatValue;

        if (numStream >> intValue && numStream.eof()) {
            token->setType(TOK_NUMBER);
            token->setValue(std::to_string(intValue));
        } else {
            token->setType(TOK_STR);
            token->setValue(word);
        }
    }
    token->setNextToken(getToken(ss));
    return token;
}

std::shared_ptr<Token> getNextToken(std::string src) {
    std::stringstream ss(src);
    std::string part;

    std::shared_ptr<Token> token = getToken(ss);
    tokenPrint(token);
    std::cout << std::endl;

    return token;
}