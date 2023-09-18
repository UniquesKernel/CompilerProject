%{
    /* Definitions */
    #include <iostream>
    #include <string>
    int yylex();
    void yyerror(const char* s);

    typedef struct ResultNode {
        int value;
        struct ResultNode* next;
    } ResultNode;

    ResultNode* results = nullptr;
    void appendResult(int value);
%}

%locations
%union {
    int num;
}

%token<num> NUMBER
%token '*'
%token '/'
%token '+'
%token '-'
%token LPAREN
%token RPAREN
%token END_OF_LINE
%token END_OF_FILE

%left '-'
%left '+'
%right '/'
%right '*'
%nonassoc LPAREN
%nonassoc RPAREN
%type<num> expr

/* Rules */
%%

start:
    program END_OF_FILE { return 0; }
;

program:
     /* Empty */
|    program expr END_OF_LINE { appendResult($2); }
;

expr:
    LPAREN expr RPAREN { $$ = $2; }
|   NUMBER { $$ = $1; }
|   expr '*' expr { $$ = $1 * $3; }
|   expr '/' expr {
        if ($3 == 0) {
            yyerror("Division by zero error");
            $$ = 0;  // Default to 0 on error
        } else {
            $$ = $1 / $3;
        }
    }
|   expr '+' expr { $$ = $1 + $3; }
|   expr '-' expr { $$ = $1 - $3; }
;

%%

/* Epilogue */
void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}

void appendResult(int value) {
    ResultNode* newNode = new ResultNode;
    newNode->value = value;
    newNode->next = nullptr;

    if (!results) {
        // If the list is empty, set the new node as the first node.
        results = newNode;
    } else {
        // Otherwise, find the last node and append the new node.
        ResultNode* current = results;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}
