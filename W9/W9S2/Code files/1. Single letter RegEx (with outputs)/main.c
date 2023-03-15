#include <stdio.h>
#include <string.h>

typedef enum {
    START_STATE,
    ACCEPTING_STATE
} State;

int recognize_single_a(const char *input) {
    State state = START_STATE;
    for (size_t i = 0; i < strlen(input); i++) {
        char c = input[i];
        switch (state) {
            case START_STATE:
                if (c == 'a') {
                    state = ACCEPTING_STATE;
                } else {
                    return 0;
                }
                break;
            case ACCEPTING_STATE:
                return 0;
        }
    }
    return state == ACCEPTING_STATE;
}

int main() {
    const char *input = "a";
    //const char *input = "ca";
    //const char *input = "bca";
    if (recognize_single_a(input)) {
        printf("The input string \"%s\" consists of the single letter 'a'.\n", input);
    } else {
        printf("The input string \"%s\" does not consist of the single letter 'a'.\n", input);
    }
    return 0;
}
