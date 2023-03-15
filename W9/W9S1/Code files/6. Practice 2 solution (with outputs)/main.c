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
// Technically, the produced output
// could also have been an attribute.
// (Leaving it as extra practice for you!)
typedef struct {
    State current_state;
} FSM;


// Define transition function updating the FSM state
// Following the logic of the FSM. Returns the output
// for the given input and state combination.
int transition(FSM *fsm, char input) {
	
	// By default output will match the input
    int output = (input == '0') ? 0 : 1;
    switch (fsm->current_state) {
        case NO_ZERO_STATE:
            if (input == '0') {
				// Move to ONE_ZERO if input is 0, otherwise stay
                fsm->current_state = ONE_ZERO_STATE;
            }
            break;
        case ONE_ZERO_STATE:
			// Move to TWO_ZERO if input is 0, otherwise back to NO_ZERO
            if (input == '0') {
                fsm->current_state = TWO_ZERO_STATE;
                return -1; // Returning -1 to signal an "OK" state
            } else {
                fsm->current_state = NO_ZERO_STATE;
            }
            break;
        case TWO_ZERO_STATE:
            break;
    }
    return output;
}


// Process the FSM with a for loop as before.
void process_binary(FSM *fsm, const char *binary) {
	// Start on NO_ZERO state.
    fsm->current_state = NO_ZERO_STATE;
	// Initialize output
    int output;
	
	// For loop as before
    for (size_t i = 0; i < strlen(binary); i++) {
        output = transition(fsm, binary[i]);
        if (output == -1) {
			// Early break if "OK" state, i.e. output is -1.
			printf("OK\n");
            break;
        }
        printf("%d\n", output);
    }
}


// Main
int main() {
	// Ask user for input string
    char binary_input[65];
    printf("Enter a binary number: ");
    scanf("%64s", binary_input);
	
	// FSM is go
    FSM fsm;
    process_binary(&fsm, binary_input);

    // Final print, showing whether the number has two successive zeroes or not
    if (fsm.current_state == TWO_ZERO_STATE) {
        printf("The number has two successive zeroes.\n");
    } else {
        printf("The number does not have two successive zeroes.\n");
    }

    return 0;
}
