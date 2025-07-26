#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>


// Our Token types
typedef enum {
    TOKEN_KEYWORD,
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


int main() {
    // Pretend we have read the source code from the file using
    // const char *filename = "source.c";
    // char *source_code = read_source_code(filename);
    //if (source_code == NULL) {
    //    fprintf(stderr, "Error reading source code from '%s'\n", filename);
    //    return 1;
    //}
	char *source_code = (char*) malloc(100*sizeof(char));
    if(source_code == NULL)
    {
        printf("Memory allocation failed!");
        return 1;
    }
    strcpy(source_code, "int while for if return intwhile");

    // Tokenize the source code into lexemes
    char *lexeme = strtok(source_code, " \t\n\r");
    while (lexeme != NULL) {
        // Check if the lexeme is a keyword using is_keyword_strcmp()
        bool is_keyword = is_keyword_strcmp(lexeme);

        // Create a token for the lexeme
        TokenType token_type = is_keyword ? TOKEN_KEYWORD : TOKEN_UNKNOWN;
        Token *token = create_token(token_type, lexeme);

        // Print the token information
        printf("Token { type: %d, lexeme: '%s' }\n", token->type, token->lexeme);

        // Free the memory allocated for the token
        free_token(token);

        // Move to the next lexeme
        lexeme = strtok(NULL, " \t\n\r");
    }
	
	// Free source_code string
	free(source_code);
	
    return 0;
}