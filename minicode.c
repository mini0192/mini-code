#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

#define MAX_VAR_NAME 50
#define MAX_VARS 10

typedef enum {
    TOK_UNKNOWN,
    TOK_EOF,
    TOK_SIGN,
    TOK_STR,
    TOK_STRDATA,
    TOK_NUMBER,
} TokenType;

typedef struct {
    TokenType type;
    char value[100];
} Token;

/**
 * 토큰 파싱
 */
Token getNextToken(const char **src) {
    Token token;
    token.type = TOK_UNKNOWN;
    token.value[0] = '\0';

    // 공백 제거
    while(isspace(**src)) {
        (*src)++;
    }
    
    // 문장이 끝났다면
    if(**src == '\0') {
        token.type = TOK_EOF;
        return token;
    }

    // 숫자라면
    if(isdigit(**src)) {
        int i = 0;
        while (isdigit(**src)) {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        token.type = TOK_NUMBER;
        return token;
    }

    // 영어라면
    if(isalpha(**src)) {
        int i = 0;
        while(isalpha(**src)) {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        token.type = TOK_STR;
        return token;
    }

    // 문자열이라면
    if(**src == '"') {
        (*src)++;
        int i = 0;
        while(**src != '"' && **src != '\0') {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        if(**src == '"') {
            (*src)++;
            token.type = TOK_STRDATA;
        }
        return token;
    }

    // 특수 문자라면
    if(ispunct(**src)) {
        token.type = TOK_SIGN;
        token.value[0] = **src;
        token.value[1] = '\0';
        (*src)++;
        return token;
    }

    token.value[0] = **src;
    token.value[1] = '\0';
    token.type = TOK_UNKNOWN;
    (*src)++;

    return token;
}


typedef struct {
    char name[MAX_VAR_NAME];
    int value;
} Var;

Var vars[MAX_VARS];
int varCount = 0;

/**
 * 이름으로 변수 찾기
 */
int getVarIndex(const char *name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}



// 오류
void error(const char *errorMessage) {
    printf("Error: %s\n", errorMessage);
    exit(1);
}

/**
 * 변수를 찾을 수 없음
 */
void notFoundVarError(char *name) {
    char *message;
    sprintf(message, "Variable '%s' not found.", name);
    error(message);
}

/**
 * 문법 오류
 */
void syntaxError(char *errorMessage) {
    char *message;
    sprintf(message, "Syntax Error %s", errorMessage);
    error(message);
}

/**
 * 파일 오픈 오류
 */
void fileError(char *errorMessage) {
    char *message;
    sprintf(message, "File Error %s", errorMessage);
    error(message);
}

char *str = NULL;

int data1 = -1;
int data2 = -1;

/**
 * 0 문자열이 저장됨
 * 1 data1에 반환값이 들어가 있음
 */
int type = -1;

short operator = -1; 

void execute(Token *token) {
    if(token->type == TOK_STR) {
        if(strcmp(token->value, "out") == 0) {
            execute(++token);
            if(type == 0) printf("%s", str);
            if(type == 1) printf("%d", data1);
            type = -1;
            return;
        }

        if(strcmp(token->value, "next") == 0) {
            printf("\n");
            return;
        }

        if(strcmp(token->value, "var") == 0) {
            char *name = (++token)->value;
            if(getVarIndex(name) != -1) syntaxError("error");
            execute(++token);

            strcpy(vars[varCount].name, name);
            if(type == 1) {
                vars[varCount].value = data1;
                type = -1;
            }
            varCount++;
            return;
        }

        int index = getVarIndex(token->value);
        if(index != -1) {
            if(type == -1) {
                data1 = vars[index].value;
                type = 1;
                execute(++token);
                return;
            }

            if(type == 1) {
                data2 = vars[index].value;
            }
        }

        return;
    }

    if(token->type == TOK_STRDATA) {
        str = token->value;
        type = 0;
        return;
    }

    if(token->type == TOK_NUMBER) {
        if(type == -1) {
            data1 = atoi(token->value);
            type = 1;
            execute(++token);
            return;
        }
        
        if(type == 1) {
            data2 = atoi(token->value);
            return;
        }
    }

    if(token->type == TOK_SIGN) {
        if(strcmp(token->value, "+") == 0) {
            execute(++token);
            data1 += data2;
        }
        else if(strcmp(token->value, "-") == 0) {
            execute(++token);
            data1 -= data2;
        }
        else if(strcmp(token->value, "*") == 0) {
            execute(++token);
            data1 *= data2;
        }
        else if(strcmp(token->value, "/") == 0) {
            execute(++token);
            data1 /= data2;
        }
        
        return;
    }
}


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