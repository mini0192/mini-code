#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue> 

#include "header/token.h"
#include "header/error.h"
// #include "header/execute.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "asd" << std::endl;
    }

    const char *filename = argv[1];
    const char *ext = strrchr(filename, '.');
    if (ext == NULL || strcmp(ext, ".mini") != 0) {
        std::cout << "asd" << std::endl;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "asd" << std::endl;
    }

    std::string line;
    int lineNumber = 0;

    try {
        while (std::getline(file, line)) {
            lineNumber++;
            Token token = getNextToken(line);
            // execute(allToken);
        }
    } catch(SyntaxError ex) {
        std::cout << "from line [" << lineNumber << "] -> " << ex.what() << std::endl;
    }

    return 0;
}
