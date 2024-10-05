%{
    #include "y.tab.h"  // Include Yacc-generated token definitions
%}

%%

[a-zA-Z][a-zA-Z0-9]*    return identifier;   // Match an identifier: starting letter, followed by letters/digits

.                       return yytext[0];    // Match and return any other character
\n                      return 0;            // End of input

%%

int yywrap() {
    return 1;
}

