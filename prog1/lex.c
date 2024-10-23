#include <stdio.h>
#include <string.h>

char line[100];

int is_operator(char c)
{
    switch (c)
    {
        case '+':   
        case '-':   
        case '*':   
        case '/':   
        case '=':   
            printf("%c - Operator\n", c);
            return 1;
    }

    return 0;
}

int is_delimiter(char c)
{
    switch (c)
    {
        case '{':
        case '}':
        case '(':
        case ')':
        case '[':
        case ']':
        case ',':
        case ';':
            printf("%c - Delimiter\n", c);
            return 1;
    }

    return 0;
}

int is_keyword(char buffer[])
{
    char keywords[32][10] = {
        "auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"
    };

    for(int i = 0; i < 32; ++i)
    {
        if(strcmp(keywords[i], buffer) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void main()
{
    char token[100];
    int index = 0;
    
    printf("Enter code (Type 'exit' to stop):\n");

    // Loop to keep reading lines from the console
    while (1)
    {
        // Read input from the console
        if (!fgets(line, sizeof(line), stdin))
        {
            break;
        }

        // Exit the loop if the user types "exit"
        if (strncmp(line, "exit", 4) == 0)
        {
            break;
        }

        printf("\n%s\n", line);  // Print the current line

        strcpy(token, "");
        index = 0;

        for (int i = 0; i < strlen(line); i++)
        {
            if (is_operator(line[i]) || is_delimiter(line[i]) || line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            {
                // Check if the token is an identifier or a keyword
                if (strcmp(token, "") != 0)
                {
                    if (is_keyword(token))
                        printf("%s - Keyword\n", token);
                    else  
                        printf("%s - Identifier\n", token);

                    strcpy(token, "");
                    index = 0;
                }
            }
            else  
            {
                token[index++] = line[i];
                token[index] = '\0';
            }
        }
    }
}
