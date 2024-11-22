#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <memory>

#include "header/token.h"
#include "header/tokenImpl.h"
#include "header/error.h"
#include "execute/execute.h"
#include "execute/functionAreaImpl.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "File Error: File information is missing." << std::endl;
    }

    const char *filename = argv[1];
    const char *ext = strrchr(filename, '.');
    if (ext == NULL || strcmp(ext, ".mini") != 0) {
        std::cout << "File Error: The file extension is incorrect." << std::endl;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File Error: Failed to open file." << std::endl;
    }

    std::string line;
    int lineNumber = 0;
    Execute run;

    try {
        while (std::getline(file, line)) {
            if(line == "") continue;
            lineNumber++;
            // std::cout << "running[" << lineNumber << "]" << std::endl;
            std::shared_ptr<Token> token = getNextToken(line);
            run.execute(token);
        }
    } catch(ProgramError ex) {
        std::cerr << "line[" << lineNumber << "] Program Error: " << ex.what() << std::endl;
    } catch(SyntaxError ex) {
        std::cerr << "line[" << lineNumber << "] Syntax Error: " << ex.what() << std::endl;
    }
    return 0;
}
