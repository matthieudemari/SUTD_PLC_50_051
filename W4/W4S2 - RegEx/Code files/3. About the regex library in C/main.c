#include <stdio.h>
#include <regex.h>

int main() {
	// Input string
    char* string = "The quick brown fox jumps over the lazy dog";
	// RegEx definition
    char* pattern = "[A-Z+]";
	
	// Initialize RegEx variable to hold RegEx object
    regex_t regex;

    // Compile the regular expression pattern
	// Will generate the FSM according to given RegEx
    int status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        printf("Error compiling regex pattern.\n");
        return 1;
    }

    // Match the compiled pattern against the string
	// Using the FSM to check if input string is acceptable or not!
    status = regexec(&regex, string, 0, NULL, 0);
    if (status == 0) {
        printf("Pattern matched!\n");
    } else if (status == REG_NOMATCH) {
        printf("Pattern not matched.\n");
    } else {
        printf("Error matching pattern.\n");
        return 1;
    }

    // Free the memory used by the regex
    regfree(&regex);

    return 0;
}
