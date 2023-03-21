#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>


// General Regex match function
bool regex_match(const char *pattern, const char *lexeme) {
	// Define RegEx and compile expression, as before
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
	
	// Check if compilation of RegEx failed
    if (result != 0) {
        return false;
    }
	
	// Match input string with given RegEx
    result = regexec(&regex, lexeme, 0, NULL, 0);
	
	// Free RegEx after using it
    regfree(&regex);
	
	// Result
    return result == 0;
}


// Define functions for matching token types
// (Using RegEx for all of them, for simplicity)
// Recognizing some keywords using RegEx
bool is_keyword(const char *lexeme) {
	// Checking for exact match on some keywords using RegEx
    const char *pattern = "^(if|while|for|return)$";
    return regex_match(pattern, lexeme);
	
}


// Recognizing some operators using RegEx
bool is_operator(const char *lexeme) {
	// Checking for exact match using RegEx, again
    const char *pattern = "^(\\+|-|\\*|/|=)$";
    return regex_match(pattern, lexeme);
}


// Recognizing some punctuation signs using RegEx
bool is_punctuation(const char *lexeme) {
	// Checking for exact match using RegEx, again
	// Will check (, ), [, ], {, }, semicolons, colons, commas.
    const char *pattern = "^(\\(|\\)|\\[|\\]|\\{|\\}|;|:|,)$";
    return regex_match(pattern, lexeme);
}


// Recognizing identifiers using RegEx
bool is_identifier(const char *lexeme) {
	// Checking for string match on identifier as discussed in class
    const char *pattern = "^[a-zA-Z_][a-zA-Z0-9_]*$";
    return regex_match(pattern, lexeme);
}


// Recognizing some literals using RegEx
// In practice we would probably do is_literal_int, is_literal_char, etc.
bool is_literal(const char *lexeme) {
	// Checking for string match on literals as discussed in class
	// Covered types: unsigned int only
    const char *integer_pattern = "^(0|[1-9][0-9]*)$";
    return regex_match(integer_pattern, lexeme);
}


// Function to check if the character is part of a lexeme
// We will add the next character being scanned c, to the current lexeme
// if it is alphanumerical, an underscore or a dot
// Dot is only here for floats, but is not that dangerous?
bool is_part_of_lexeme(char c) {
    return isalnum(c) || c == '_';
}


// Trying it out
int main() {
    const char *source_code = "if(condition=7):{ x = 0 * 5;} \n 1t00 = 1;";

    char lexeme_buffer[256] = {0};
    int buffer_index = 0;

    size_t code_length = strlen(source_code);

    for (size_t i = 0; i < code_length; i++) {
		
		if (isspace(source_code[i])) {
            continue;
        }
		
        lexeme_buffer[buffer_index++] = source_code[i];
        lexeme_buffer[buffer_index] = '\0';

        bool valid_token = is_keyword(lexeme_buffer) || is_operator(lexeme_buffer) || is_punctuation(lexeme_buffer) || is_identifier(lexeme_buffer) || is_literal(lexeme_buffer);

        if (!valid_token || i == code_length - 1) {
            if (!valid_token) {
                buffer_index--;
                lexeme_buffer[buffer_index] = '\0';
            }

            if (is_keyword(lexeme_buffer)) {
                printf("Keyword Token: %s\n", lexeme_buffer);
            } else if (is_operator(lexeme_buffer)) {
                printf("Operator Token: %s\n", lexeme_buffer);
            } else if (is_punctuation(lexeme_buffer)) {
                printf("Punctuation Token: %s\n", lexeme_buffer);
            } else if (is_identifier(lexeme_buffer)) {
                printf("Identifier Token: %s\n", lexeme_buffer);
            } else if (is_literal(lexeme_buffer)) {
                printf("Literal Token: %s\n", lexeme_buffer);
            } else if (strlen(lexeme_buffer) > 0) {
                printf("Unknown Token: %s\n", lexeme_buffer);
            }

            buffer_index = 0;
            if (!valid_token) {
                i--; // Re-process the current character
            }
        }
    }

    return 0;
}