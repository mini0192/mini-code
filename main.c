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

typedef struct {
    char name[MAX_VAR_NAME];
    int value;
} Var;

Var vars[MAX_VARS];
int varCount = 0;

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

void execute(Token *token) {
    // 입력
    if(strcmp(token[0].value, "in") == 0) {
        if(token[1].type != TOK_STR) {
            printf("Enter the variable to receive input.\n");
            return;
        }
        for (int i = 0; i < varCount; i++) {
            if (strcmp(vars[i].name, token[1].value) == 0) {
                scanf("%d", &vars[i].value);
                return;
            }
        }
        printf("Error: Variable '%s' not found.\n", token[1].value);
        return;
    }
    
    // 출력
    if(strcmp(token[0].value, "out") == 0) {
        if (token[1].type == TOK_STRDATA) {
            printf("%s\n", token[1].value);
        } else if (token[1].type == TOK_STR) {
            for (int i = 0; i < varCount; i++) {
                if (strcmp(vars[i].name, token[1].value) == 0) {
                    printf("%d\n", vars[i].value);
                    return;
                }
            }
            printf("Error: Variable '%s' not found.\n", token[1].value);
        }
        return;
    }

    // 변수 선언
    if(strcmp(token[0].value, "var") == 0) {
        Token varNameToken = token[1];
        Token varValueToken = token[3];

        if(strcmp(token[2].value, "=") != 0) {
            printf("Error: Variables need to be initialized.\n");
            return;
        }

        if(varCount >= MAX_VARS) {
            printf("Error: Maximum number of variables reached.\n");
            return;
        }

        if(varNameToken.type != TOK_STR) {
            printf("Error: Invalid variable name.\n");
            return;
        }

        strcpy(vars[varCount].name, varNameToken.value);
        vars[varCount].value = atoi(varValueToken.value);
        varCount++;

        return;
    }

    // 변수 수정
    if(strcmp(token[0].value, "set") == 0) {
        if (token[1].type != TOK_STR) {
            printf("Error: Invalid syntax for 'set'. Correct syntax: set <variable_name> <value>\n");
            return;
        }

        if(strcmp(token[2].value, "=") != 0) {
            printf("Error: Variables need to be initialized.\n");
            return;
        }

        for (int i = 0; i < varCount; i++) {
            if (strcmp(vars[i].name, token[1].value) == 0) {
                vars[i].value = atoi(token[3].value);
                return;
            }
        }
        
        printf("Error: Variable '%s' not found.\n", token[1].value);
        return;
    }

    printf("This is an unknown phrase.\n");
}

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Can't open file.\n");
        return 1;
    }

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
    }

    return 0;
}