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


void execute(Token *token) {

    // 출력
    if(strcmp(token[0].value, "out") == 0) {
        // 문자열이라면
        if (token[1].type == TOK_STRDATA) {
            printf("%s\n", token[1].value);
            return;
        }
        
        // 변수라면
        if (token[1].type == TOK_STR) {
            Token varNameToken = token[1];

            int varIndex = getVarIndex(varNameToken.value);
            if(varIndex == -1) notFoundVarError(varNameToken.value);
            
            printf("%d\n", vars[varIndex].value);
            return;
        }
        syntaxError("Please enter your input values.");
    }

    // 변수 선언
    if(strcmp(token[0].value, "var") == 0) {
        Token varNameToken = token[1];
        Token varValueToken = token[2];

        if(varCount >= MAX_VARS)                syntaxError("Maximum number of variables reached.");
        if(varNameToken.type != TOK_STR)        syntaxError("Invalid variable name.\n");

        strcpy(vars[varCount].name, varNameToken.value);
        vars[varCount].value = atoi(varValueToken.value);
        varCount++;

        return;
    }

    // 변수 수정
    if(strcmp(token[0].value, "set") == 0) {
        Token varNameToken = token[1];
        int data = 0;
        
        if (varNameToken.type != TOK_STR) syntaxError("Invalid syntax for 'set'. Correct syntax: set <variable_name> <value>");
        int varIndex = getVarIndex(varNameToken.value);
        if(varIndex == -1) notFoundVarError(varNameToken.value);

        if(token[2].type == TOK_STR) {
            Token inputFunc = token[2];

            if(strcmp(inputFunc.value, "in") == 0) {
                scanf("%d", &data);
            }
        }

        if(token[2].type == TOK_NUMBER) {
            data = atoi(token[2].value);
        }

        vars[varIndex].value = atoi(token[2].value);
        return;
    }

    syntaxError("This is an unknown phrase.");
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
        Token allToken[10];
        int index = 0;

        while(1) {
            Token token = getNextToken(&src);
            if(token.type == TOK_EOF) break;
            allToken[index] = token;
            index++;
        }

        if(allToken[0].type == TOK_STR) {
            execute(allToken);
        }
        memset(allToken, 0, sizeof(allToken));
    }

    return 0;
}