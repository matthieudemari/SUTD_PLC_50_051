#include <stdio.h>
#include <string.h>

typedef enum {
    START_STATE,
    VALID_STATE
} State;

int recognize_contains_a(const char *input) {
    State state = START_STATE;
    for (size_t i = 0; i < strlen(input); i++) {
		// State will change if and only if
		// we are in START_STATE and see a character a
        char c = input[i];
        if (state == START_STATE && c == 'a') {
			state = VALID_STATE;
			return 1;
		}
    }
    return 0;
}

int main() {
    // Some test cases
    //const char *input = "a";
    const char *input = "ac";
    //const char *input = "bc";
    if (recognize_contains_a(input)) {
        printf("The input string \"%s\" contains the letter 'a'.\n", input);
    } else {
        printf("The input string \"%s\" does not contain the letter 'a'.\n", input);
    }
    return 0;
}