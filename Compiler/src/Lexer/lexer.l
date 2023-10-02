%{
  /* Definitions */
  #include "parser.hpp"
  #include <cstdio>
  #include <string>

%}

%option noyywrap
%option yylineno

/* rules */
%% 

"fn" { return FUNCTION; }

"true" { return T_TRUE; }

"false" { return T_FALSE; }

"return" { return RETURN; }

"if" { return IF_TOKEN; }

"else" { return ELSE_TOKEN; }

"int" { yylval.type = new std::string(yytext); return TYPE; }
"bool" { yylval.type = new std::string(yytext); return TYPE; }

[a-zA-Z][a-zA-Z0-9]* { yylval.identifier = new std::string(yytext); return IDENTIFIER; }

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

"=" { return '='; }

"let" { return KW_VAR; }

"mut" { return KW_MUT; }

[a-zA-Z][0-9a-zA-Z]* { yylval.str = strdup(yytext); return TOKEN_STR;}

[ \t\r\n]* { }

<<EOF>> { return END_OF_FILE; }

. { return 0; }

%% 
