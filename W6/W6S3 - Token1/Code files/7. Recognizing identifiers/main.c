#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>


// Recognizing identifiers using RegEx
bool is_identifier_regex(const char *lexeme) {
    // Define a regular expression pattern for identifiers
    // Identifiers start with a letter or an underscore, followed by any
    // combination of letters, digits, or underscores.
    const char *pattern = "^[a-zA-Z_]\\w*$";

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


// Testing the function
int main() {
    // Array of lexemes to test
    const char *lexemes[] = {"_identifier", "variable", "Int", "123invalid", "valid123", "with_underscore", "a0?", NULL};

    // Iterate through the lexemes and test the is_identifier_regex() function
    for (int i = 0; lexemes[i] != NULL; i++) {
        const char *lexeme = lexemes[i];

        // Check if the lexeme is an identifier using is_identifier_regex()
        bool is_identifier_with_regex = is_identifier_regex(lexeme);

        // Print the results
        printf("Lexeme '%s':\n", lexeme);
        printf("  is_identifier_regex:  %s\n", is_identifier_with_regex ? "true" : "false");
    }

    return 0;
}
