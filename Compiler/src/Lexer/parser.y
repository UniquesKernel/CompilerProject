%{
    /* Definitions */
    #include <iostream>
    int yylex();
    int yyerror(char* s);
    int result;
%}

%union {
    int num;
    char sym;
}

%token<num> NUMBER
%token PLUS
%left PLUS
%type<num> expr

/* Rules */
%%

input: 
     expr { std::cout << $1 << std::endl; };

expr:
    NUMBER { $$ = $1; }
|   expr PLUS expr { $$ = $1 + $3; }
;

%%
/* Epilogue */

int yyerror(char* s) {
    std::cout << "ERROR: " << s << std::endl;
    return 0;
}
