const char *next_lexeme(const char **input) {
    const char *start = *input;
    while (**input != '\0') {
        switch (**input) {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                if (start != *input) {
                    return strndup(start, *input - start);
                }
                start++;
                (*input)++;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
            case ';':
            case '&':
                if (start != *input) {
                    return strndup(start, *input - start);
                }
                if (**input == '&' && *(*input + 1) == '&') {
                    (*input) += 2;
                    return "&&";
                }
                (*input)++;
                return strndup(start, 1);
            default:
                (*input)++;
        }
    }
    if (start != *input) {
        return strndup(start, *input - start);
    }
    return NULL;
}


int main() {
    const char *filename = "source.c";
    char *source_code = read_source_code(filename);
    if (source_code == NULL) {
        fprintf(stderr, "Error reading source code from '%s'\n", filename);
        return 1;
    }

    const char *input = source_code;
    char *lexeme = next_lexeme(&input);
    while (lexeme != NULL) {
        TokenType token_type;

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
        } else if (strcmp(lexeme, "&") == 0) {
            token_type = TOKEN_SINGLE_AND;
        } else if (strcmp(lexeme, "&&") == 0) {
            token_type = TOKEN_DOUBLE_AND;
        } else {
            token_type = TOKEN_UNKNOWN;
        }

        Token *token = create_token(token_type, lexeme);
        printf("Token { type: %d, lexeme: '%s' }\n", token->type, token->lexeme);
        free_token(token);
        free(lexeme);
        lexeme = next_lexeme(&input);
    }

    free(source_code);
    return 0;
}
