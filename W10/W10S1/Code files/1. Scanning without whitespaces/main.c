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
    const char *pattern = "^(\\+|-|\\*|/|=|==)$";
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
	// Pretend we read this code from a source file
    const char *source_code = "if(condition + 7):{ x = 0 * 5;} \n 1t00 = 1;";
	
	// Preparing a buffer to store my lexemes, one at a time.
	// If lexeme is too long, will cause problems!
    char lexeme_buffer[256] = {0};
    int buffer_index = 0;
	
	// Left to right scan, one character at a time
    for (size_t i = 0; i < strlen(source_code); i++) {
		// Fetch next character from source_code string
        char current_char = source_code[i];
		
		// Check if it is a special character
		// Will return true is the character is a special character or operator
        bool special_char = strchr("(){}[];:,+-=*/", current_char) != NULL;
		
		// If the current character is part of a lexeme (an alphanumeric character or an underscore)
		// or a special character, it is added to the lexeme_buffer.
        if (is_part_of_lexeme(current_char) || special_char) {
            lexeme_buffer[buffer_index++] = current_char;
        }
		
		// If the current character is not part of a lexeme,
		// or if it is the last character in the source_code string,
		// or if it is a special character,
		// then the lexeme is considered complete and ready for processing.
        if (!is_part_of_lexeme(current_char) || i == strlen(source_code) - 1 || special_char) {
			// If the current character is a special character
			// and the lexeme_buffer has more than one character,
			// the buffer index is decremented, and the loop index is also decremented.
			// This allows the special character to be processed separately in the next iteration.
			// (Not the most elegant solution, but it will do for now!)
            if (special_char && buffer_index > 1) {
                buffer_index--;
                i--;
            }
			
			// Terminate the current lexeme with a \0
            lexeme_buffer[buffer_index] = '\0';
			
			// Check lexeme again all types.
			// Keywords have priority over the identifiers
			// while passes the is_identifier() RegEx
			// but should not be considered an identifier!
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
			
			// Not shown, but create Token object with
			// appropriate token type and lexeme as before!
			
			// Reset buffer index to 0 after lexeme has been recognized.
            buffer_index = 0;
        }
    }

    return 0;
}
