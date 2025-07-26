#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

// Update the TokenType enumeration to include TOKEN_END_OF_LINE
typedef enum {
    TOKEN_KEYWORD,
	...
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


// Destructor for the Token struct
void free_token(Token *token) {
    free(token->lexeme);
    free(token);
}


// Read source code
char* read_source_code(const char *filename) {
    ...
}


// Recognizing keywords using strcmp
TokenType is_keyword_strcmp(const char *lexeme) {
    ...
}


// Recognizing (unsigned) integer literals using RegEx
bool is_integer_literal_regex(const char *lexeme) {
    ...
}


// Recognizing identifiers using RegEx
bool is_identifier_regex(const char *lexeme) {
    ...
}

// Tokenizer v1.1
// Almost same main() as before
int main() {
	// Load source code from file 
	...
    
	// Splitting source code into lexemes
	...
	
	// Token stream definition
	...
	
	// Classify lexemes, has been reworked to include more token types
    while (...) {
        ...
		
		if(...) {
			...
		else if (...) {
				...
		}	
		}
    }
	
	// Free tokens in the token stream and free the token stream
    ...

	// Free source code string
    ...

    return 0;
}
