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
    double flt;
    TerminalExpression* terminal;
    BinaryExpression* binary;
    BaseExpression* base;
    VariableExpression* var;
    VariableAssignmentExpression* varAssign;
    VariableReassignmentExpression* varReassign;
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
%type<varReassign> variableReassignment
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
%token PLUS MINUS MUL DIV MOD
%token LT GT EQ NEQ
%token ','
%token FUNCTION
%token '='
%token KW_VAR
%token KW_MUT
%token COLON
%token LPAREN RPAREN
%token LBRACE RBRACE
%token END_OF_LINE
%token END_OF_FILE
%token RETURN
%token<boolean> T_TRUE T_FALSE
%token IF_TOKEN ELSE_TOKEN

%left PLUS MINUS 
%left MUL DIV MOD
%nonassoc '='
%nonassoc LOWEST_PRECEDENCE
%nonassoc IF_TOKEN
%nonassoc NEQ EQ LT GT
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
    FUNCTION IDENTIFIER LPAREN arg_list RPAREN COLON TYPE exprBlock {
        std::string type = *$7;
        std::string identifier = *$2;
        if ($4) {
            $$ = new FunctionDeclaration(identifier, type, $8, *$4);
        } else {
            $$ = new FunctionDeclaration(identifier, type, $8);
        }
    }
;

arg_list:
    { $$ = nullptr; }
|   arg_list ',' IDENTIFIER COLON TYPE {
        std::string type = *$5;
        std::string identifier = *$3;
        $1->push_back(std::make_pair(type, identifier));
        $$ = $1;
    }
|   IDENTIFIER COLON TYPE {
        std::string type = *$3;
        std::string identifier = *$1;
        auto list = new std::vector<std::pair<std::string, std::string>>();
        list->push_back(std::make_pair(type, identifier));
        $$ = list;
}
;

functionCall:
    IDENTIFIER LPAREN call_list RPAREN {
        std::string identifier = *$1;
        if ($3) {
            $$ = new FunctionCall(identifier, *$3);
        } else {
            $$ = new FunctionCall(identifier);
        }
    }
;

call_list:
    { $$ = nullptr; }
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
|   variableReassignment { $$ = $1; }
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
    IF_TOKEN LPAREN expr RPAREN exprBlock {
        $$ = new IfExpression($3, $5, nullptr);
    }
|   IF_TOKEN LPAREN expr RPAREN exprBlock ELSE_TOKEN exprBlock {
        $$ = new IfExpression($3, $5, $7);
    }
|   IF_TOKEN LPAREN expr RPAREN exprBlock ELSE_TOKEN ifExpr {
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
    KW_VAR variable COLON TYPE '=' expr {
        std::string varType = *$4;
        $$ = new VariableAssignmentExpression($6, $2, false, varType); 
        }
|   KW_VAR KW_MUT variable COLON TYPE '=' expr {
        std::string varType = *$5;
        $$  = new VariableAssignmentExpression($7, $3, true, varType); 
        }

variableReassignment:
    variable '=' expr {
        $$  = new VariableReassignmentExpression($3, $1); 
        }
;

variable:
    IDENTIFIER { $$ = new VariableExpression(*$1); }
;

arith_expr:
    expr PLUS expr { 
        $$ = BinaryExpression::createBinaryExpression($1, "+", $3);
        }
|   expr MINUS expr { 
        $$ = BinaryExpression::createBinaryExpression($1, "-", $3);
        }
|   expr MUL expr { 
        $$ = BinaryExpression::createBinaryExpression($1, "*", $3);
        }
|   expr DIV expr { 
        $$ = BinaryExpression::createBinaryExpression($1, "/", $3);
        }
|   expr MOD expr { 
        $$ = BinaryExpression::createBinaryExpression($1, "%", $3);
        }
|   expr LT expr { 
        $$ = BinaryExpression::createBinaryExpression($1, "<", $3);
        }
|   expr GT expr { 
        $$ = BinaryExpression::createBinaryExpression($1, ">", $3);
        }
|   expr EQ expr { 
        $$ = BinaryExpression::createBinaryExpression($1, "==", $3);
        }
|   expr NEQ expr {
        $$ = BinaryExpression::createBinaryExpression($1, "!=", $3);
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

