#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>


// Update the TokenType enumeration
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_ADD,          // The '+' operator
    TOKEN_SUBTRACT,     // The '-' operator
    TOKEN_MULTIPLY,     // The '*' operator
    TOKEN_DIVIDE,       // The '/' operator
    TOKEN_LEFT_PAREN,   // The '(' character
    TOKEN_RIGHT_PAREN,  // The ')' character
    TOKEN_END_OF_LINE,  // The ';' character
    TOKEN_UNKNOWN
} TokenType;


// Our Token object
typedef struct {
    TokenType type;
    char *lexeme;
} Token;


// Constructor for the Token struct
Token *create_token(TokenType type, const char *lexeme) {
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = type;
    token->lexeme = strdup(lexeme);
    return token;
}


// Desctructor for the Token struct
void free_token(Token *token) {
    free(token->lexeme);
    free(token);
}


// Same function recognizing keywords using strcmp
bool is_keyword_strcmp(const char *lexeme) {
    const char *keywords[] = {"int", "while", "for", "if", "return", NULL};
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(lexeme, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}


// Almost same main() as before
int main() {
    char *source_code = (char*) malloc(100*sizeof(char));
    if(source_code == NULL)
    {
        printf("Memory allocation failed!");
        return 1;
    }
    strcpy(source_code, "int + / for while return ;\n* - if ;");

    char *lexeme = strtok(source_code, " \t\n\r");
    while (lexeme != NULL) {
        TokenType token_type;
		
		// Now covering lots of possible token types!
		// But to be honest there are many many more!
        if (is_keyword_strcmp(lexeme)) {
            token_type = TOKEN_KEYWORD;
        } else if (strcmp(lexeme, "+") == 0) {
            token_type = TOKEN_ADD;
        } else if (strcmp(lexeme, "-") == 0) {
            token_type = TOKEN_SUBTRACT;
        } else if (strcmp(lexeme, "*") == 0) {
            token_type = TOKEN_MULTIPLY;
        } else if (strcmp(lexeme, "/") == 0) {
            token_type = TOKEN_DIVIDE;
        } else if (strcmp(lexeme, "(") == 0) {
            token_type = TOKEN_LEFT_PAREN;
        } else if (strcmp(lexeme, ")") == 0) {
            token_type = TOKEN_RIGHT_PAREN;
        } else if (strcmp(lexeme, ";") == 0) {
            token_type = TOKEN_END_OF_LINE;
        } else {
            token_type = TOKEN_UNKNOWN;
        }

        Token *token = create_token(token_type, lexeme);
        printf("Token { type: %d, lexeme: '%s' }\n", token->type, token->lexeme);
        free_token(token);
        lexeme = strtok(NULL, " \t\n\r");
    }

    free(source_code);

    return 0;
}