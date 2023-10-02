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
    #include "Expressions/variableExpression.hpp"
    #include "Expressions/blockExpression.hpp"
    #include "Expressions/ReturnExpression.hpp"
    #include "Expressions/ifExpression.hpp"
    #include "Expressions/functionDeclaration.hpp"
    #include "Expressions/functionCall.hpp"

<<<<<<< HEAD
#line 60 "parser.hpp"
=======
#line 59 "parser.hpp"
>>>>>>> origin/Variables

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
<<<<<<< HEAD
    TOKEN_INT = 258,               /* TOKEN_INT  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    TYPE = 260,                    /* TYPE  */
    FUNCTION = 261,                /* FUNCTION  */
=======
    TOKEN_STR = 258,               /* TOKEN_STR  */
    TOKEN_INT = 259,               /* TOKEN_INT  */
    KW_VAR = 260,                  /* KW_VAR  */
    KW_MUT = 261,                  /* KW_MUT  */
>>>>>>> origin/Variables
    LPAREN = 262,                  /* LPAREN  */
    RPAREN = 263,                  /* RPAREN  */
    LBRACE = 264,                  /* LBRACE  */
    RBRACE = 265,                  /* RBRACE  */
    END_OF_LINE = 266,             /* END_OF_LINE  */
    END_OF_FILE = 267,             /* END_OF_FILE  */
    RETURN = 268,                  /* RETURN  */
    T_TRUE = 269,                  /* T_TRUE  */
    T_FALSE = 270,                 /* T_FALSE  */
    IF_TOKEN = 271,                /* IF_TOKEN  */
    ELSE_TOKEN = 272,              /* ELSE_TOKEN  */
    LOWEST_PRECEDENCE = 273        /* LOWEST_PRECEDENCE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "parser.y"

    int num;
<<<<<<< HEAD
    std::string* identifier;
    std::string* type;
=======
    char* str;
>>>>>>> origin/Variables
    bool boolean;
    BaseExpression* base;
    TerminalExpression* terminal;
    VariableExpression* var;
    VariableAssignmentExpression* varAssign;
    BinaryExpression* binary;
    BlockExpression* blockExpr;
    std::vector<BaseExpression*>* block;

#line 107 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
