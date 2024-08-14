#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_SYMBOL,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
} Token;

const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do","double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
const int num_keywords = 33;

int is_keyword(const char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

Token get_next_token(FILE *source) {
    Token token;
    int c;
    
    // Ignore whitespace
    do {
        c = fgetc(source);
    } while (isspace(c));
    
    if (c == EOF) {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }
    
    if (isalpha(c)) {
        int i = 0;
        token.lexeme[i++] = c;
        while (isalnum(c = fgetc(source))) {
            token.lexeme[i++] = c;
        }
        ungetc(c, source);
        token.lexeme[i] = '\0';
        
        if (is_keyword(token.lexeme)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
    } else if (isdigit(c)) {
        int i = 0;
        token.lexeme[i++] = c;
        while (isdigit(c = fgetc(source))) {
            token.lexeme[i++] = c;
        }
        ungetc(c, source);
        token.lexeme[i] = '\0';
        token.type = TOKEN_NUMBER;
    } else {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_SYMBOL;
    }
    
    return token;
}

void print_token(Token token) {
    switch (token.type) {
        case TOKEN_KEYWORD:
            printf("Keyword: %s\n", token.lexeme);
            break;
        case TOKEN_IDENTIFIER:
            printf("Identifier: %s\n", token.lexeme);
            break;
        case TOKEN_NUMBER:
            printf("Number: %s\n", token.lexeme);
            break;
        case TOKEN_SYMBOL:
            printf("Symbol: %s\n", token.lexeme);
            break;
        case TOKEN_EOF:
            printf("End of File\n");
            break;
    }
}

int main() {
    FILE *source = fopen("input.txt", "r");
    if (!source) {
        fprintf(stderr, "Could not open input file.\n");
        return 1;
    }
    
    Token token;
    do {
        token = get_next_token(source);
        print_token(token);
    } while (token.type != TOKEN_EOF);
    
    fclose(source);
    return 0;
}

