#include <stdio.h>
#include <stdlib.h>

char* read_source_code(const char *filename) {
    // Open the file in filename, in read mode
	// Check for opening errors
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Move the file position indicator to the end of the file
	// And get the current file position (which is the size of the file)
    fseek(file, 0, SEEK_END);  
    long file_size = ftell(file);

    // Now that we know the length of the file,
	// Rewind the file position indicator back to the beginning of the file
    rewind(file);

    // Allocate memory for the source code string
	// (file_size + 1 for the null-terminator)
    char *source_code = (char *)malloc((file_size + 1) * sizeof(char));
    if (source_code == NULL) {
        fprintf(stderr, "Error allocating memory for source code\n");
        exit(EXIT_FAILURE);
    }

    // Read the content of the file into the source_code string
    size_t read_size = fread(source_code, sizeof(char), file_size, file);

    // Add a null-terminator at the end of the source_code string
    source_code[read_size] = '\0';

    // Close the file
    fclose(file);

    // Return the source_code string as output
    return source_code;
}

int main() {
    // Specify the filename where the source code is
    const char *filename = "source.c";

    // Call the read_source_code() function to read the content of the file into a string
    char *source_code = read_source_code(filename);

    // Print the content of the source_code string
    printf("Source code content:\n%s\n", source_code);

    // Free the memory allocated for the source_code string
    free(source_code);

	// ENd
    return 0;
}