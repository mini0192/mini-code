#include <string>
#include <sstream>
#include <memory>

#pragma once

enum TokenType {
    TOK_TYPE_NUM,
    TOK_TYPE_STR,
    TOK_TYPE_BOOL,
    TOK_SAVE,

    TOK_VAR,
    TOK_OUT,
    TOK_NEXT,
    TOK_IN,
    TOK_IF,

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
    TOK_EQUAL,

    TOK_FUNCTION,
    TOK_PARAMETER,
    TOK_STOP,
    TOK_DONE,
    TOK_CALL,
    TOK_GIVE,

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
    case TOK_SAVE:
        return "TOK_SAVE";
    
    case TOK_VAR:
        return "TOK_VAR";
    case TOK_OUT:
        return "TOK_OUT";
    case TOK_NEXT:
        return "TOK_NEXT";
    case TOK_IN:
        return "TOK_IN";
    case TOK_IF:
        return "TOK_IF";

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
    case TOK_EQUAL:
        return "TOK_EQUAL";

    case TOK_FUNCTION:
        return "TOK_FUNCTION";
    case TOK_PARAMETER:
        return "TOK_PARAMETER";
    case TOK_STOP:
        return "TOK_STOP";
    case TOK_DONE:
        return "TOK_DONE";
    case TOK_CALL:
        return "TOK_CALL";
    case TOK_GIVE:
        return "TOK_GIVE";

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