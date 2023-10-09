/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 15 "parser.y"

    #include "Expressions/baseExpression.hpp"
    #include "Expressions/terminalExpression.hpp"
    #include "Expressions/binaryExpression.hpp"
    #include "Expressions/blockExpression.hpp"
    #include "Expressions/ReturnExpression.hpp"
    #include "Expressions/ifExpression.hpp"
    #include "Expressions/variableExpression.hpp"
    #include "Expressions/functionDeclaration.hpp"
    #include "Expressions/functionCall.hpp"

#line 61 "parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_INT = 258,               /* TOKEN_INT  */
    TOKEN_STR = 259,               /* TOKEN_STR  */
    TOKEN_CHAR = 260,              /* TOKEN_CHAR  */
    TOKEN_FLOAT = 261,             /* TOKEN_FLOAT  */
    IDENTIFIER = 262,              /* IDENTIFIER  */
    TYPE = 263,                    /* TYPE  */
    FUNCTION = 264,                /* FUNCTION  */
    LPAREN = 265,                  /* LPAREN  */
    RPAREN = 266,                  /* RPAREN  */
    LBRACE = 267,                  /* LBRACE  */
    RBRACE = 268,                  /* RBRACE  */
    KW_VAR = 269,                  /* KW_VAR  */
    KW_MUT = 270,                  /* KW_MUT  */
    END_OF_LINE = 271,             /* END_OF_LINE  */
    END_OF_FILE = 272,             /* END_OF_FILE  */
    RETURN = 273,                  /* RETURN  */
    T_TRUE = 274,                  /* T_TRUE  */
    T_FALSE = 275,                 /* T_FALSE  */
    IF_TOKEN = 276,                /* IF_TOKEN  */
    ELSE_TOKEN = 277,              /* ELSE_TOKEN  */
    LOWEST_PRECEDENCE = 278        /* LOWEST_PRECEDENCE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "parser.y"

    int num;
    std::string* identifier;
    std::string* type;
    bool boolean;
    char* str;
    char chr;
    float flt;
    TerminalExpression* terminal;
    BinaryExpression* binary;
    BaseExpression* base;
    BlockExpression* blockExpr;
    std::vector<BaseExpression*>* block;
    VariableExpression* var;
    VariableAssignmentExpression* varAssign;

#line 118 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
