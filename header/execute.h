#include<string.h>
#include<stdbool.h>

#include "token.h"
#include "error.h"


#define MAX_VAR_NAME 50
#define MAX_VARS 10

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

char *str = NULL;

int data1 = -1;
int data2 = -1;

bool isData = false;
bool isStr = false;

int type = -1;

void execute(Token *token) {
    if(token->type == TOK_STR) {
        if(strcmp(token->value, "out") == 0) {
            execute(++token);
            if(isStr) {
                printf("%s", str);
                isStr = false;
            }
            if(isData) {
                printf("%d", data1);
                isData = false;
            }
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
            if(isData) {
                vars[varCount].value = data1;
                isData = false;
            }
            varCount++;
            return;
        }

        if(strcmp(token->value, "set") == 0) {
            char *name = (++token)->value;
            int index = getVarIndex(name);
            if(index == -1) syntaxError("error");

            execute(++token);
            if(isData) {
                vars[index].value = data1;
                isData = false;
            }
        }

        int index = getVarIndex(token->value);
        if(index != -1) {
            if(!isData) {
                data1 = vars[index].value;
                isData = true;
                execute(++token);
                return;
            }

            if(isData) {
                data2 = vars[index].value;
            }
        }

        return;
    }

    if(token->type == TOK_SIGN) {
        if(isData && strcmp(token->value, "+") == 0) {
            execute(++token);
            data1 += data2;
            return;
        }
        
        if(isData && strcmp(token->value, "-") == 0) {
            execute(++token);
            data1 -= data2;
            return;
        }
        
        if(isData && strcmp(token->value, "*") == 0) {
            execute(++token);
            data1 *= data2;
            return;
        }
        
        if(isData && strcmp(token->value, "/") == 0) {
            execute(++token);
            data1 /= data2;
            return;
        }
        
        return;
    }

    if(token->type == TOK_STRDATA) {
        str = token->value;
        isStr = true;
        return;
    }

    if(token->type == TOK_NUMBER) {
        if(!isData) {
            data1 = atoi(token->value);
            isData = true;
            execute(++token);
            return;
        }
        
        if(isData) {
            data2 = atoi(token->value);
            return;
        }
    }
}