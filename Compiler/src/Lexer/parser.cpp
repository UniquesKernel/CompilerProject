/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* First part of user prologue.  */
#line 1 "parser.y"

/* Definitions */
#include "Expressions/binaryExpression.hpp"
#include "Expressions/terminalExpression.hpp"
#include "Expressions/variableExpression.hpp"
#include <iostream>
#include <string>

int yylex();
void yyerror(const char *s);

ProgramExpression *rootAST = nullptr;

#line 85 "parser.cpp"

#ifndef YY_CAST
#ifdef __cplusplus
#define YY_CAST(Type, Val) static_cast<Type>(Val)
#define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type>(Val)
#else
#define YY_CAST(Type, Val) ((Type)(Val))
#define YY_REINTERPRET_CAST(Type, Val) ((Type)(Val))
#endif
#endif
#ifndef YY_NULLPTR
#if defined __cplusplus
#if 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#else
#define YY_NULLPTR ((void *)0)
#endif
#endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t {
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,               /* "end of file"  */
  YYSYMBOL_YYerror = 1,             /* error  */
  YYSYMBOL_YYUNDEF = 2,             /* "invalid token"  */
  YYSYMBOL_TOKEN_INT = 3,           /* TOKEN_INT  */
  YYSYMBOL_TOKEN_CHAR = 4,          /* TOKEN_CHAR  */
  YYSYMBOL_TOKEN_FLOAT = 5,         /* TOKEN_FLOAT  */
  YYSYMBOL_IDENTIFIER = 6,          /* IDENTIFIER  */
  YYSYMBOL_MAIN = 7,                /* MAIN  */
  YYSYMBOL_TYPE = 8,                /* TYPE  */
  YYSYMBOL_PLUS = 9,                /* PLUS  */
  YYSYMBOL_MINUS = 10,              /* MINUS  */
  YYSYMBOL_MUL = 11,                /* MUL  */
  YYSYMBOL_DIV = 12,                /* DIV  */
  YYSYMBOL_MOD = 13,                /* MOD  */
  YYSYMBOL_LT = 14,                 /* LT  */
  YYSYMBOL_GT = 15,                 /* GT  */
  YYSYMBOL_EQ = 16,                 /* EQ  */
  YYSYMBOL_NEQ = 17,                /* NEQ  */
  YYSYMBOL_18_ = 18,                /* ','  */
  YYSYMBOL_FUNCTION = 19,           /* FUNCTION  */
  YYSYMBOL_20_ = 20,                /* '='  */
  YYSYMBOL_KW_VAR = 21,             /* KW_VAR  */
  YYSYMBOL_KW_MUT = 22,             /* KW_MUT  */
  YYSYMBOL_LPAREN = 23,             /* LPAREN  */
  YYSYMBOL_RPAREN = 24,             /* RPAREN  */
  YYSYMBOL_LBRACE = 25,             /* LBRACE  */
  YYSYMBOL_RBRACE = 26,             /* RBRACE  */
  YYSYMBOL_END_OF_LINE = 27,        /* END_OF_LINE  */
  YYSYMBOL_END_OF_FILE = 28,        /* END_OF_FILE  */
  YYSYMBOL_RETURN = 29,             /* RETURN  */
  YYSYMBOL_T_TRUE = 30,             /* T_TRUE  */
  YYSYMBOL_T_FALSE = 31,            /* T_FALSE  */
  YYSYMBOL_IF_TOKEN = 32,           /* IF_TOKEN  */
  YYSYMBOL_ELSE_TOKEN = 33,         /* ELSE_TOKEN  */
  YYSYMBOL_LOWEST_PRECEDENCE = 34,  /* LOWEST_PRECEDENCE  */
  YYSYMBOL_YYACCEPT = 35,           /* $accept  */
  YYSYMBOL_program = 36,            /* program  */
  YYSYMBOL_function_list = 37,      /* function_list  */
  YYSYMBOL_function_decl = 38,      /* function_decl  */
  YYSYMBOL_arg_list = 39,           /* arg_list  */
  YYSYMBOL_functionCall = 40,       /* functionCall  */
  YYSYMBOL_call_list = 41,          /* call_list  */
  YYSYMBOL_expr = 42,               /* expr  */
  YYSYMBOL_exprBlock = 43,          /* exprBlock  */
  YYSYMBOL_expr_list = 44,          /* expr_list  */
  YYSYMBOL_ifExpr = 45,             /* ifExpr  */
  YYSYMBOL_terminal = 46,           /* terminal  */
  YYSYMBOL_variableAssignment = 47, /* variableAssignment  */
  YYSYMBOL_variable = 48,           /* variable  */
  YYSYMBOL_arith_expr = 49,         /* arith_expr  */
  YYSYMBOL_return_expr = 50         /* return_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;

#ifdef short
#undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
#include <limits.h> /* INFRINGES ON USER NAME SPACE */
#if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#define YY_STDINT_H
#endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
#undef UINT_LEAST8_MAX
#undef UINT_LEAST16_MAX
#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H &&                  \
       UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H &&                 \
       UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
#if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#define YYPTRDIFF_T __PTRDIFF_TYPE__
#define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
#elif defined PTRDIFF_MAX
#ifndef ptrdiff_t
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#endif
#define YYPTRDIFF_T ptrdiff_t
#define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
#else
#define YYPTRDIFF_T long
#define YYPTRDIFF_MAXIMUM LONG_MAX
#endif
#endif

#ifndef YYSIZE_T
#ifdef __SIZE_TYPE__
#define YYSIZE_T __SIZE_TYPE__
#elif defined size_t
#define YYSIZE_T size_t
#elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#define YYSIZE_T size_t
#else
#define YYSIZE_T unsigned
#endif
#endif

#define YYSIZE_MAXIMUM                                                         \
  YY_CAST(YYPTRDIFF_T,                                                         \
          (YYPTRDIFF_MAXIMUM < YY_CAST(YYSIZE_T, -1) ? YYPTRDIFF_MAXIMUM       \
                                                     : YY_CAST(YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST(YYPTRDIFF_T, sizeof(X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#define YY_(Msgid) dgettext("bison-runtime", Msgid)
#endif
#endif
#ifndef YY_
#define YY_(Msgid) Msgid
#endif
#endif

#ifndef YY_ATTRIBUTE_PURE
#if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_PURE __attribute__((__pure__))
#else
#define YY_ATTRIBUTE_PURE
#endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_UNUSED __attribute__((__unused__))
#else
#define YY_ATTRIBUTE_UNUSED
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
#define YY_USE(E) ((void)(E))
#else
#define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && !defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
#if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                                    \
  _Pragma("GCC diagnostic push")                                               \
      _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")
#else
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                                    \
  _Pragma("GCC diagnostic push")                                               \
      _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")                    \
          _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#endif
#define YY_IGNORE_MAYBE_UNINITIALIZED_END _Pragma("GCC diagnostic pop")
#else
#define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && !defined __ICC && 6 <= __GNUC__
#define YY_IGNORE_USELESS_CAST_BEGIN                                           \
  _Pragma("GCC diagnostic push")                                               \
      _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"")
#define YY_IGNORE_USELESS_CAST_END _Pragma("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_END
#endif

#define YY_ASSERT(E) ((void)(0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

#ifdef YYSTACK_USE_ALLOCA
#if YYSTACK_USE_ALLOCA
#ifdef __GNUC__
#define YYSTACK_ALLOC __builtin_alloca
#elif defined __BUILTIN_VA_ARG_INCR
#include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#elif defined _AIX
#define YYSTACK_ALLOC __alloca
#elif defined _MSC_VER
#include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#define alloca _alloca
#else
#define YYSTACK_ALLOC alloca
#if !defined _ALLOCA_H && !defined EXIT_SUCCESS
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
/* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#endif
#endif
#endif

#ifdef YYSTACK_ALLOC
/* Pacify GCC's 'empty if-body' warning.  */
#define YYSTACK_FREE(Ptr)                                                      \
  do { /* empty */                                                             \
    ;                                                                          \
  } while (0)
#ifndef YYSTACK_ALLOC_MAXIMUM
/* The OS might guarantee only one guard page at the bottom of the stack,
   and a page size can be as small as 4096 bytes.  So we cannot safely
   invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
   to allow for a few compiler-allocated temporary stack slots.  */
#define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#endif
#else
#define YYSTACK_ALLOC YYMALLOC
#define YYSTACK_FREE YYFREE
#ifndef YYSTACK_ALLOC_MAXIMUM
#define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#endif
#if (defined __cplusplus && !defined EXIT_SUCCESS &&                           \
     !((defined YYMALLOC || defined malloc) &&                                 \
       (defined YYFREE || defined free)))
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#if !defined malloc && !defined EXIT_SUCCESS
void *malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#ifndef YYFREE
#define YYFREE free
#if !defined free && !defined EXIT_SUCCESS
void free(void *); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#endif
#endif /* !defined yyoverflow */

#if (!defined yyoverflow &&                                                    \
     (!defined __cplusplus ||                                                  \
      (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
#define YYSTACK_GAP_MAXIMUM (YYSIZEOF(union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
#define YYSTACK_BYTES(N)                                                       \
  ((N) * (YYSIZEOF(yy_state_t) + YYSIZEOF(YYSTYPE)) + YYSTACK_GAP_MAXIMUM)

#define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
#define YYSTACK_RELOCATE(Stack_alloc, Stack)                                   \
  do {                                                                         \
    YYPTRDIFF_T yynewbytes;                                                    \
    YYCOPY(&yyptr->Stack_alloc, Stack, yysize);                                \
    Stack = &yyptr->Stack_alloc;                                               \
    yynewbytes = yystacksize * YYSIZEOF(*Stack) + YYSTACK_GAP_MAXIMUM;         \
    yyptr += yynewbytes / YYSIZEOF(*yyptr);                                    \
  } while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
#ifndef YYCOPY
#if defined __GNUC__ && 1 < __GNUC__
#define YYCOPY(Dst, Src, Count)                                                \
  __builtin_memcpy(Dst, Src, YY_CAST(YYSIZE_T, (Count)) * sizeof(*(Src)))
#else
#define YYCOPY(Dst, Src, Count)                                                \
  do {                                                                         \
    YYPTRDIFF_T yyi;                                                           \
    for (yyi = 0; yyi < (Count); yyi++)                                        \
      (Dst)[yyi] = (Src)[yyi];                                                 \
  } while (0)
#endif
#endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL 3
/* YYLAST -- Last index in YYTABLE.  */

#define YYLAST 123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 35
/* YYNNTS -- Number of nonterminals.  */

#define YYNNTS 16
/* YYNRULES -- Number of rules.  */
#define YYNRULES 46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 86

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 287

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                       \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                                            \
       ? YY_CAST(yysymbol_kind_t, yytranslate[YYX])                            \
       : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] = {
    0,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  18, 2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  20, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */

static const yytype_int16 yyrline[] = {
    0,   105, 105, 109, 110, 117, 122, 130, 131, 137, 147, 150,
    158, 159, 163, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 184, 188, 191, 195, 202, 205, 208, 214, 215, 216, 217,
    218, 222, 226, 232, 238, 242, 245, 248, 251, 254, 260};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST(yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name(yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */

static const char *const yytname[] = {"\"end of file\"",
                                      "error",
                                      "\"invalid token\"",
                                      "TOKEN_INT",
                                      "TOKEN_CHAR",
                                      "TOKEN_FLOAT",
                                      "IDENTIFIER",
                                      "MAIN",
                                      "TYPE",
                                      "'*'",
                                      "'/'",
                                      "'+'",
                                      "'-'",
                                      "'%'",
                                      "','",
                                      "FUNCTION",
                                      "'='",
                                      "KW_VAR",
                                      "KW_MUT",
                                      "LPAREN",
                                      "RPAREN",
                                      "LBRACE",
                                      "RBRACE",
                                      "END_OF_LINE",
                                      "END_OF_FILE",
                                      "RETURN",
                                      "T_TRUE",
                                      "T_FALSE",
                                      "IF_TOKEN",
                                      "ELSE_TOKEN",
                                      "LOWEST_PRECEDENCE",
                                      "$accept",
                                      "program",
                                      "function_list",
                                      "function_decl",
                                      "arg_list",
                                      "functionCall",
                                      "call_list",
                                      "expr",
                                      "exprBlock",
                                      "expr_list",
                                      "ifExpr",
                                      "terminal",
                                      "variableAssignment",
                                      "variableReassignment",
                                      "variable",
                                      "arith_expr",
                                      "return_expr",
                                      YY_NULLPTR};

static const char *yysymbol_name(yysymbol_kind_t yysymbol) {
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-29)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */

static const yytype_int8 yypact[] = {
    -40, 9,   15,  -40, 24,  -40, -40, 30,  28,  -4,  46,  33,  20,  -40,
    -40, -40, 66,  33,  16,  69,  -40, -40, -40, -40, 57,  -1,  78,  -40,
    78,  -40, -40, 67,  -40, 1,   -40, 98,  -40, -40, -40, 71,  -40, -40,
    -40, 52,  79,  80,  103, -40, 50,  63,  78,  78,  78,  78,  78,  -40,
    78,  -40, 31,  50,  -40, 75,  79,  -40, 81,  -40, 89,  109, 83,  40,
    50,  78,  -40, 78,  84,  33,  50,  50,  78,  73,  50,  -13, -40, -40};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */

static const yytype_int8 yydefact[] = {
    3,  0,  0,  1,  0,  2,  4,  0,  0,  7,  0,  0,  0,  9,  26, 5,  0,
    0,  0,  0,  6,  32, 33, 34, 40, 0,  0,  25, 0,  35, 36, 0,  21, 0,
    17, 28, 20, 22, 23, 24, 19, 15, 8,  12, 0,  0,  0,  18, 46, 0,  0,
    0,  0,  0,  0,  27, 0,  10, 0,  14, 40, 0,  0,  16, 0,  43, 44, 41,
    42, 45, 39, 0,  11, 0,  0,  0,  13, 37, 0,  29, 38, 0,  30, 31};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] = {-40, -40, -40, -40, -40, -40,
                                      -40, -25, -11, -40, -16, 68,
                                      -40, -40, -39, -40, -40};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] = {
    0, 1, 2, 6, 12, 32, 58, 33, 34,

    /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
       positive, shift that token.  If negative, reduce the rule whose
       number is the opposite.  If YYTABLE_NINF, syntax error.  */

    static const yytype_int8 yytable[] = {
        15, 46, 35, 48, 10, 61, 20, 44, 14, 3,   50, 51,  52,  53,  54,  31,
        11, 45, 59, 21, 22, 23, 24, 74, 55, 65,  66, 67,  68,  69,  4,   70,
        7,  25, 16, 26, 8,  14, 27, 5,  17, 28,  29, 30,  31,  71,  76,  9,
        77, 50, 51, 72, 13, 80, 14, 21, 22, 23,  24, 50,  51,  52,  53,  54,
        79, 83, 21, 22, 23, 25, 82, 26, 57, 14,  19, 42,  43,  28,  29,  30,
        31, 21, 22, 23, 24, 60, 49, 56, 62, 29,  30, 73,  50,  51,  52,  25,
        54, 26, 50, 14, 78, 75, 81, 28, 29, 30,  31, -18, -18, -18, -18, -18,
        50, 51, 52, 53, 54, 64, 50, 51, 0,  -18, 54, 63};

static const yytype_int8 yycheck[] = {
    11, 26, 18, 28, 8,  44, 17, 8,  21, 0,  9,  10, 11, 12, 13, 28, 20, 18,
    43, 3,  4,  5,  6,  62, 23, 50, 51, 52, 53, 54, 15, 56, 8,  17, 14, 19,
    6,  21, 22, 24, 20, 25, 26, 27, 28, 14, 71, 19, 73, 9,  10, 20, 6,  78,
    21, 3,  4,  5,  6,  9,  10, 11, 12, 13, 75, 81, 3,  4,  5,  17, 81, 19,
    20, 21, 8,  6,  19, 25, 26, 27, 28, 3,  4,  5,  6,  6,  19, 16, 8,  26,
    27, 16, 9,  10, 11, 17, 13, 19, 9,  21, 16, 20, 29, 25, 26, 27, 28, 9,
    10, 11, 12, 13, 9,  10, 11, 12, 13, 49, 9,  10, -1, 23, 13, 20};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] = {
    0,  32, 33, 0,  15, 24, 34, 8,  6,  19, 8,  20, 35, 6,  21, 39, 14,
    20, 40, 8,  39, 3,  4,  5,  6,  17, 19, 22, 25, 26, 27, 28, 36, 38,
    39, 41, 42, 43, 44, 45, 46, 47, 6,  19, 8,  18, 38, 41, 38, 19, 9,
    10, 11, 12, 13, 23, 16, 20, 37, 38, 6,  45, 8,  20, 42, 38, 38, 38,
    38, 38, 38, 14, 20, 16, 45, 20, 38, 38, 16, 39, 38, 29, 39, 41};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] = {
    0,  31, 32, 33, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 37, 38,
    38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 40, 40, 40, 41, 41, 41,
    42, 42, 42, 42, 42, 43, 43, 44, 45, 46, 46, 46, 46, 46, 47};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
 */
static const yytype_int8 yyr2[] = {
    0, 2, 2, 0, 2, 6, 7, 0, 4, 2, 3, 4, 0, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1,
    1, 3, 0, 3, 2, 5, 7, 7, 1, 1, 1, 1, 1, 5, 6, 3, 1, 3, 3, 3, 3, 3, 2};

enum { YYENOMEM = -2 };

#define yyerrok (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYNOMEM goto yyexhaustedlab

#define YYRECOVERING() (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                                 \
  do                                                                           \
    if (yychar == YYEMPTY) {                                                   \
      yychar = (Token);                                                        \
      yylval = (Value);                                                        \
      YYPOPSTACK(yylen);                                                       \
      yystate = *yyssp;                                                        \
      goto yybackup;                                                           \
    } else {                                                                   \
      yyerror(YY_("syntax error: cannot back up"));                            \
      YYERROR;                                                                 \
    }                                                                          \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* Enable debugging if requested.  */
#if YYDEBUG

#ifndef YYFPRINTF
#include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#define YYFPRINTF fprintf
#endif

#define YYDPRINTF(Args)                                                        \
  do {                                                                         \
    if (yydebug)                                                               \
      YYFPRINTF Args;                                                          \
  } while (0)

#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                          \
  do {                                                                         \
    if (yydebug) {                                                             \
      YYFPRINTF(stderr, "%s ", Title);                                         \
      yy_symbol_print(stderr, Kind, Value);                                    \
      YYFPRINTF(stderr, "\n");                                                 \
    }                                                                          \
  } while (0)

/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void yy_symbol_value_print(FILE *yyo, yysymbol_kind_t yykind,
                                  YYSTYPE const *const yyvaluep) {
  FILE *yyoutput = yyo;
  YY_USE(yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE(yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void yy_symbol_print(FILE *yyo, yysymbol_kind_t yykind,
                            YYSTYPE const *const yyvaluep) {
  YYFPRINTF(yyo, "%s %s (", yykind < YYNTOKENS ? "token" : "nterm",
            yysymbol_name(yykind));

  yy_symbol_value_print(yyo, yykind, yyvaluep);
  YYFPRINTF(yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void yy_stack_print(yy_state_t *yybottom, yy_state_t *yytop) {
  YYFPRINTF(stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++) {
    int yybot = *yybottom;
    YYFPRINTF(stderr, " %d", yybot);
  }
  YYFPRINTF(stderr, "\n");
}

#define YY_STACK_PRINT(Bottom, Top)                                            \
  do {                                                                         \
    if (yydebug)                                                               \
      yy_stack_print((Bottom), (Top));                                         \
  } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void yy_reduce_print(yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule) {
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %d):\n", yyrule - 1,
            yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++) {
    YYFPRINTF(stderr, "   $%d = ", yyi + 1);
    yy_symbol_print(stderr, YY_ACCESSING_SYMBOL(+yyssp[yyi + 1 - yynrhs]),
                    &yyvsp[(yyi + 1) - (yynrhs)]);
    YYFPRINTF(stderr, "\n");
  }
}

#define YY_REDUCE_PRINT(Rule)                                                  \
  do {                                                                         \
    if (yydebug)                                                               \
      yy_reduce_print(yyssp, yyvsp, Rule);                                     \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
#define YYDPRINTF(Args) ((void)0)
#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
#define YY_STACK_PRINT(Bottom, Top)
#define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void yydestruct(const char *yymsg, yysymbol_kind_t yykind,
                       YYSTYPE *yyvaluep) {
  YY_USE(yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT(yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE(yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;

/*----------.
| yyparse.  |
`----------*/

int yyparse(void) {
  yy_state_fast_t yystate = 0;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus = 0;

  /* Refer to the stacks through separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* Their size.  */
  YYPTRDIFF_T yystacksize = YYINITDEPTH;

  /* The state stack: array, bottom, top.  */
  yy_state_t yyssa[YYINITDEPTH];
  yy_state_t *yyss = yyssa;
  yy_state_t *yyssp = yyss;

  /* The semantic value stack: array, bottom, top.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#define YYPOPSTACK(N) (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF((stderr, "Entering state %d\n", yystate));
  YY_ASSERT(0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST(yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT(yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
  {
    /* Get the current used size of the three stacks, in elements.  */
    YYPTRDIFF_T yysize = yyssp - yyss + 1;

#if defined yyoverflow
    {
      /* Give user a chance to reallocate the stack.  Use copies of
         these so that the &'s don't force the real ones into
         memory.  */
      yy_state_t *yyss1 = yyss;
      YYSTYPE *yyvs1 = yyvs;

      /* Each stack pointer address is followed by the size of the
         data in use in that stack, in bytes.  This used to be a
         conditional around just the two extra args, but that might
         be undefined if yyoverflow is a macro.  */
      yyoverflow(YY_("memory exhausted"), &yyss1, yysize * YYSIZEOF(*yyssp),
                 &yyvs1, yysize * YYSIZEOF(*yyvsp), &yystacksize);
      yyss = yyss1;
      yyvs = yyvs1;
    }
#else /* defined YYSTACK_RELOCATE */
    /* Extend the stack our own way.  */
    if (YYMAXDEPTH <= yystacksize)
      YYNOMEM;
    yystacksize *= 2;
    if (YYMAXDEPTH < yystacksize)
      yystacksize = YYMAXDEPTH;

    {
      yy_state_t *yyss1 = yyss;
      union yyalloc *yyptr =
          YY_CAST(union yyalloc *,
                  YYSTACK_ALLOC(YY_CAST(YYSIZE_T, YYSTACK_BYTES(yystacksize))));
      if (!yyptr)
        YYNOMEM;
      YYSTACK_RELOCATE(yyss_alloc, yyss);
      YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#undef YYSTACK_RELOCATE
      if (yyss1 != yyssa)
        YYSTACK_FREE(yyss1);
    }
#endif

    yyssp = yyss + yysize - 1;
    yyvsp = yyvs + yysize - 1;

    YY_IGNORE_USELESS_CAST_BEGIN
    YYDPRINTF(
        (stderr, "Stack size increased to %ld\n", YY_CAST(long, yystacksize)));
    YY_IGNORE_USELESS_CAST_END

    if (yyss + yystacksize - 1 <= yyssp)
      YYABORT;
  }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default(yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY) {
    YYDPRINTF((stderr, "Reading a token\n"));
    yychar = yylex();
  }

  if (yychar <= YYEOF) {
    yychar = YYEOF;
    yytoken = YYSYMBOL_YYEOF;
    YYDPRINTF((stderr, "Now at end of input.\n"));
  } else if (yychar == YYerror) {
    /* The scanner already issued an error message, process directly
       to error recovery.  But do not keep the error token as
       lookahead, it is too special and may lead us to an endless
       loop in error recovery. */
    yychar = YYUNDEF;
    yytoken = YYSYMBOL_YYerror;
    goto yyerrlab1;
  } else {
    yytoken = YYTRANSLATE(yychar);
    YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
  }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0) {
    if (yytable_value_is_error(yyn))
      goto yyerrlab;
    yyn = -yyn;
    goto yyreduce;
  }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;

/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;

/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1 - yylen];

  YY_REDUCE_PRINT(yyn);
  switch (yyn) {
  case 2: /* program: function_list END_OF_FILE  */

#line 105 "parser.y"
  {
    rootAST = new ProgramExpression(*(yyvsp[-1].funcList));
    return 0;
  }
#line 1176 "parser.cpp"
  break;

  case 3: /* function_list: %empty  */
#line 109 "parser.y"
  {
    (yyval.funcList) = new std::vector<FunctionDeclaration *>();
  }
#line 1182 "parser.cpp"
  break;

  case 4: /* function_list: function_list function_decl  */
#line 110 "parser.y"
  {
    (yyvsp[-1].funcList)
        ->push_back(static_cast<FunctionDeclaration *>((yyvsp[0].base)));
    (yyval.funcList) = (yyvsp[-1].funcList);
  }
#line 1191 "parser.cpp"
  break;

  case 5: /* function_decl: FUNCTION TYPE IDENTIFIER LPAREN RPAREN exprBlock  */
#line 117 "parser.y"
  {
    std::string type = *(yyvsp[-4].type);
    std::string identifier = *(yyvsp[-3].identifier);
    (yyval.base) =
        new FunctionDeclaration(identifier, type, (yyvsp[0].blockExpr));
  }
#line 1201 "parser.cpp"
  break;

  case 6: /* function_decl: FUNCTION TYPE IDENTIFIER LPAREN arg_list RPAREN
             exprBlock  */
#line 122 "parser.y"
  {
    std::string type = *(yyvsp[-5].type);
    std::string identifier = *(yyvsp[-4].identifier);
    (yyval.base) = new FunctionDeclaration(
        identifier, type, (yyvsp[0].blockExpr), *(yyvsp[-2].argList));
  }
#line 1211 "parser.cpp"
  break;

  case 7: /* arg_list: %empty  */
#line 130 "parser.y"
  {
    (yyval.argList) = new std::vector<std::pair<std::string, std::string>>();
  }
#line 1217 "parser.cpp"
  break;

  case 8: /* arg_list: arg_list ',' TYPE IDENTIFIER  */
#line 131 "parser.y"
  {
    std::string type = *(yyvsp[-1].type);
    std::string identifier = *(yyvsp[0].identifier);
    (yyvsp[-3].argList)->push_back(std::make_pair(type, identifier));
    (yyval.argList) = (yyvsp[-3].argList);
  }
#line 1228 "parser.cpp"
  break;

  case 9: /* arg_list: TYPE IDENTIFIER  */
#line 137 "parser.y"
  {
    std::string type = *(yyvsp[-1].type);
    std::string identifier = *(yyvsp[0].identifier);
    auto list = new std::vector<std::pair<std::string, std::string>>();
    list->push_back(std::make_pair(type, identifier));
    (yyval.argList) = list;
  }
#line 1240 "parser.cpp"
  break;

  case 10: /* functionCall: IDENTIFIER LPAREN RPAREN  */
#line 147 "parser.y"
  {
    (yyval.base) = new FunctionCall(*(yyvsp[-2].identifier));
  }
#line 1248 "parser.cpp"
  break;

  case 11: /* functionCall: IDENTIFIER LPAREN call_list RPAREN  */
#line 150 "parser.y"
  {
    std::vector<BaseExpression *> args = *(yyvsp[-1].exprList);
    std::string identifier = *(yyvsp[-3].identifier);
    (yyval.base) = new FunctionCall(identifier, args);
  }
#line 1258 "parser.cpp"
  break;

  case 12: /* call_list: %empty  */
#line 158 "parser.y"
  {
    (yyval.exprList) = new std::vector<BaseExpression *>();
  }
#line 1264 "parser.cpp"
  break;

  case 13: /* call_list: call_list ',' expr  */
#line 159 "parser.y"
  {
    (yyvsp[-2].exprList)->push_back((yyvsp[0].base));
    (yyval.exprList) = (yyvsp[-2].exprList);
  }
#line 1273 "parser.cpp"
  break;

  case 14: /* call_list: expr  */
#line 163 "parser.y"
  {
    auto list = new std::vector<BaseExpression *>();
    list->push_back((yyvsp[0].base));
    (yyval.exprList) = list;
  }
#line 1283 "parser.cpp"
  break;

  case 15: /* expr: return_expr  */
#line 171 "parser.y"
  {
    (yyval.base) = (yyvsp[0].base);
  }
#line 1289 "parser.cpp"
  break;

  case 16: /* expr: LPAREN expr RPAREN  */
#line 172 "parser.y"
  {
    (yyval.base) = (yyvsp[-1].base);
  }
#line 1295 "parser.cpp"
  break;

  case 17: /* expr: exprBlock  */
#line 173 "parser.y"
  {
    (yyval.base) = (yyvsp[0].blockExpr);
  }
#line 1301 "parser.cpp"
  break;

  case 18: /* expr: ifExpr  */
#line 174 "parser.y"
  {
    (yyval.base) = (yyvsp[0].base);
  }
#line 1307 "parser.cpp"
  break;

  case 19: /* expr: arith_expr  */
#line 175 "parser.y"
  {
    (yyval.base) = (yyvsp[0].base);
  }
#line 1313 "parser.cpp"
  break;

  case 20: /* expr: terminal  */
#line 176 "parser.y"
  {
    (yyval.base) = (yyvsp[0].terminal);
  }
#line 1319 "parser.cpp"
  break;

  case 21: /* expr: functionCall  */
#line 177 "parser.y"
  {
    (yyval.base) = (yyvsp[0].base);
  }
#line 1325 "parser.cpp"
  break;

  case 22: /* expr: variableAssignment  */
#line 178 "parser.y"
  {
    (yyval.base) = (yyvsp[0].varAssign);
  }
#line 1331 "parser.cpp"
  break;

  case 23: /* expr: variableReassignment  */
#line 179 "parser.y"
  {
    (yyval.base) = (yyvsp[0].varReassign);
  }
#line 1337 "parser.cpp"
  break;

  case 24: /* expr: variable  */
#line 180 "parser.y"
  {
    (yyval.base) = (yyvsp[0].var);
  }
#line 1343 "parser.cpp"
  break;

  case 25: /* exprBlock: LBRACE expr_list RBRACE  */
#line 184 "parser.y"
  {
    (yyval.blockExpr) = new BlockExpression(*(yyvsp[-1].block));
  }
#line 1349 "parser.cpp"
  break;

  case 26: /* expr_list: %empty  */
#line 188 "parser.y"
  {
    (yyval.block) = new std::vector<BaseExpression *>();
  }
#line 1357 "parser.cpp"
  break;

  case 27: /* expr_list: expr_list expr END_OF_LINE  */
#line 191 "parser.y"
  {
    (yyvsp[-2].block)->push_back((yyvsp[-1].base));
    (yyval.block) = (yyvsp[-2].block);
  }
#line 1366 "parser.cpp"
  break;

  case 28: /* expr_list: expr_list ifExpr  */
#line 195 "parser.y"
  {
    (yyvsp[-1].block)->push_back((yyvsp[0].base));
    (yyval.block) = (yyvsp[-1].block);
  }
#line 1375 "parser.cpp"
  break;

  case 29: /* ifExpr: IF_TOKEN LPAREN terminal RPAREN exprBlock  */
#line 202 "parser.y"
  {
    (yyval.base) =
        new IfExpression((yyvsp[-2].terminal), (yyvsp[0].blockExpr), nullptr);
  }
#line 1383 "parser.cpp"
  break;

  case 30: /* ifExpr: IF_TOKEN LPAREN terminal RPAREN exprBlock ELSE_TOKEN
              exprBlock  */
#line 205 "parser.y"
  {
    (yyval.base) = new IfExpression((yyvsp[-4].terminal), (yyvsp[-2].blockExpr),
                                    (yyvsp[0].blockExpr));
  }
#line 1391 "parser.cpp"
  break;

  case 31: /* ifExpr: IF_TOKEN LPAREN terminal RPAREN exprBlock ELSE_TOKEN
              ifExpr  */
#line 208 "parser.y"
  {
    (yyval.base) = new IfExpression((yyvsp[-4].terminal), (yyvsp[-2].blockExpr),
                                    (yyvsp[0].base));
  }
#line 1399 "parser.cpp"
  break;

  case 32: /* terminal: TOKEN_INT  */
#line 214 "parser.y"
  {
    (yyval.terminal) = new TerminalExpression((yyvsp[0].num));
  }
#line 1405 "parser.cpp"
  break;

  case 33: /* terminal: TOKEN_CHAR  */
#line 215 "parser.y"
  {
    (yyval.terminal) = new TerminalExpression((yyvsp[0].chr));
  }
#line 1411 "parser.cpp"
  break;

  case 34: /* terminal: TOKEN_FLOAT  */
#line 216 "parser.y"
  {
    (yyval.terminal) = new TerminalExpression((yyvsp[0].flt));
  }
#line 1417 "parser.cpp"
  break;

  case 35: /* terminal: T_TRUE  */
#line 217 "parser.y"
  {
    (yyval.terminal) = new TerminalExpression(true);
  }
#line 1423 "parser.cpp"
  break;

  case 36: /* terminal: T_FALSE  */
#line 218 "parser.y"
  {
    (yyval.terminal) = new TerminalExpression(false);
  }
#line 1429 "parser.cpp"
  break;

  case 37: /* variableAssignment: KW_VAR TYPE variable '=' expr  */
#line 222 "parser.y"
  {
    std::string varType = *(yyvsp[-3].type);
    (yyval.varAssign) = new VariableAssignmentExpression(
        (yyvsp[0].base), (yyvsp[-2].var), false, varType);
  }
#line 1438 "parser.cpp"
  break;

  case 38: /* variableAssignment: KW_VAR KW_MUT TYPE variable '=' expr  */
#line 226 "parser.y"
  {
    std::string varType = *(yyvsp[-3].type);
    (yyval.varAssign) = new VariableAssignmentExpression(
        (yyvsp[0].base), (yyvsp[-2].var), true, varType);
  }
#line 1447 "parser.cpp"
  break;

  case 39: /* variableReassignment: variable '=' expr  */
#line 232 "parser.y"
  {
    (yyval.varReassign) =
        new VariableReassignmentExpression((yyvsp[0].base), (yyvsp[-2].var));
  }
#line 1455 "parser.cpp"
  break;

  case 40: /* variable: IDENTIFIER  */
#line 238 "parser.y"
  {
    (yyval.var) = new VariableExpression(*(yyvsp[0].identifier));
  }
#line 1461 "parser.cpp"
  break;

  case 41: /* arith_expr: expr '+' expr  */
#line 242 "parser.y"
  {
    (yyval.base) = BinaryExpression::createBinaryExpression(
        (yyvsp[-2].base), '+', (yyvsp[0].base));
  }
#line 1469 "parser.cpp"
  break;

  case 42: /* arith_expr: expr '-' expr  */
#line 245 "parser.y"
  {
    (yyval.base) = BinaryExpression::createBinaryExpression(
        (yyvsp[-2].base), '-', (yyvsp[0].base));
  }
#line 1477 "parser.cpp"
  break;

  case 43: /* arith_expr: expr '*' expr  */
#line 248 "parser.y"
  {
    (yyval.base) = BinaryExpression::createBinaryExpression(
        (yyvsp[-2].base), '*', (yyvsp[0].base));
  }
#line 1485 "parser.cpp"
  break;

  case 44: /* arith_expr: expr '/' expr  */
#line 251 "parser.y"
  {
    (yyval.base) = BinaryExpression::createBinaryExpression(
        (yyvsp[-2].base), '/', (yyvsp[0].base));
  }
#line 1493 "parser.cpp"
  break;

  case 45: /* arith_expr: expr '%' expr  */
#line 254 "parser.y"
  {
    (yyval.base) = BinaryExpression::createBinaryExpression(
        (yyvsp[-2].base), '%', (yyvsp[0].base));
  }
#line 1501 "parser.cpp"
  break;

  case 46: /* return_expr: RETURN expr  */
#line 260 "parser.y"
  {
    (yyval.base) = new ReturnExpression((yyvsp[0].base));
  }
#line 1507 "parser.cpp"
  break;

#line 1511 "parser.cpp"

  case 44: /* arith_expr: expr EQ expr  */
#line 251 "parser.y"
  {
    (yyval.base) = BinaryExpression::createBinaryExpression(
        (yyvsp[-2].base), "==", (yyvsp[0].base));
  }
#line 1511 "parser.cpp"
  break;

  case 45: /* arith_expr: expr NEQ expr  */
#line 254 "parser.y"
  {
    (yyval.base) = BinaryExpression::createBinaryExpression(
        (yyvsp[-2].base), "!=", (yyvsp[0].base));
  }
#line 1519 "parser.cpp"
  break;

  case 46: /* return_expr: RETURN expr  */
#line 260 "parser.y"
  {
    (yyval.base) = new ReturnExpression((yyvsp[0].base));
  }
#line 1525 "parser.cpp"
  break;

#line 1529 "parser.cpp"

  default:
    break;
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT("-> $$ =", YY_CAST(yysymbol_kind_t, yyr1[yyn]), &yyval,
                  &yyloc);

  YYPOPSTACK(yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
                   ? yytable[yyi]
                   : yydefgoto[yylhs]);
  }

  goto yynewstate;

/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE(yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus) {
    ++yynerrs;
    yyerror(YY_("syntax error"));
  }

  if (yyerrstatus == 3) {
    /* If just tried and failed to reuse lookahead token after an
       error, discard it.  */

    if (yychar <= YYEOF) {
      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        YYABORT;
    } else {
      yydestruct("Error: discarding", yytoken, &yylval);
      yychar = YYEMPTY;
    }
  }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;

/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;

/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3; /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;) {
    yyn = yypact[yystate];
    if (!yypact_value_is_default(yyn)) {
      yyn += YYSYMBOL_YYerror;
      if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror) {
        yyn = yytable[yyn];
        if (0 < yyn)
          break;
      }
    }

    /* Pop the current state because it cannot handle the error token.  */
    if (yyssp == yyss)
      YYABORT;

    yydestruct("Error: popping", YY_ACCESSING_SYMBOL(yystate), yyvsp);
    YYPOPSTACK(1);
    yystate = *yyssp;
    YY_STACK_PRINT(yyss, yyssp);
  }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Shift the error token.  */
  YY_SYMBOL_PRINT("Shifting", YY_ACCESSING_SYMBOL(yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;

/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;

/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror(YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;

/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY) {
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = YYTRANSLATE(yychar);
    yydestruct("Cleanup: discarding lookahead", yytoken, &yylval);
  }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK(yylen);
  YY_STACK_PRINT(yyss, yyssp);
  while (yyssp != yyss) {
    yydestruct("Cleanup: popping", YY_ACCESSING_SYMBOL(+*yyssp), yyvsp);
    YYPOPSTACK(1);
  }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE(yyss);
#endif

  return yyresult;
}

#line 263 "parser.y"

/* Epilogue */
void yyerror(const char *s) {
  /* if mainFunc tell the user that the main function is missing */
  // if (rootAST == nullptr) {
  //     std::cout << "Error: main function is missing" << std::endl;
  // }
  // else {
  std::cout << "Error: " << s << std::endl;
  // }
}
