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

"main" { yylval.identifier = new std::string(yytext); return MAIN; }

"fn" { return FUNCTION; }

"true" { return T_TRUE; }

"false" { return T_FALSE; }

"return" { return RETURN; }

"if" { return IF_TOKEN; }

"else" { return ELSE_TOKEN; }

"int" { yylval.type = new std::string(yytext); return TYPE; }
"bool" { yylval.type = new std::string(yytext); return TYPE; }

"let" { return KW_VAR; }

"mut" { return KW_MUT; }

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

[a-zA-Z][a-zA-Z0-9]* { yylval.identifier = new std::string(yytext); return IDENTIFIER; }

[ \t\r\n]* { }

<<EOF>> { return END_OF_FILE; }

. { return 0; }

%% 
