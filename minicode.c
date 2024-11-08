#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

#include "header/token.h"
#include "header/error.h"
#include "header/execute.h"


int main(int argc, char *argv[]) {
    if (argc < 2) fileError("No file provided.");
    
    const char *filename = argv[1];
    const char *ext = strrchr(filename, '.');
    if (ext == NULL || strcmp(ext, ".mini") != 0) fileError("The file must have a '.mini' extension.");

    FILE *file = fopen(filename, "r");
    if (file == NULL) fileError("Can't open file.");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        const char *src = line;
        Token *allToken = (Token *)malloc(sizeof(Token) * 10);
        if (!allToken) {
            fileError("Memory allocation failed.");
        }

        int index = 0;
        while (1) {
            Token token = getNextToken(&src);
            allToken[index] = token;
            index++;
            if (token.type == TOK_EOF) break;

            if (index >= 10) {
                allToken = (Token *)realloc(allToken, sizeof(Token) * (index + 10));
                if (!allToken) {
                    fileError("Memory allocation failed.");
                }
            }
        }

        if (allToken[0].type == TOK_STR) {
            execute(allToken);
        }

        free(allToken);
    }

    return 0;
}