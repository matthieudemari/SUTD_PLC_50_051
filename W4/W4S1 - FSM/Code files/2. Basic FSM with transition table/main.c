#include <stdio.h>

// Define possible states as an enum
typedef enum {
    START,
    EVEN,
    ODD
} State;


// Define our FSM object, it has only one
// attribute of interest, its current state.
typedef struct {
    State current_state;
} FSM;


// Define our transition table for new states
// 3 states (START, EVEN, ODD) and two actions (0, 1)
const State transition_table[3][2] = {
    // 0    1
    {EVEN, ODD}, // START
    {EVEN, ODD}, // EVEN
    {EVEN, ODD}  // ODD
};


// Define our FSM transition function.
void update_state(FSM *f, int input) {
    // Get the current state from the FSM object
    State current_state = f->current_state;

    // Look up the next state based on the current state and input
    State next_state = transition_table[current_state][input];

    // Update the FSM object with the new state
    f->current_state = next_state;

    // Print the new state
    if (next_state == EVEN) {
        printf("New state is even.\n");
    } else if (next_state == ODD) {
        printf("New state is odd.\n");
    }
}


// Main
int main() {
    // Initialize FSM
    FSM f = {START};
    
    // Decimal representation of an int (our input)
    int input[] = {1, 0, 1, 1, 0};
    
    // Run for loop on each character of our input
    int n = sizeof(input) / sizeof(input[0]);
    for (int i = 0; i < n; i++) {
        // Update state for each possible input value
        update_state(&f, input[i]);
    }
    
    // Final display
    switch (f.current_state) {
        case EVEN:
            printf("Our final state tells us the number is even.\n");
            break;
        case ODD:
            printf("Our final state tells us the number is odd.\n");
            break;
        default:
            break;
    }
    
    // End
    return 0;
}