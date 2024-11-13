#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10];

// Function declarations
void follow(char c);
void first(char c);

int main() {
    int i, z;
    char c, ch;

    printf("Enter the number of productions: \n");
    scanf("%d", &n);

    printf("Enter the productions:\n");
    for (i = 0; i < n; i++) {
        scanf("%s%c", a[i], &ch); // Read production and ignore newline
    }

    do {
        m = 0;
        printf("Enter a variable whose First & Follow is to be found: ");
        scanf(" %c", &c); 

        // Calculate and print First set
        first(c);
        printf("First(%c) = {", c);
        for (i = 0; i < m; i++) {
            printf("%c", f[i]);
            if (i < m - 1) printf(", ");
        }
        printf("}\n");

        // Reset the array for Follow calculation
        strcpy(f, " ");
        m = 0;

        // Calculate and print Follow set
        follow(c);
        printf("Follow(%c) = {", c);
        for (i = 0; i < m; i++) {
            printf("%c", f[i]);
            if (i < m - 1) printf(", ");
        }
        printf("}\n");

        printf("Want to continue or not (1/0)? ");
        scanf("%d%c", &z, &ch); 
    } while (z == 1);

    return 0;
}

// Function to compute the First set
void first(char c) {
    int k;

    // If 'c' is a terminal, add it to the First set
    if (!isupper(c)) {
        f[m++] = c;
        return;
    }

    // Iterate over all productions to find those that begin with 'c'
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            // If the production contains epsilon (represented by '$')
            if (a[k][2] == '$') {
                follow(a[k][0]); // Add FOLLOW of the LHS non-terminal
            }
            // If the next symbol is a terminal, add it to First set
            else if (islower(a[k][2])) {
                f[m++] = a[k][2];
            }
            // If the next symbol is non-terminal, recursively find its First
            else {
                first(a[k][2]);
            }
        }
    }
}

// Function to compute the Follow set
void follow(char c) {
    // If 'c' is the start symbol, add '$' to its Follow set
    if (a[0][0] == c) {
        f[m++] = '$';
    }

    // Iterate over all productions to find occurrences of 'c'
    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                // Case 1: If there is a symbol after 'c'
                if (a[i][j + 1] != '\0') {
                    char nextSymbol = a[i][j + 1];

                    // If the next symbol is a terminal, add it to Follow set
                    if (islower(nextSymbol)) {
                        f[m++] = nextSymbol;
                    }
                    // If the next symbol is non-terminal, add its First set
                    else {
                        first(nextSymbol);

                        // Handle epsilon in the First set
                        for (int k = 0; k < m; k++) {
                            if (f[k] == '$') { // If epsilon exists
                                follow(a[i][0]); // Add FOLLOW(LHS)
                            }
                        }
                    }
                }

                // Case 2: If 'c' is the last symbol in the production
                if (a[i][j + 1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]); // Add FOLLOW(LHS)
                }
            }
        }
    }
}
