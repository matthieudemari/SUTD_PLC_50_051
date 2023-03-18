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


// Same read source code functions as before
char* read_source_code(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);  
    long file_size = ftell(file);
    rewind(file);
    char *source_code = (char *)malloc((file_size + 1) * sizeof(char));
    if (source_code == NULL) {
        fprintf(stderr, "Error allocating memory for source code\n");
        exit(EXIT_FAILURE);
    }
    size_t read_size = fread(source_code, sizeof(char), file_size, file);
    source_code[read_size] = '\0';
    fclose(file);
    return source_code;
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
    // Read the source code from the file
    const char *filename = "source.c";
    char *source_code = read_source_code(filename);
    if (source_code == NULL) {
        fprintf(stderr, "Error reading source code from '%s'\n", filename);
        return 1;
    }

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

    // Free the memory allocated for the source code
    free(source_code);

    return 0;
}