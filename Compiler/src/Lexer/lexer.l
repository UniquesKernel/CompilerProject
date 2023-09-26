%{
  /* Definitions */
  #include "parser.hpp"
  #include <cstdio>

%}

%option noyywrap
%option yylineno

/* rules */
%% 

"true" { return T_TRUE; }

"false" { return T_FALSE; }

"return" { return RETURN; }

"if" { return IF_TOKEN; }

"else" { return ELSE_TOKEN; }

"{" { return LBRACE; }

"}" { return RBRACE; }

[;] { return END_OF_LINE; }

[0-9]+ { yylval.num = atoi(yytext); return TOKEN_INT; }

"*" { return '*'; }

"/" { return '/'; }

"+" { return '+'; }

"-" { return '-'; }

"%" { return '%'; }

"(" { return LPAREN; }

")" { return RPAREN; }

[ \t\r\n]* { }

<<EOF>> { return END_OF_FILE; }

. { return 0; }

%% 
