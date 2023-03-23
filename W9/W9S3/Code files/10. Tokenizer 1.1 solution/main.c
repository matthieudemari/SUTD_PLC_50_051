#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

// Update the TokenType enumeration to include TOKEN_END_OF_LINE
typedef enum {
    TOKEN_KEYWORD_INT,
	TOKEN_KEYWORD_FLOAT,
	TOKEN_KEYWORD_CHAR,
	TOKEN_KEYWORD_CHAR_PTR,
	TOKEN_KEYWORD_WHILE,
	TOKEN_KEYWORD_FOR,
	TOKEN_KEYWORD_IF,
	TOKEN_KEYWORD_RETURN,
    TOKEN_OP_ADD,
    TOKEN_OP_SUBTRACT,
    TOKEN_OP_MULTIPLY,
    TOKEN_OP_DIVIDE,
	TOKEN_OP_EQ,
    TOKEN_PUNCT_LEFT_PAREN,
    TOKEN_PUNCT_RIGHT_PAREN,
    TOKEN_PUNCT_END_OF_LINE,
    TOKEN_OP_SINGLE_AND,
    TOKEN_OP_DOUBLE_AND,
	TOKEN_IDENTIFIER,
	TOKEN_LITERAL_INT,
    TOKEN_LITERAL_FLOAT,
    TOKEN_LITERAL_CHAR,
    TOKEN_LITERAL_STRING,
    TOKEN_UNKNOWN
} TokenType;


// Our Token object
typedef struct {
    TokenType type;
    char *lexeme;
	//int line_number;
} Token;


// Constructor for the Token struct
//Token *create_token(TokenType type, const char *lexeme, int line_number) {
Token *create_token(TokenType type, const char *lexeme) {
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = type;
    token->lexeme = strdup(lexeme);
	//token->line_number = line_number;
    return token;
}


// Destructor for the Token struct
void free_token(Token *token) {
	//free(token->line_number);
    free(token->lexeme);
    free(token);
}


// Read source code
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


// Recognizing keywords using strcmp
// Will now return the corresponding kewyord TokenType that has been
// recognized in case of a match, or TOKEN_UNKNOWN otherwise.
TokenType is_keyword_strcmp(const char *lexeme) {
    const struct {
        const char *lexeme;
        TokenType token_type;
    } keywords[] = {
        {"int", TOKEN_KEYWORD_INT},
		{"float", TOKEN_KEYWORD_FLOAT},
        {"char", TOKEN_KEYWORD_CHAR},
        {"char*", TOKEN_KEYWORD_CHAR_PTR},
        {"while", TOKEN_KEYWORD_WHILE},
        {"for", TOKEN_KEYWORD_FOR},
        {"if", TOKEN_KEYWORD_IF},
        {"return", TOKEN_KEYWORD_RETURN},
        {NULL, TOKEN_UNKNOWN} // Sentinel value
    };

    for (int i = 0; keywords[i].lexeme != NULL; i++) {
        if (strcmp(lexeme, keywords[i].lexeme) == 0) {
            return keywords[i].token_type;
        }
    }
    return TOKEN_UNKNOWN;
}


// Recognizing (unsigned) integer literals using RegEx
bool is_integer_literal_regex(const char *lexeme) {
    const char *pattern = "^(0|[1-9][0-9]*)$";
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }
    result = regexec(&regex, lexeme, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return true;
    }
    return false;
}


// Recognizing float literals using RegEx
bool is_float_literal_regex(const char *lexeme) {
    const char *pattern = "^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$";
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }
    result = regexec(&regex, lexeme, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return true;
    }
    return false;
}


// Recognizing char literals using RegEx
bool is_char_literal_regex(const char *lexeme) {
    const char *pattern = "^'(\\.|[^\\'])'$";
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }
    result = regexec(&regex, lexeme, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return true;
    }
    return false;
}


// Recognizing string literals using RegEx
bool is_string_literal_regex(const char *lexeme) {
    const char *pattern = "^\"(\\.|[^\\\"])*\"$";
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }
    result = regexec(&regex, lexeme, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return true;
    }
    return false;
}


// Recognizing identifiers using RegEx
bool is_identifier_regex(const char *lexeme) {
    const char *pattern = "^[a-zA-Z_]\\w*$";
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }
    result = regexec(&regex, lexeme, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return true;
    }
    return false;
}

// Tokenizer v1.2
// Almost same main() as before
int main() {
	// Load source code from file 
    // For testing, will put code string in source_code string directly (simpler).
    // You can uncomment/comment things as needed, if you want to play with a source.c file instead.
    /*
    const char *filename = "source.c";
    char *source_code = read_source_code(filename);
    if (source_code == NULL) {
        fprintf(stderr, "Error reading source code from '%s'\n", filename);
        return 1;
    }
    */
    char *source_code = strdup("int x = 7 float 2.5e-1 char 'a' char* \"hello\" ; \n while ( for ) if return 1t0 + - * / & &&");
    
	// Splitting will have to be reworked to include line_tracking!
	// (Missing feature at the moment)
	//int line_number = 0
	char *lexeme = strtok(source_code, " \t\n\r");
	
	// Token stream definition
	Token **token_stream = NULL;
    size_t token_count = 0;
	
	// Classify lexemes, has been reworked to include more token types
    while (lexeme != NULL) {
        TokenType token_type;
		
        // Now covering lots of possible token types!
        // But to be honest there are many many more!
        if (is_keyword_strcmp(lexeme) != TOKEN_UNKNOWN) {
            token_type = is_keyword_strcmp(lexeme);
        } else if (strcmp(lexeme, "+") == 0) {
            token_type = TOKEN_OP_ADD;
        } else if (strcmp(lexeme, "-") == 0) {
            token_type = TOKEN_OP_SUBTRACT;
        } else if (strcmp(lexeme, "*") == 0) {
            token_type = TOKEN_OP_MULTIPLY;
        } else if (strcmp(lexeme, "/") == 0) {
            token_type = TOKEN_OP_DIVIDE;
        } else if (strcmp(lexeme, "(") == 0) {
            token_type = TOKEN_PUNCT_LEFT_PAREN;
        } else if (strcmp(lexeme, "=") == 0) {
            token_type = TOKEN_OP_EQ;
		} else if (strcmp(lexeme, ")") == 0) {
            token_type = TOKEN_PUNCT_RIGHT_PAREN;
        } else if (strcmp(lexeme, ";") == 0) {
            token_type = TOKEN_PUNCT_END_OF_LINE;
        } else if (strcmp(lexeme, "&") == 0) {
            token_type = TOKEN_OP_SINGLE_AND;
        } else if (strcmp(lexeme, "&&") == 0) {
            token_type = TOKEN_OP_DOUBLE_AND;
        } else if (is_identifier_regex(lexeme)) {
            token_type = TOKEN_IDENTIFIER;
        } else if (is_integer_literal_regex(lexeme)) {
            token_type = TOKEN_LITERAL_INT;
        } else if (is_float_literal_regex(lexeme)) {
            token_type = TOKEN_LITERAL_FLOAT;
        } else if (is_char_literal_regex(lexeme)) {
            token_type = TOKEN_LITERAL_CHAR;
        } else if (is_string_literal_regex(lexeme)) {
            token_type = TOKEN_LITERAL_STRING;
        } else {
            token_type = TOKEN_UNKNOWN;
        }

        //Token *token = create_token(token_type, lexeme, line_number);
		Token *token = create_token(token_type, lexeme);
		
		 // Resize the token stream and add the new token
        token_stream = (Token **)realloc(token_stream, (token_count + 1) * sizeof(Token *));
        token_stream[token_count] = token;
        token_count++;
        printf("Token { type: %d, lexeme: '%s' }\n", token->type, token->lexeme);
        lexeme = strtok(NULL, " \t\n\r");
    }
	
	// Check valid token stream and display error messages if any
	
	// Free tokens in the token stream and free the token stream
    for (size_t i = 0; i < token_count; i++) {
        free_token(token_stream[i]);
    }
    free(token_stream);

	// Free source code string
    free(source_code);
	

    return 0;
}
