#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

// Recognizing integer literals using RegEx
bool is_integer_literal_regex(const char *lexeme) {
    // Define a regular expression pattern for integer literals
    // Integer literals are a sequence of digits without leading zeros.
    const char *pattern = "^(0|[1-9][0-9]*)$";

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
    const char *lexemes[] = {"42", "12345", "00123", "0", "1notinteger", NULL};

    // Iterate through the lexemes and test the is_integer_literal_regex() function
    for (int i = 0; lexemes[i] != NULL; i++) {
        const char *lexeme = lexemes[i];

        // Check if the lexeme is an integer literal using is_integer_literal_regex()
        bool is_integer = is_integer_literal_regex(lexeme);

        // Print the results
        printf("Lexeme '%s':\n", lexeme);
        printf("  is_integer_literal_regex:  %s\n", is_integer ? "true" : "false");
    }

    return 0;
}
