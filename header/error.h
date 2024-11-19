#include <iostream>
#include <stdexcept>
#include <string>

#pragma once

class SyntaxError : public std::exception {
private:
    std::string message;

public:
    SyntaxError(const std::string& msg) {
        message = msg;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};