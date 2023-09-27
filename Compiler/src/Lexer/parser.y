%{
    /* Definitions */
    #include <iostream>
    #include <string>
    #include "Expressions/binaryExpression.hpp"
    #include "Expressions/terminalExpression.hpp"
    #include "Expressions/variableExpression.hpp"

    int yylex();
    void yyerror(const char* s);

    BaseExpression* rootAST = nullptr;
%}

%code requires{
    #include "Expressions/baseExpression.hpp"
    #include "Expressions/terminalExpression.hpp"
    #include "Expressions/binaryExpression.hpp"
    #include "Expressions/variableExpression.hpp"
}

%union {
    int num;
    char* str;
    TerminalExpression* terminal;
    BinaryExpression* binary;
    BaseExpression* base;
    VariableExpression* var;
    VariableAssignmentExpression* varAssign;
}

%token<num> INT
%token<str> STR
%type<base> expr
%type<base> start
%token '*'
%token '/'
%token '+'
%token '-'
%token '%'
%token '='
%token KW_VAR
%token KW_MUT
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
    | STR { $$ = new VariableExpression($1); }
    | LPAREN expr RPAREN { $$ = $2; }
    | expr '+' expr { $$ = new BinaryExpression($1, '+', $3); }
    | expr '-' expr { $$ = new BinaryExpression($1, '-', $3); }
    | expr '*' expr { $$ = new BinaryExpression($1, '*', $3); }
    | expr '/' expr { $$ = new BinaryExpression($1, '-', $3); }
    | expr '%' expr { $$ = new BinaryExpression($1, '%', $3); }
    | KW_VAR STR '=' expr { $$ = new VariableAssignmentExpression($4, $2, false); }
    | KW_VAR KW_MUT STR '=' expr { $$  = new VariableAssignmentExpression($5, $3, true); }
%%

/* Epilogue */
void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}
