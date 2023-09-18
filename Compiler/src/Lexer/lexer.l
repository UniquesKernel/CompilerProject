%{
  /* Definitions */
  #include "parser.hpp"
  #include <cstdio>

%}

%option noyywrap
%option yylineno

/* rules */
%% 

[;] { return END_OF_LINE; }

[0-9]+ { yylval.num = atoi(yytext); return NUMBER; }

"*" { return '*'; }

"/" { return '/'; }

"+" { return '+'; }

"-" { return '-'; }

"(" { return LPAREN; }

")" { return RPAREN; }

[ \t\r\n]* { }

<<EOF>> { return END_OF_FILE; }

. { return 0; }

%% 
