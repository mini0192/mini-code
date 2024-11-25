#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <stack>

#include "../error/error.h"
#include "token.h"

#pragma once

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
    } else if (word == "==") {
        token->setType(TOK_EQUAL);
    }

    else if (word == "function") {
        token->setType(TOK_FUNCTION);
    } else if (word == "parameter") {
        token->setType(TOK_PARAMETER);
    } else if (word == "stop") {
        token->setType(TOK_STOP);
    } else if (word == "done") {
        token->setType(TOK_DONE);
    } else if (word == "call") {
        token->setType(TOK_CALL);
    } else if (word == "give") {
        token->setType(TOK_GIVE);
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
    } else if (word == "save") {
        token->setType(TOK_SAVE);
    }
    
    else if (word == "out") {
        token->setType(TOK_OUT);
    } else if(word == "next") {
        token->setType(TOK_NEXT);
    } else if (word == "in") {
        token->setType(TOK_IN);
    } else if (word == "if") {
        token->setType(TOK_IF);
    }
    
    else if (word.front() == '"') {
        token->setType(TOK_STRDATA);
        std::string data;

        while (true) {
            data += word;
            if (word.back() == '"') {
                break;
            }
            data += " ";
            ss >> word;
        }

        if (data.length() >= 2) {
            token->setValue(data.substr(1, data.length() - 2));
        } else {
            token->setValue("");
        }
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
    // tokenPrint(token);
    // std::cout << std::endl;

    return token;
}