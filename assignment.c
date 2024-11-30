#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// Function to check if a string represents a positive integer
// This ensures that arguments like "123" are valid, but "abc" or "-5" are not
int is_positive_integer(const char *str) {
    while (*str) { // Loop through each character in the string
        if (!isdigit(*str)) return 0; // If it's not a digit, it's not a positive integer
        str++;
    }
    return 1; // If we made it here, the string is a positive integer
}

int main(int argc, char *argv[]) {
    // initialize random number generator
    
    srand(time(NULL));
    int minrand = 1;   // The smallest random number we can generate
    int maxrand = 100; // The largest random number we can generate

    // WRITE YOUR CODE HERE

    //  Check if the user provided the correct number of arguments
    if (argc != 3) {
        // If there aren't exactly 2 additional arguments, print an error and exit
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1; // Exit with an error code
    }

    //  Validate that the arguments are positive integers
    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2])) {
        // If either argument is not a positive integer, print an error and exit
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Convert the arguments to integers
    int rows = atoi(argv[1]); // Convert the first argument to the number of rows
    int cols = atoi(argv[2]); // Convert the second argument to the number of columns

    // Extra check: Make sure the rows and columns are greater than 0 (just in case)
    if (rows <= 0 || cols <= 0) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    //  Dynamically allocate memory for the matrix
    // We're creating a 2D array of integers with 'rows' rows and 'cols' columns
    int **matrix = malloc(rows * sizeof(int *)); // Allocate memory for the rows
    if (!matrix) { // Check if the allocation failed
        perror("Failed to allocate memory for rows");
        return 1;
    }

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int)); // Allocate memory for the columns in each row
        if (!matrix[i]) { // Check if the allocation failed
            perror("Failed to allocate memory for columns");
            return 1;
        }
    }

    //  Fill the matrix with random integers
    // We'll populate each cell with a random number between 1 and 100
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = minrand + rand() % (maxrand - minrand + 1); // Generate a random number
        }
    }

    //  Write the matrix to a file
    // Open the file "matrix.txt" for writing
    FILE *file = fopen("matrix.txt", "w");
    if (!file) { // Check if the file couldn't be opened
        perror("Failed to open file for writing");
        return 1;
    }

    // Write the matrix to the file
    // Each row is written on a separate line, with numbers separated by spaces
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]); // Write the number
            if (j < cols - 1) fprintf(file, " "); // Add a space between numbers, but not at the end of the line
        }
        fprintf(file, "\n"); // Add a newline at the end of each row
    }
    fclose(file); // Close the file when we're done

    
    // Free all the memory we allocated earlier to avoid memory leaks
    for (int i = 0; i < rows; i++) {
        free(matrix[i]); // Free each row
    }
    free(matrix); // Free the array of row pointers

    return 0; // # return 0 to indicate that it woked
    
}
