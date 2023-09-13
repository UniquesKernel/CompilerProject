%{
  /* Definitions */
  #include "parser.hpp"
  #include <cstdio>
%}

/* rules */
%% 

[0-9]+ { yylval.num = atoi(yytext); return NUMBER; }
"+" { return PLUS; }
[ \t\r]+ { /* ignore whitespace */ }
<<EOF>> { return 0; }
. {}

%% 
/* Epilogue */

int yywrap() {
  return 0;
}
