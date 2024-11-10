#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

#include "header/token.h"
#include "header/error.h"
#include "header/execute.h"

void tokenPrint(Token token) {
    printf("Type: %s, Value: %s\n", token.type, token.value);
}

int main(int argc, char *argv[]) {
    if (argc < 2) error("FileError: No file provided.");
    
    const char *filename = argv[1];
    const char *ext = strrchr(filename, '.');
    if (ext == NULL || strcmp(ext, ".mini") != 0) error("FileError: The file must have a '.mini' extension.");

    FILE *file = fopen(filename, "r");
    if (file == NULL) error("FileError: Can't open file.");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        const char *src = line;
        Token *allToken = (Token *)malloc(sizeof(Token) * 10);
        if (!allToken) {
            error("FileError: Memory allocation failed.");
        }

        int index = 0;
        while (1) {
            Token token = getNextToken(&src);
            tokenPrint(token);
            allToken[index] = token;
            index++;
            if (token.type == TOK_EOF) break;

            if (index >= 10) {
                allToken = (Token *)realloc(allToken, sizeof(Token) * (index + 10));
                if (!allToken) {
                    error("FileError: Memory allocation failed.");
                }
            }
        }
        execute(allToken);
        
        free(allToken);
    }

    return 0;
}