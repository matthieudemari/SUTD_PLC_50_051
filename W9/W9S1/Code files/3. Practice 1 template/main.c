#include <stdio.h>
#include <string.h>

// Possible states
typedef enum {
    ...
} State;


// Define our FSM object, it has only one
// attribute of interest, its current state.
typedef struct {
    State current_state;
} FSM;


// Define transition function updating the FSM state
// Following the logic of the FSM.
// (Can use a transition table of an if/else statement as you prefer
void transition(FSM *fsm, char input) {
    ...
}


// Repeat for every binary character, start in EVEN state.
// Return 0 if odd number of zeroes and 1 otherwise.
int has_even_zeroes(FSM *fsm, const char *binary) {
    fsm->current_state = ...
    for (...) {
        ...
    }
    return ...
}


// Main
int main() {
    // Ask user to enter a number (64-bit + null terminator)
    char binary_input[65]; 
    printf("Enter a binary number: ");
    scanf("%64s", binary_input);

    // Create an instance of the FSM
    FSM fsm;

    // Check for even number of zeroes and display print accordingly
    if (...) {
        printf("The binary number has an even number of zeroes.\n");
    } else {
        printf("The binary number has an odd number of zeroes.\n");
    }

    return 0;
}
