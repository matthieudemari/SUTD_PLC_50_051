#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>


// Recognizing keywords using RegEx
bool is_keyword_regex(const char *lexeme) {
    // Define a regular expression pattern for the predefined keywords
	// Using the | operator to list keywords here, adding the start ^ and $
	// to enforce the fact that there should be no other characters.
    const char *pattern = "^(int|while|for|if|return)$";

    // Define and compile the regular expression
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
	
	// If there is an error compiling the regular expression, return false
    if (result != 0) {
        return false;
    }

    // Match the lexeme against the regular expression
    result = regexec(&regex, lexeme, 0, NULL, 0);

    // Free the memory allocated for the regular expression
    regfree(&regex);

    // If the lexeme matches the regular expression, return true
    if (result == 0) {
        return true;
    }

    // Otherwise, return false
    return false;
}


// Recognizing keywords using strcmp
bool is_keyword_strcmp(const char *lexeme) {
    // List of predefined keywords
    const char *keywords[] = {"int", "while", "for", "if", "return", NULL};

    // Iterate through the keywords
    for (int i = 0; keywords[i] != NULL; i++) {
        // Compare the lexeme with the current keyword using strcmp()
        if (strcmp(lexeme, keywords[i]) == 0) {
            // If the lexeme matches the keyword, return true
            return true;
        }
    }

    // If no keyword matches the lexeme, return false
    return false;
}


// Testing both functions
int main() {
    // Array of lexemes to test
    const char *lexemes[] = {"int", "while", "for", "if", "return", "intwhile", NULL};

    // Iterate through the lexemes and test both is_keyword_strcmp() and is_keyword_regex() functions
    for (int i = 0; lexemes[i] != NULL; i++) {
        const char *lexeme = lexemes[i];

        // Check if the lexeme is a keyword using is_keyword_strcmp()
        bool is_keyword_with_strcmp = is_keyword_strcmp(lexeme);

        // Check if the lexeme is a keyword using is_keyword_regex()
        bool is_keyword_with_regex = is_keyword_regex(lexeme);

        // Print the results
        printf("Lexeme '%s':\n", lexeme);
        printf("  is_keyword_strcmp: %s\n", is_keyword_with_strcmp ? "true" : "false");
        printf("  is_keyword_regex:  %s\n", is_keyword_with_regex ? "true" : "false");
    }

    return 0;
}
