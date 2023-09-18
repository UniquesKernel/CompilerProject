%{
    /* Definitions */
    #include <iostream>
    #include <string>
    #include "Expressions/binaryExpression.hpp"
    #include "Expressions/terminalExpression.hpp"

    int yylex();
    void yyerror(const char* s);

    BaseExpression* rootAST = nullptr;
%}

%code requires{
    #include "Expressions/baseExpression.hpp"
    #include "Expressions/terminalExpression.hpp"
    #include "Expressions/binaryExpression.hpp"
}

%union {
    int num;
    TerminalExpression* terminal;
    BinaryExpression* binary;
    BaseExpression* base;
}

%token<num> INT
%type<base> expr
%type<base> start
%token '*'
%token '/'
%token '+'
%token '-'
%token '%'
%token LPAREN
%token RPAREN
%token END_OF_LINE
%token END_OF_FILE

%left '-'
%left '+'
%left '%'
%left '/'
%left '*'
%nonassoc LPAREN
%nonassoc RPAREN

/* Rules */
%%

start:
     expr END_OF_FILE { rootAST = $1; return 0; }

expr:
    INT { $$ = new TerminalExpression($1); }
    | LPAREN expr RPAREN { $$ = $2; }
    | expr '+' expr { $$ = new BinaryExpression($1, '+', $3); }
    | expr '-' expr { $$ = new BinaryExpression($1, '-', $3); }
    | expr '*' expr { $$ = new BinaryExpression($1, '*', $3); }
    | expr '/' expr { $$ = new BinaryExpression($1, '-', $3); }
    | expr '%' expr { $$ = new BinaryExpression($1, '%', $3); }

%%

/* Epilogue */
void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}
