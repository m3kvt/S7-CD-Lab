#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 20
#define MAX_ALPHABETS 20

struct node {
    int st;
    struct node *link;
};

void findclosure(int, int);
void insert_trantbl(int, char, int);
int findalpha(char);
void print_e_closure(int);

static int set[MAX_STATES], nostate, noalpha, s, notransition, c, r, buffer[MAX_STATES];
char alphabet[MAX_ALPHABETS];
static int e_closure[MAX_STATES][MAX_STATES] = {0};
struct node *transition[MAX_STATES][MAX_ALPHABETS] = {NULL};

int main() {
    int i, j, k, m, t, n;
    struct node *temp;

    printf("Enter the number of alphabets?\n");
    scanf("%d", &noalpha);
    getchar();

    printf("NOTE:- [ use letter e as epsilon]\n");
    printf("NOTE:- [e must be last character, if it is present]\n");

    printf("\nEnter alphabets?\n");
    for(i = 0; i < noalpha; i++) {
        alphabet[i] = getchar();
        getchar();
    }

    printf("\nEnter the number of states?\n");
    scanf("%d", &nostate);

    printf("\nEnter no of transitions?\n");
    scanf("%d", &notransition);

    printf("NOTE:- [Transition is in the form -> qno alphabet qno]\n");
    printf("NOTE:- [States numbers must be greater than zero]\n");

    printf("\nEnter transitions?\n");
    for(i = 0; i < notransition; i++) {
        scanf("%d %c %d", &r, &c, &s);
        insert_trantbl(r, c, s);
    }

    printf("\n");
    printf("e-closure of states……\n");
    printf("—————————–\n");
    for(i = 1; i <= nostate; i++) {
        c = 0;
        for(j = 0; j < MAX_STATES; j++) {
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }
        findclosure(i, i);
        printf("\ne-closure(q%d): ", i);
        print_e_closure(i);
    }

    return 0;
}

void findclosure(int x, int sta) {
    struct node *temp;
    if (buffer[x])
        return;
    e_closure[sta][c++] = x;
    buffer[x] = 1;
    if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL) {
        temp = transition[x][noalpha - 1];
        while (temp != NULL) {
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
}

void insert_trantbl(int r, char c, int s) {
    int j;
    struct node *temp;
    j = findalpha(c);
    if (j == -1) {
        printf("Error: Alphabet not found\n");
        exit(1);
    }
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

int findalpha(char c) {
    int i;
    for (i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;
    return -1;
}

void print_e_closure(int i) {
    int j;
    printf("{");
    for (j = 0; e_closure[i][j] != 0; j++)
        printf("q%d,", e_closure[i][j]);
    printf("}");
}

