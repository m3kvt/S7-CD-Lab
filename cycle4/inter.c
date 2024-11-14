#include <stdio.h>
#include <string.h>
char temp[100];
void gen_code_op(char *inp, char op, char *reg)
{

    int i = 0, j = 0;
    while (inp[i] != '\0')
    {
        if (inp[i] == op)
        {
            printf("%c\t%c\t%c\t%c\n", op, *reg, inp[i - 1], inp[i + 1]);
            temp[j - 1] = *reg;
            i += 2;
            (*reg)--;
            continue;
        }
        temp[j] = inp[i];
        i++;
        j++;
    }
    temp[++j] = '\0';
    strcpy(temp, inp);
}

void gen_code(char *inp)
{
    char reg = 'Z';
    gen_code_op(inp, '/', &reg);
    gen_code_op(inp, '*', &reg);
    gen_code_op(inp, '+', &reg);
    gen_code_op(inp, '-', &reg);
}
int main()
{
    char *inp;
    printf("enter the expression:\n");
    scanf("%s", inp);
    printf("operator\tdestin\targ1\t arg2\n");
    gen_code(inp);
}
