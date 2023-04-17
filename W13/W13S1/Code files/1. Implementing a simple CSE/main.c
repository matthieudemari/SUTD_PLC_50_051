
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a dictionary-kind of structure
// to hold expressions and corresponding variables
typedef struct {
    char expression[20];
    char variable[20];
} CSETable;

// Function to search if an expression already appears in the CSE table
// Will return index i if found; and -1 otherwise.
int find_expression(CSETable *table, int table_size, const char *expression) {
    for (int i = 0; i < table_size; ++i) {
        if (strcmp(table[i].expression, expression) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to optimize a basic block using the CSE technique
void optimize_cse(const char *block[], int block_size) {
    CSETable cse_table[block_size];
    int table_size = 0;
    char lhs[20], rhs[20];

    // Iterate through the statements in the basic block
    for (int i = 0; i < block_size; ++i) {
        // Extract the left-hand side and right-hand side of the statement
        sscanf(block[i], "%[^=] = %[^\n]", lhs, rhs);
        // Check if the expression is present in the CSE table
        int index = find_expression(cse_table, table_size, rhs);
        if (index != -1) {
            // If the expression is found, print the optimized statement
            printf("%s = %s\n", lhs, cse_table[index].variable);
        } else {
            // If the expression is not found, add it to the CSE table
            strcpy(cse_table[table_size].expression, rhs);
            strcpy(cse_table[table_size].variable, lhs);
            // Print the original statement
            printf("%s\n", block[i]);
            // Increment the table size
            ++table_size;
        }
    }
}

int main() {
    // Define a basic block as an array of strings for testing
    const char *block[] = {
        "x = a + b",
        "y = a * c",
        "z = a + b",
        "w = a * c",
        "t = x + z"
    };
    int block_size = sizeof(block) / sizeof(block[0]);
    // Optimize the basic block using the CSE technique
    optimize_cse(block, block_size);
    return 0;
}



