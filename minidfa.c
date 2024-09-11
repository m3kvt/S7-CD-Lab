#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_ALPHABET 20

// Structures
struct DFA {
    int num_states;
    int num_alpha;
    int start_state;
    int final_states[MAX_STATES];
    int num_final_states;
    char alphabet[MAX_ALPHABET];
    int transitions[MAX_STATES][MAX_ALPHABET];
};

// Global Variables
bool partition[MAX_STATES][MAX_STATES];
int new_state_map[MAX_STATES];
int state_partition[MAX_STATES];
int num_partitions;
int partition_states[MAX_STATES][MAX_STATES];
bool visited[MAX_STATES];

// Function Prototypes
void initialize_DFA(struct DFA* dfa);
void print_DFA(const struct DFA* dfa);
void minimize_DFA(struct DFA* dfa);
void print_minimized_DFA(const struct DFA* dfa);

int main() {
    struct DFA dfa;
    initialize_DFA(&dfa);
    printf("Original DFA:\n");
    print_DFA(&dfa);

    minimize_DFA(&dfa);
    printf("\nMinimized DFA:\n");
    print_minimized_DFA(&dfa);

    return 0;
}

// Initialize DFA
void initialize_DFA(struct DFA* dfa) {
    printf("Enter number of states: ");
    scanf("%d", &dfa->num_states);

    printf("Enter number of alphabet symbols: ");
    scanf("%d", &dfa->num_alpha);
    printf("Enter alphabet symbols: ");
    for (int i = 0; i < dfa->num_alpha; i++) {
        scanf(" %c", &dfa->alphabet[i]);
    }

    printf("Enter start state: ");
    scanf("%d", &dfa->start_state);

    printf("Enter number of final states: ");
    scanf("%d", &dfa->num_final_states);
    printf("Enter final states: ");
    for (int i = 0; i < dfa->num_final_states; i++) {
        scanf("%d", &dfa->final_states[i]);
    }

    printf("Enter transition table (state, symbol, next_state):\n");
    for (int i = 0; i < dfa->num_states; i++) {
        for (int j = 0; j < dfa->num_alpha; j++) {
            printf("Transition for state %d on symbol %c: ", i, dfa->alphabet[j]);
            scanf("%d", &dfa->transitions[i][j]);
        }
    }
}

// Print DFA
void print_DFA(const struct DFA* dfa) {
    printf("States: ");
    for (int i = 0; i < dfa->num_states; i++) {
        printf("%d ", i);
    }
    printf("\nAlphabet: ");
    for (int i = 0; i < dfa->num_alpha; i++) {
        printf("%c ", dfa->alphabet[i]);
    }
    printf("\nStart State: %d\n", dfa->start_state);
    printf("Final States: ");
    for (int i = 0; i < dfa->num_final_states; i++) {
        printf("%d ", dfa->final_states[i]);
    }
    printf("\nTransitions:\n");
    for (int i = 0; i < dfa->num_states; i++) {
        for (int j = 0; j < dfa->num_alpha; j++) {
            printf("State %d on symbol %c -> State %d\n", i, dfa->alphabet[j], dfa->transitions[i][j]);
        }
    }
}

// Minimize DFA
void minimize_DFA(struct DFA* dfa) {
    int i, j, k;

    // Initialize partitions
    for (i = 0; i < dfa->num_states; i++) {
        state_partition[i] = 0;
        new_state_map[i] = -1;
        for (j = 0; j < dfa->num_states; j++) {
            partition[i][j] = false;
        }
    }

    // Initial partition (final and non-final states)
    num_partitions = 0;
    for (i = 0; i < dfa->num_states; i++) {
        state_partition[i] = (i < dfa->num_final_states) ? 1 : 0;
    }

    for (i = 0; i < dfa->num_states; i++) {
        for (j = 0; j < dfa->num_states; j++) {
            partition[i][j] = (state_partition[i] == state_partition[j]);
        }
    }

    // Refinement
    bool changed;
    do {
        changed = false;
        for (i = 0; i < dfa->num_states; i++) {
            for (j = 0; j < dfa->num_states; j++) {
                if (partition[i][j]) {
                    for (k = 0; k < dfa->num_alpha; k++) {
                        int p1 = dfa->transitions[i][k];
                        int p2 = dfa->transitions[j][k];
                        if (!partition[p1][p2]) {
                            partition[i][j] = false;
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }
    } while (changed);

    // Create new minimized DFA states
    for (i = 0; i < dfa->num_states; i++) {
        if (new_state_map[i] == -1) {
            for (j = 0; j < dfa->num_states; j++) {
                if (partition[i][j]) {
                    new_state_map[j] = i;
                }
            }
        }
    }

    // Update DFA details
    int new_num_states = 0;
    for (i = 0; i < dfa->num_states; i++) {
        if (new_state_map[i] == i) {
            new_num_states++;
        }
    }

    int new_transitions[MAX_STATES][MAX_ALPHABET];
    int new_final_states[MAX_STATES];
    int new_state_map[MAX_STATES];
    int new_start_state;

    for (i = 0; i < new_num_states; i++) {
        for (j = 0; j < dfa->num_alpha; j++) {
            new_transitions[i][j] = new_state_map[dfa->transitions[i][j]];
        }
    }

    int new_num_final_states = 0;
    for (i = 0; i < dfa->num_final_states; i++) {
        if (new_state_map[dfa->final_states[i]] == new_start_state) {
            new_final_states[new_num_final_states++] = new_state_map[dfa->final_states[i]];
        }
    }

    // Update DFA structure
    dfa->num_states = new_num_states;
    dfa->num_final_states = new_num_final_states;
    for (i = 0; i < new_num_states; i++) {
        for (j = 0; j < dfa->num_alpha; j++) {
            dfa->transitions[i][j] = new_transitions[i][j];
        }
    }
    for (i = 0; i < new_num_final_states; i++) {
        dfa->final_states[i] = new_final_states[i];
    }
    dfa->start_state = new_state_map[dfa->start_state];
}

// Print Minimized DFA
void print_minimized_DFA(const struct DFA* dfa) {
    printf("States: ");
    for (int i = 0; i < dfa->num_states; i++) {
        printf("%d ", i);
    }
    printf("\nAlphabet: ");
    for (int i = 0; i < dfa->num_alpha; i++) {
        printf("%c ", dfa->alphabet[i]);
    }
    printf("\nStart State: %d\n", dfa->start_state);
    printf("Final States: ");
    for (int i = 0; i < dfa->num_final_states; i++) {
        printf("%d ", dfa->final_states[i]);
    }
    printf("\nTransitions:\n");
    for (int i = 0; i < dfa->num_states; i++) {
        for (int j = 0; j < dfa->num_alpha; j++) {
            printf("State %d on symbol %c -> State %d\n", i, dfa->alphabet[j], dfa->transitions[i][j]);
        }
    }
}

