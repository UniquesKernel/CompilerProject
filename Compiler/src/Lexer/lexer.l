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

"let" { return KW_VAR; }

"mut" { return KW_MUT; }

"int" { yylval.type = new std::string(yytext); return TYPE; }
"bool" { yylval.type = new std::string(yytext); return TYPE; }
"float" { yylval.type = new std::string(yytext); return TYPE; }
"char" { yylval.type = new std::string(yytext); return TYPE; }

[a-zA-Z][a-zA-Z0-9]* { yylval.identifier = new std::string(yytext); return IDENTIFIER; }

'[a-zA-Z]' { yylval.chr = yytext[1]; return TOKEN_CHAR; }

[0-9]+\.[0-9]+ { yylval.flt = atof(yytext); return TOKEN_FLOAT; }

"{" { return LBRACE; }

"}" { return RBRACE; }

[;] { return END_OF_LINE; }

[,] { return ','; }

[0-9]+ { yylval.num = atoi(yytext); return TOKEN_INT; }

"*" { return '*'; }

"/" { return '/'; }

"+" { return '+'; }

"-" { return '-'; }

"%" { return '%'; }

"(" { return LPAREN; }

")" { return RPAREN; }

"=" { return '='; }



[ \t\r\n]* { }

<<EOF>> { return END_OF_FILE; }

. { return 0; }

%% 
