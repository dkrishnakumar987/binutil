#include <ctype.h> // for isprint
#include <stdio.h>
#include <string.h> // for strlen
#include <unistd.h>

#define PROJECT_NAME "binutil"

int count_ascii_characters(const char *str) {
    int cnt = 0;
    while (*str) {
        if (isprint((unsigned char)*str)) {
            cnt++; // Count the printable ASCII characters
        }
        str++;
    }
    return cnt;
}

int main(int argc, char *argv[]) {
    int total_count = 0;
    char buffer[1024];
    // If there are no arguments and no pipelined input, print and exit
    if (argc == 1) {
        // Check if there is any input on stdin
        if (isatty(fileno(stdin))) {
            printf("No input provided. Exiting...\n");
            return 1;
        }
    }

    // Add count from stdin
    if (!isatty(fileno(stdin)) &&
        fgets(buffer, sizeof(buffer), stdin) != NULL) {
        total_count += count_ascii_characters(buffer);
    }

    // Process command-line arguments (if provided)
    for (int i = 1; i < argc; i++) {
        total_count += count_ascii_characters(argv[i]);
    }

    // Print the final result
    if (total_count > 0) {
        printf("Total ASCII characters: %d\n", total_count);
    } else {
        printf("No ASCII characters found.\n");
    }

    return 0;
}
