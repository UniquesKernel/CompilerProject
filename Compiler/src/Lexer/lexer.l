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

[0-9]+ { yylval.num = atoi(yytext); return INT; }

"*" { return '*'; }

"/" { return '/'; }

"+" { return '+'; }

"-" { return '-'; }

"%" { return '%'; }

"(" { return LPAREN; }

")" { return RPAREN; }

"=" { return '='; }

"let" { return KW_VAR; }

"mut" { return KW_MUT; }

[a-zA-Z][0-9a-zA-Z]* { yylval.str = strdup(yytext); return STR;}

[ \t\r\n]* { }

<<EOF>> { return END_OF_FILE; }

. { return 0; }

%% 
