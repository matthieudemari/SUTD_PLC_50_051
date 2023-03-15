#include <stdio.h>
#include <string.h>

// Possible states
typedef enum {
    NO_ZERO_STATE,
    ONE_ZERO_STATE,
    TWO_ZERO_STATE
} State;


// Define our FSM object, it has only one
// attribute of interest, its current state.
typedef struct {
    State current_state;
} FSM;


// Define transition function updating the FSM state
// Following the logic of the FSM.
void transition(FSM *fsm, char input) {
    switch (fsm->current_state) {
        case NO_ZERO_STATE:
            if (input == '0') {
                fsm->current_state = ONE_ZERO_STATE;
            }
            break;
        case ONE_ZERO_STATE:
            if (input == '0') {
                fsm->current_state = TWO_ZERO_STATE;
            } else {
                fsm->current_state = NO_ZERO_STATE;
            }
            break;
        case TWO_ZERO_STATE:
            break;
    }
}


// Repeat for every binary character, start in the NO_ZERO_STATE state.
// Return 1 if two successive zeroes are found, 0 otherwise.
int has_two_successive_zeroes(FSM *fsm, const char *binary) {
    fsm->current_state = NO_ZERO_STATE;
    for (size_t i = 0; i < strlen(binary); i++) {
        transition(fsm, binary[i]);
        if (fsm->current_state == TWO_ZERO_STATE) {
            return 1;
        }
    }
    return 0;
}


// Main
int main() {
    // Ask user to enter a number (64-bit + null terminator)
    char binary_input[65]; 
    printf("Enter a binary number: ");
    scanf("%64s", binary_input);

    // Create an instance of the FSM
    FSM fsm;

    // Check for two successive zeroes and display print accordingly
    if (has_two_successive_zeroes(&fsm, binary_input)) {
        printf("The binary number has two successive zeroes.\n");
    } else {
        printf("The binary number does not have two successive zeroes.\n");
    }

    return 0;
}
