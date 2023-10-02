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
    #include "Expressions/blockExpression.hpp"
    #include "Expressions/ReturnExpression.hpp"
    #include "Expressions/ifExpression.hpp"
    #include "Expressions/variableExpression.hpp"
}

%union {
    int num;
    bool boolean;
    char* str;
    TerminalExpression* terminal;
    BinaryExpression* binary;
    BaseExpression* base;
    BlockExpression* blockExpr;
    std::vector<BaseExpression*>* block;
    VariableExpression* var;
    VariableAssignmentExpression* varAssign;
}

%token<num> TOKEN_INT
%token<str> TOKEN_STR
%type<base> expr
%type<terminal> terminal
%type<base> program
%type<blockExpr> exprBlock
%type<base> return_expr
%type<block> expr_list
%type<base> arith_expr
%type<varAssign> variableAssignment
%type<var> variable
%type<base> ifExpr
%token '*'
%token '/'
%token '+'
%token '-'
%token '%'
%token LPAREN RPAREN
%token LBRACE RBRACE
%token '='
%token KW_VAR
%token KW_MUT
%token END_OF_LINE
%token END_OF_FILE
%token RETURN
%token<boolean> T_TRUE T_FALSE
%token IF_TOKEN ELSE_TOKEN

%nonassoc LOWEST_PRECEDENCE
%nonassoc IF_TOKEN
%left '-'
%left '+'
%left '%'
%left '/'
%left '*'
%nonassoc LPAREN RPAREN
%nonassoc LBRACE RBRACE

/* Rules */
%%

program:
     expr END_OF_FILE { rootAST = $1; return 0; }
;

expr:
    return_expr { $$ = $1; }
|   LPAREN expr RPAREN { $$ = $2; }
|   exprBlock { $$ = $1; }
|   ifExpr { $$ = $1; }
|   arith_expr { $$ = $1; }
|   terminal { $$ = $1; }
;

terminal:
    TOKEN_INT { $$ = new TerminalExpression($1); }
|   T_TRUE { $$ = new TerminalExpression(true); }
|   T_FALSE { $$ = new TerminalExpression(false); }

variableAssignment:
    KW_VAR variable '=' expr { $$ = new VariableAssignmentExpression($4, $2, false); }
|   KW_VAR KW_MUT variable '=' expr { $$  = new VariableAssignmentExpression($5, $3, true); }

variable:
    TOKEN_STR { $$ = new VariableExpression($1); }


arith_expr:
    expr '+' expr { $$ = new BinaryExpression($1, '+', $3); }
|   expr '-' expr { $$ = new BinaryExpression($1, '-', $3); }
|   expr '*' expr { $$ = new BinaryExpression($1, '*', $3); }
|   expr '/' expr { $$ = new BinaryExpression($1, '/', $3); }
|   expr '%' expr { $$ = new BinaryExpression($1, '%', $3); }

exprBlock: 
   LBRACE expr_list RBRACE { $$ = new BlockExpression(*$2); }
;

ifExpr:
    IF_TOKEN LPAREN expr RPAREN exprBlock {
        std::cout << "matched if" << std::endl; $$ = new IfExpression($3, $5, nullptr);
    }
|   IF_TOKEN LPAREN expr RPAREN exprBlock ELSE_TOKEN exprBlock {
        std::cout << "match if-else" << std::endl; $$ = new IfExpression($3, $5, $7);
    }
|   IF_TOKEN LPAREN expr RPAREN exprBlock ELSE_TOKEN ifExpr {
        std::cout << "match if-else if" << std::endl; $$ = new IfExpression($3, $5, $7);
    }
;

expr_list:
    {
        $$ = new std::vector<BaseExpression*>();
    }
|   expr_list expr END_OF_LINE {
        $1->push_back($2);
        $$ = $1;
    }
|   expr_list ifExpr {
        $1->push_back($2);
        $$ = $1;
    }
;

return_expr:
    RETURN expr %prec LOWEST_PRECEDENCE { $$ = new ReturnExpression($2); }
;

%%

/* Epilogue */
void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}
