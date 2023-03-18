#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Let us list the different types of tokens as an enum first
// TOKEN_KEYWORD = 0, for keywords, e.g. int, while, for, if, etc.
// TOKEN_IDENTIFIER = 1, for variables and functions names, e.g. x, my_function, etc.
// TOKEN_NUMBER = 2, for numerical values to be assigned to int variables, e.g. 0, 1, 1023.
// TOKEN_OPERATOR = 3, for operators, e.g. +, *, =, etc.
// TOKEN_UNKNOWN = 4, for any lexemes that does not seem to fall in any category, e.g. ???, 0ab54df, etc.
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN
} TokenType;


// Our Token object, consisting of a TokenType and a lexeme
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


// Main, demonstrating how Token will look like
int main() {
    // Create an array of sample lexemes for each token type
    const char *sample_lexemes[] = {
		"int",           // TOKEN_KEYWORD
        "variable_name", // TOKEN_IDENTIFIER
        "42",            // TOKEN_NUMBER
        "+",             // TOKEN_OPERATOR
        "",              // TOKEN_END_OF_FILE
        "???"            // TOKEN_UNKNOWN
    };

    // Iterate through the TokenType enum and create tokens using the sample lexemes
    for (int i = 0; i <= TOKEN_UNKNOWN; i++) {
		// Fetch token type and lexeme
        TokenType type = (TokenType)i;
        const char *lexeme = sample_lexemes[i];
		
		// Create token object
        Token *token = create_token(type, lexeme);
		
		// Display it
        printf("Token: Type = %d, Lexeme = '%s'\n", token->type, token->lexeme);
		
		// Free token object
        free_token(token);
    }
	
	// End
    return 0;
}