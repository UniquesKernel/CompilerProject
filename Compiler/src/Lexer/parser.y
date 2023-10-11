%{
    /* Definitions */
    #include <iostream>
    #include <string>
    #include "Expressions/binaryExpression.hpp"
    #include "Expressions/terminalExpression.hpp"
    #include "Expressions/variableExpression.hpp"

    int yylex();
    void yyerror(const char* s);

    ProgramExpression* rootAST = nullptr;
%}

%code requires{
    #include "Expressions/baseExpression.hpp"
    #include "Expressions/terminalExpression.hpp"
    #include "Expressions/binaryExpression.hpp"
    #include "Expressions/variableExpression.hpp"
    #include "Expressions/blockExpression.hpp"
    #include "Expressions/ReturnExpression.hpp"
    #include "Expressions/ifExpression.hpp"
    #include "Expressions/functionDeclaration.hpp"
    #include "Expressions/functionCall.hpp"
    #include "Expressions/programExpression.hpp"
    #include <memory>
}

%union {
    int num;
    std::string* identifier;
    std::string* type;
    std::string* str;
    bool boolean;
    char chr;
    float flt;
    TerminalExpression* terminal;
    BinaryExpression* binary;
    BaseExpression* base;
    VariableExpression* var;
    VariableAssignmentExpression* varAssign;
    BlockExpression* blockExpr;
    std::vector<BaseExpression*>* block;
    std::vector<FunctionDeclaration*>* funcList;
    ProgramExpression* programExpr;
    std::vector<std::pair<std::string, std::string>>* argList;
    std::vector<BaseExpression*>* exprList;
}

%token<num> TOKEN_INT
%token<chr> TOKEN_CHAR
%token<flt> TOKEN_FLOAT
%type<base> expr
%type<terminal> terminal
%type<programExpr> program
%type<blockExpr> exprBlock
%type<base> return_expr
%type<block> expr_list
%type<base> arith_expr
%type<varAssign> variableAssignment
%type<var> variable
%type<base> ifExpr
%type<base> function_decl
%type<base> functionCall
%type<funcList> function_list
%type<argList> arg_list
%type<exprList> call_list
%token<identifier> IDENTIFIER
%token<identifier> MAIN
%token<type> TYPE
%token '*'
%token '/'
%token '+'
%token '-'
%token '%'
%token ','
%token FUNCTION
%token '='
%token KW_VAR
%token KW_MUT
%token LPAREN RPAREN
%token LBRACE RBRACE
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
     function_list END_OF_FILE { rootAST = new ProgramExpression(*$1); return 0; }
;

function_list:
        { $$ = new std::vector<FunctionDeclaration*>();}
|   function_list function_decl {
        $1->push_back(static_cast<FunctionDeclaration*>($2));
        $$ = $1;
    }
;

function_decl:
    FUNCTION TYPE IDENTIFIER LPAREN RPAREN exprBlock {
        std::string type = *$2;
        std::string identifier = *$3;
        $$ = new FunctionDeclaration(identifier, type, $6);
    }
|   FUNCTION TYPE IDENTIFIER LPAREN arg_list RPAREN exprBlock {
        std::string type = *$2;
        std::string identifier = *$3;
        $$ = new FunctionDeclaration(identifier, type, $7, *$5);
    }
;

arg_list:
    { $$ = new std::vector<std::pair<std::string, std::string>>(); }
|   arg_list ',' TYPE IDENTIFIER {
        std::string type = *$3;
        std::string identifier = *$4;
        $1->push_back(std::make_pair(type, identifier));
        $$ = $1;
    }
|   TYPE IDENTIFIER {
        std::string type = *$1;
        std::string identifier = *$2;
        auto list = new std::vector<std::pair<std::string, std::string>>();
        list->push_back(std::make_pair(type, identifier));
        $$ = list;
}
;

functionCall:
    IDENTIFIER LPAREN RPAREN {
        $$ = new FunctionCall(*$1);
    }
|   IDENTIFIER LPAREN call_list RPAREN {
        std::vector<BaseExpression*> args = *$3;
        std::string identifier = *$1;
        $$ = new FunctionCall(identifier, args);
    }
;

call_list:
    { $$ = new std::vector<BaseExpression*>(); }
|   call_list ',' expr {
        $1->push_back($3);
        $$ = $1;
    }
|   expr {
        auto list = new std::vector<BaseExpression*>();
        list->push_back($1);
        $$ = list;
    }
;

expr:
    return_expr { $$ = $1; }
|   LPAREN expr RPAREN { $$ = $2; }
|   exprBlock { $$ = $1; }
|   ifExpr { $$ = $1; }
|   arith_expr { $$ = $1; }
|   terminal { $$ = $1; }
|   functionCall { $$ = $1; }
|   variableAssignment { $$ = $1; }
|   variable { $$ = $1; }
;

exprBlock: 
   LBRACE expr_list RBRACE { $$ = new BlockExpression(*$2); }
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

ifExpr:
    IF_TOKEN LPAREN terminal RPAREN exprBlock {
        $$ = new IfExpression($3, $5, nullptr);
    }
|   IF_TOKEN LPAREN terminal RPAREN exprBlock ELSE_TOKEN exprBlock {
        $$ = new IfExpression($3, $5, $7);
    }
|   IF_TOKEN LPAREN terminal RPAREN exprBlock ELSE_TOKEN ifExpr {
        $$ = new IfExpression($3, $5, $7);
    }
;

terminal:
    TOKEN_INT { $$ = new TerminalExpression($1); }
|   TOKEN_CHAR { $$ = new TerminalExpression($1); }
|   TOKEN_FLOAT { $$ = new TerminalExpression($1); }
|   T_TRUE { $$ = new TerminalExpression(true); }
|   T_FALSE { $$ = new TerminalExpression(false); }
;

variableAssignment:
    KW_VAR TYPE variable '=' expr {
        std::string varType = *$2;
        $$ = new VariableAssignmentExpression($5, $3, false, varType); 
        }
|   KW_VAR KW_MUT TYPE variable '=' expr {
        std::cout << "parse var assign \n";
        std::string varType = *$3;
        $$  = new VariableAssignmentExpression($6, $4, true, varType); 
        }
;

variable:
    IDENTIFIER { $$ = new VariableExpression(*$1); }
;

arith_expr:
    expr '+' expr { 
        $$ = BinaryExpression::createBinaryExpression($1, '+', $3);
        }
|   expr '-' expr { 
        $$ = BinaryExpression::createBinaryExpression($1, '-', $3);
        }
|   expr '*' expr { 
        $$ = BinaryExpression::createBinaryExpression($1, '*', $3);
        }
|   expr '/' expr { 
        $$ = BinaryExpression::createBinaryExpression($1, '/', $3);
        }
|   expr '%' expr { 
        $$ = BinaryExpression::createBinaryExpression($1, '%', $3);
        }
;

return_expr:
    RETURN expr %prec LOWEST_PRECEDENCE { $$ = new ReturnExpression($2); }
;

%%

/* Epilogue */
void yyerror(const char* s) {
    /* if mainFunc tell the user that the main function is missing */
    // if (rootAST == nullptr) {
    //     std::cout << "Error: main function is missing" << std::endl;
    // }
    // else {
        std::cout << "Error: " << s << std::endl;
    // }
}

