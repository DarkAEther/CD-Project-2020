/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "pointer.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "./lib/queue.h"
#include "./lib/lookup.h"
#include "./lib/quadruple.h"
#include "./lib/symtab_util.h"
#include "./lib/optimizer.h"
#include <string.h>
#include <assert.h>
void yyerror();
int line_num=1;  
int error_count = 0;  
extern int scope;
extern int max_depth;
NODE* st[100];
QUEUE queue;
int top;
int temp_count;
int label_count;
QUAD* head_quad;

char * temp_value;
char* CUSTYPES[] ={"ID\0","STRING\0","DECIMAL\0","FLOAT\0","CHARACTER\0","BOOLEAN\0","OP\0","KW\0"};

NODE* get_new_node(char* token,int child_nodes,NODE** children,enum TYPE type){
  NODE* newnode = (NODE*)malloc(sizeof(NODE));
  newnode->value.value.string = (char*)(malloc(sizeof(char)*strlen(token)+1));
  strcpy(newnode->value.value.string,token);
  newnode->child_count = child_nodes;
  newnode->children = children;
  newnode->type = type;
  return newnode;
}

NODE* mod_node(NODE* original,int child_nodes,NODE** children){
  original->child_count = child_nodes;
  original->children = children;
  return original;
}

void display_AST_BFS(NODE* root){
  if (error_count > 0){
    printf("Semantic Errors, Cannot build parse tree\n");
    return;
  }
  enqueue(&queue,root);
  NODE* current;int currlvl = 0;
  while (queue.queue_front!= -1){
    current = dequeue(&queue);
    assert (current !=NULL);
    if (currlvl != current->level){
      printf("\n");
      currlvl = current->level;
    }
    printf(" %s ",current->value.value.string);fflush(stdout);
    for (int i = 0;i < current->child_count;i++){
      current->children[i]->level = currlvl+1;
      enqueue(&queue,current->children[i]);
    }
  }
  printf("\n");
}


#line 133 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KW_AS = 258,
    KW_BREAK = 259,
    KW_CONST = 260,
    KW_CONTINUE = 261,
    KW_CRATE = 262,
    KW_ELSE = 263,
    KW_ENUM = 264,
    KW_EXTERN = 265,
    KW_FALSE = 266,
    KW_FN = 267,
    KW_FOR = 268,
    KW_IF = 269,
    KW_IMPL = 270,
    KW_IN = 271,
    KW_LET = 272,
    KW_MATCH = 273,
    KW_MOD = 274,
    KW_MOVE = 275,
    KW_MUT = 276,
    KW_PUB = 277,
    KW_REF = 278,
    KW_RETURN = 279,
    KW_SELFVALUE = 280,
    KW_SELFTYPE = 281,
    KW_STATIC = 282,
    KW_STRUCT = 283,
    KW_SUPER = 284,
    KW_TRAIT = 285,
    KW_TRUE = 286,
    KW_TYPE = 287,
    KW_UNSAFE = 288,
    KW_USE = 289,
    KW_WHERE = 290,
    KW_WHILE = 291,
    KW_LOOP = 292,
    CHARACTER = 293,
    STRING = 294,
    RAW_STRING = 295,
    BYTE = 296,
    BYTE_STRING = 297,
    RAW_BYTE_STRING = 298,
    DECIMAL = 299,
    HEX_INT = 300,
    OCTAL_INT = 301,
    BIN_INT = 302,
    FLOAT = 303,
    ARITH = 304,
    BITWISE = 305,
    ASSIGN_OPS = 306,
    ASSIGN = 307,
    RELATIONAL = 308,
    IDENTIFIER = 309,
    STMT_TERMINATOR = 310,
    RANGE = 311,
    ERROR = 312,
    OPEN_BLOCK = 313,
    CLOSE_BLOCK = 314,
    OPEN_PARANTHESIS = 315,
    CLOSE_PARANTHESIS = 316,
    COMMA = 317,
    KW_MAIN = 318,
    KW_PRINTLN = 319,
    EOFI = 320
  };
#endif
/* Tokens.  */
#define KW_AS 258
#define KW_BREAK 259
#define KW_CONST 260
#define KW_CONTINUE 261
#define KW_CRATE 262
#define KW_ELSE 263
#define KW_ENUM 264
#define KW_EXTERN 265
#define KW_FALSE 266
#define KW_FN 267
#define KW_FOR 268
#define KW_IF 269
#define KW_IMPL 270
#define KW_IN 271
#define KW_LET 272
#define KW_MATCH 273
#define KW_MOD 274
#define KW_MOVE 275
#define KW_MUT 276
#define KW_PUB 277
#define KW_REF 278
#define KW_RETURN 279
#define KW_SELFVALUE 280
#define KW_SELFTYPE 281
#define KW_STATIC 282
#define KW_STRUCT 283
#define KW_SUPER 284
#define KW_TRAIT 285
#define KW_TRUE 286
#define KW_TYPE 287
#define KW_UNSAFE 288
#define KW_USE 289
#define KW_WHERE 290
#define KW_WHILE 291
#define KW_LOOP 292
#define CHARACTER 293
#define STRING 294
#define RAW_STRING 295
#define BYTE 296
#define BYTE_STRING 297
#define RAW_BYTE_STRING 298
#define DECIMAL 299
#define HEX_INT 300
#define OCTAL_INT 301
#define BIN_INT 302
#define FLOAT 303
#define ARITH 304
#define BITWISE 305
#define ASSIGN_OPS 306
#define ASSIGN 307
#define RELATIONAL 308
#define IDENTIFIER 309
#define STMT_TERMINATOR 310
#define RANGE 311
#define ERROR 312
#define OPEN_BLOCK 313
#define CLOSE_BLOCK 314
#define OPEN_PARANTHESIS 315
#define CLOSE_PARANTHESIS 316
#define COMMA 317
#define KW_MAIN 318
#define KW_PRINTLN 319
#define EOFI 320

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 67 "pointer.y" /* yacc.c:355  */

  char *str;
  struct node* node;

#line 308 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 325 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   116

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  45
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  92

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      67,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    66,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   140,   141,   142,   143,   145,   152,   157,
     162,   165,   168,   170,   171,   172,   173,   175,   236,   357,
     358,   360,   362,   363,   364,   365,   366,   368,   369,   370,
     372,   374,   476,   478,   479,   481,   481,   491,   491,   497,
     499,   499,   499,   510,   510,   510
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_AS", "KW_BREAK", "KW_CONST",
  "KW_CONTINUE", "KW_CRATE", "KW_ELSE", "KW_ENUM", "KW_EXTERN", "KW_FALSE",
  "KW_FN", "KW_FOR", "KW_IF", "KW_IMPL", "KW_IN", "KW_LET", "KW_MATCH",
  "KW_MOD", "KW_MOVE", "KW_MUT", "KW_PUB", "KW_REF", "KW_RETURN",
  "KW_SELFVALUE", "KW_SELFTYPE", "KW_STATIC", "KW_STRUCT", "KW_SUPER",
  "KW_TRAIT", "KW_TRUE", "KW_TYPE", "KW_UNSAFE", "KW_USE", "KW_WHERE",
  "KW_WHILE", "KW_LOOP", "CHARACTER", "STRING", "RAW_STRING", "BYTE",
  "BYTE_STRING", "RAW_BYTE_STRING", "DECIMAL", "HEX_INT", "OCTAL_INT",
  "BIN_INT", "FLOAT", "ARITH", "BITWISE", "ASSIGN_OPS", "ASSIGN",
  "RELATIONAL", "IDENTIFIER", "STMT_TERMINATOR", "RANGE", "ERROR",
  "OPEN_BLOCK", "CLOSE_BLOCK", "OPEN_PARANTHESIS", "CLOSE_PARANTHESIS",
  "COMMA", "KW_MAIN", "KW_PRINTLN", "EOFI", "';'", "'\\n'", "$accept",
  "start", "Main", "Blk", "Code", "Eval", "Exp", "id", "Val", "op",
  "equals", "Var_dec", "Out", "Body", "If", "$@1", "Else", "$@2", "While",
  "$@3", "$@4", "For", "$@5", "$@6", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,    59,    10
};
# endif

#define YYPACT_NINF -63

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-63)))

#define YYTABLE_NINF -13

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      45,   -37,   -62,   -49,   -22,   -49,   -63,   -63,   -63,   -63,
     -63,   -63,   -22,   -51,   -63,    11,   -50,   -63,    52,   -63,
     -63,   -13,   -63,   -63,    52,    52,    52,   -63,   -63,   -40,
     -63,     5,   -63,   -46,   -29,   -22,   -36,     9,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,   -22,   -22,   -63,   -63,   -63,
     -34,   -20,   -23,   -22,   -63,   -63,   -10,    -8,   -63,    -1,
      -3,   -63,    52,     8,     6,   -20,    12,   -63,    52,    14,
      17,   -63,    52,   -63,   -63,    18,   -20,    60,    19,   -63,
     -63,   -63,   -63,   -63,    13,    15,    52,    52,    20,    21,
     -63,   -63
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    40,    26,    23,    24,
      25,    22,     0,     0,     4,     0,     0,     3,    12,    13,
      15,    20,    16,    14,    12,    12,    12,     5,     6,     0,
      21,     0,    35,    20,     0,     0,     0,     0,     1,     2,
       8,    27,    28,    30,    29,     0,     0,     9,    10,    11,
       0,     0,     0,     0,    41,    19,    33,     0,    18,     0,
       0,    43,    12,     0,     0,     0,     0,    17,    12,     0,
       0,    31,    12,    34,    32,     0,     0,    39,     0,     7,
      44,    37,    36,    42,     0,     0,    12,    12,     0,     0,
      45,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -63,   -12,   -63,   -63,    -2,    77,    -4,   -63,
      51,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    15,    16,    17,    18,    19,    20,    31,    21,    45,
      46,    22,    23,    57,    24,    52,    82,    85,    25,    35,
      64,    26,    69,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      33,    29,    32,    41,    42,    30,    40,    44,    33,    37,
      36,    38,    47,    48,    49,    39,     7,     8,     7,     8,
      50,    51,     9,    43,     9,    55,    10,    60,    10,    27,
      28,    33,    11,    54,    11,    62,    41,    42,    12,    43,
      44,    33,    33,    58,    59,   -12,     1,    61,    56,    33,
      70,    63,    65,    66,    67,    68,    75,     2,     3,     4,
      78,    73,     5,    71,    72,     3,     4,    74,    81,     5,
      76,    86,    80,    87,    88,    89,    77,    79,    83,    90,
      91,     6,    34,     7,     8,    53,     0,     0,     6,     9,
       7,     8,     0,    10,     0,     0,     9,     0,     0,    11,
      10,     0,     0,     0,     0,    12,    11,     0,     0,    13,
      14,     0,    12,     0,     0,     0,    13
};

static const yytype_int8 yycheck[] =
{
       4,    63,     4,    49,    50,    54,    18,    53,    12,    60,
      12,     0,    24,    25,    26,    65,    38,    39,    38,    39,
      60,    16,    44,    52,    44,    61,    48,    61,    48,    66,
      67,    35,    54,    35,    54,    58,    49,    50,    60,    52,
      53,    45,    46,    45,    46,     0,     1,    51,    39,    53,
      62,    53,    62,    61,    55,    58,    68,    12,    13,    14,
      72,    65,    17,    55,    58,    13,    14,    55,     8,    17,
      56,    58,    76,    58,    86,    87,    59,    59,    59,    59,
      59,    36,     5,    38,    39,    34,    -1,    -1,    36,    44,
      38,    39,    -1,    48,    -1,    -1,    44,    -1,    -1,    54,
      48,    -1,    -1,    -1,    -1,    60,    54,    -1,    -1,    64,
      65,    -1,    60,    -1,    -1,    -1,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    12,    13,    14,    17,    36,    38,    39,    44,
      48,    54,    60,    64,    65,    69,    70,    71,    72,    73,
      74,    76,    79,    80,    82,    86,    89,    66,    67,    63,
      54,    75,    74,    76,    75,    87,    74,    60,     0,    65,
      71,    49,    50,    52,    53,    77,    78,    71,    71,    71,
      60,    16,    83,    78,    74,    61,    39,    81,    74,    74,
      61,    76,    58,    74,    88,    62,    61,    55,    58,    90,
      71,    55,    58,    76,    55,    71,    56,    59,    71,    59,
      76,     8,    84,    59,    91,    85,    58,    58,    71,    71,
      59,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    69,    69,    69,    69,    70,    71,    71,
      71,    71,    71,    72,    72,    72,    72,    73,    74,    74,
      74,    75,    76,    76,    76,    76,    76,    77,    77,    77,
      78,    79,    80,    81,    81,    83,    82,    85,    84,    84,
      87,    88,    86,    90,    91,    89
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     2,     7,     2,     2,
       2,     2,     0,     1,     1,     1,     1,     4,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     1,     3,     0,     7,     0,     5,     0,
       0,     0,     7,     0,     0,    11
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 139 "pointer.y" /* yacc.c:1646  */
    {printf("\n-------------DONE----------------\n"); }
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 145 "pointer.y" /* yacc.c:1646  */
    {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*7);
  kids[0]= get_new_node("FN",0,NULL,KW); kids[1] = get_new_node("MAIN",0,NULL,KW); kids[2]=get_new_node("(",0,NULL,KW); kids[3] = get_new_node(")",0,NULL,KW); kids[5] = (yyvsp[-1].node);kids[4] = get_new_node("{",0,NULL,KW); kids[6] = get_new_node("}",0,NULL,KW);
  (yyval.node) = get_new_node("MAIN",7,kids,KW);
  //display_AST_BFS($$);
}
#line 1492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 152 "pointer.y" /* yacc.c:1646  */
    {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= (yyvsp[-1].node); kids[1] = (yyvsp[0].node); 
  (yyval.node) = get_new_node("BLK",2,kids,KW);
}
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 157 "pointer.y" /* yacc.c:1646  */
    {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= (yyvsp[-1].node); kids[1] = (yyvsp[0].node); 
  (yyval.node) = get_new_node("BLK",2,kids,KW);
}
#line 1512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 162 "pointer.y" /* yacc.c:1646  */
    { NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= (yyvsp[-1].node); kids[1] = (yyvsp[0].node); 
  (yyval.node) = get_new_node("BLK",2,kids,KW);}
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 165 "pointer.y" /* yacc.c:1646  */
    {NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= (yyvsp[-1].node); kids[1] = (yyvsp[0].node); 
  (yyval.node) = get_new_node("BLK",2,kids,KW);}
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 168 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node("LAMBDA",0,NULL,KW);}
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 170 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 171 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 172 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 173 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 175 "pointer.y" /* yacc.c:1646  */
    {
  if ((yyvsp[-3].node)->type != ID){
    printf("ERROR - LHS must be an identifier. Given %s Line no. %d\n",CUSTYPES[(yyvsp[-3].node)->type],yylineno);
    error_count++;
    (yyval.node) = get_new_node("ERROR",0,NULL,KW);
  }else{
    NODE ** kids = (NODE**)malloc(sizeof(NODE*)*2);
    NODE** assign_kids = (NODE**)malloc(sizeof(NODE*)*2);
    assign_kids[0] = (yyvsp[-3].node); assign_kids[1] = (yyvsp[-1].node);
    kids[0] = get_new_node("ASSIGN",2,assign_kids,KW); kids[1] = get_new_node(";",0,NULL,KW);
    (yyval.node) = get_new_node("ASSIGNMENT",2,kids,KW);
    //Write changes to ST
    struct id* record = lookup_ST_declared(&symbolTable,(yyvsp[-3].node)->value.value.string,scope);
    if (record != NULL){
        //printf("ASSIGN TYPE %s #%s#\n",record->name,record->type);
        if (strcmp(record->type,"") != 0){
                //variable is declared
                //strcpy(record->type,CUSTYPES[$3->type]);
                if ((yyvsp[-1].node)->type == DEC){
                  (yyvsp[-3].node)->type = DEC;
                  record->value.discriminator = 0;
                  strcpy(record->type,"DECIMAL");
                }
                if ((yyvsp[-1].node)->type == FLT){
                  (yyvsp[-3].node)->type = FLT;
                  record->value.discriminator = 1;
                  strcpy(record->type,"FLOAT");
                }
                if ((yyvsp[-1].node)->type == CHAR){
                  (yyvsp[-3].node)->type = CHAR;
                  record->value.discriminator = 2;
                  strcpy(record->type,"CHARACTER");
                }
                if ((yyvsp[-1].node)->type == STR){
                  (yyvsp[-3].node)->type = STR;
                  record->value.discriminator = 3;
                  strcpy(record->type,"STRING");
                }
                (yyvsp[-3].node)->PTR.st_ptr = record;
          }
          
    }else{
      printf("ERROR - Variable use before declaration %s on line %d\n",(yyvsp[-3].node)->value.value.string,yylineno);
      error_count++;
    } 
  }
  if ((yyvsp[-1].node)->core_type == VAL){
    struct literal* assigned = lookup_LT(&symbolTable,(yyvsp[-1].node)->value.value.string);
    if (assigned != NULL){
      (yyvsp[-1].node)->PTR.lt_ptr = assigned;
    }
  }
  if ((yyvsp[-1].node)->core_type == ID){
    struct id* record = lookup_ST_declared(&symbolTable,(yyvsp[-1].node)->value.value.string,scope);
    if (record != NULL){
      (yyvsp[-1].node)->PTR.st_ptr = record;
    }
  }
  codegen_assign(scope,st,&top,&head_quad);
}
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 236 "pointer.y" /* yacc.c:1646  */
    {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0] = (yyvsp[-2].node); kids[1] = (yyvsp[0].node); 
  (yyval.node) = mod_node((yyvsp[-1].node),2,kids);
  if ((yyvsp[-1].node)->type == REL){
      (yyval.node)->type = BOOL;
  }
  if ((yyvsp[-2].node)->type == ID){
    struct id* record = lookup_ST_declared(&symbolTable,(yyvsp[-2].node)->value.value.string,scope);
    if (record != NULL){
      if (strcmp(record->type,"") != 0){
            //declared var
            if (record->value.discriminator == 0){
              (yyvsp[-2].node)->type = DEC;
            }
            if (record->value.discriminator == 1){
              (yyvsp[-2].node)->type = FLT;
            }
            if (record->value.discriminator == 2){
              (yyvsp[-2].node)->type = CHAR;
            }
            if (record->value.discriminator == 3){
              (yyvsp[-2].node)->type = STR;
            }
      }
       (yyvsp[-2].node)->PTR.st_ptr = record;
    }
  }else{
    //literal
    struct literal * lit = lookup_LT(&symbolTable,(yyvsp[-2].node)->value.value.string);
    if (lit!=NULL){
      //literal found
      //printf("LITERAL 1 FOUND %d\n",lit->value.integer);
      (yyvsp[-2].node)->PTR.lt_ptr = lit;
      //printf("DISCRIMINATOR 1 %d\n",lit->discriminator);
      if (lit->discriminator == 0){
        (yyvsp[-2].node)->type = DEC;
      }
      if (lit->discriminator == 1){
        (yyvsp[-2].node)->type = FLT;
      }
      if (lit->discriminator == 2){
        (yyvsp[-2].node)->type = CHAR;
      }
      if (lit->discriminator == 3){
        (yyvsp[-2].node)->type = STR;
      }
    }
  }
  if ((yyvsp[0].node)->type == ID){
    struct id* record = lookup_ST_declared(&symbolTable,(yyvsp[0].node)->value.value.string,scope);
    if (record != NULL){
        // The variable has been 
        //printf("TYPE 3 #%s#\n",record->type);
        if (strcmp(record->type,"") != 0){
            //declared var
            if (record->value.discriminator == 0){
              (yyvsp[0].node)->type = DEC;
            }
            if (record->value.discriminator == 1){
              (yyvsp[0].node)->type = FLT;
            }
            if (record->value.discriminator == 2){
              (yyvsp[0].node)->type = CHAR;
            }
            if (record->value.discriminator == 3){
              (yyvsp[0].node)->type = STR;
            }
        }
        (yyvsp[0].node)->PTR.st_ptr = record;
      }
  }else{
    struct literal * lit = lookup_LT(&symbolTable,(yyvsp[0].node)->value.value.string);
    if (lit!=NULL){
      //literal found
      //printf("LITERAL 3 FOUND %d\n",lit->value.integer);
      (yyvsp[0].node)->PTR.lt_ptr = lit;
      //printf("DISCRIMINATOR 3 %d\n",lit->discriminator);
      if (lit->discriminator == 0){
        (yyvsp[0].node)->type = DEC;
      }
      if (lit->discriminator  == 1){
        (yyvsp[0].node)->type = FLT;
      }
      if (lit->discriminator  == 2){
        (yyvsp[0].node)->type = CHAR;
      }
      if (lit->discriminator  == 3){
        (yyvsp[0].node)->type = STR;
      }
    }
  }
  if ((yyvsp[-1].node)->type == NUM){
    int set = 0;
    if ((yyvsp[-2].node)->type == ID){
        printf("ERROR - Variable use before declaration - %s Line No - %d\n",(yyvsp[-2].node)->value.value.string,yylineno);
        error_count++;
    }
    if ((yyvsp[0].node)->type == ID){
        printf("ERROR - Variable use before declaration - %s Line No - %d\n",(yyvsp[0].node)->value.value.string,yylineno);
        error_count++;
    }
    if ((yyvsp[-2].node)->type == DEC && (yyvsp[0].node)->type == FLT){
        (yyval.node)->type = FLT;set = 1;
    }
    if ((yyvsp[-2].node)->type == FLT && (yyvsp[0].node)->type == DEC){
        (yyval.node)->type = FLT;set = 1;
    }
    if ((yyvsp[-2].node)->type == DEC && (yyvsp[0].node)->type == DEC){
      (yyval.node)->type = DEC;set=1;
    }
    if ((yyvsp[-2].node)->type == FLT && (yyvsp[0].node)->type == FLT){
      (yyval.node)->type = FLT;set=1;
    }
    if (set!= 1){
      error_count++;
      printf("ERROR-  CANNOT PERFORM %s operation on %s and %s Line No- %d\n",(yyvsp[-1].node)->value.value.string, CUSTYPES[(yyvsp[-2].node)->type], CUSTYPES[(yyvsp[0].node)->type], yylineno);
    }
  }
  codegen(st,&top,&temp_count,yylineno,&head_quad,scope,&symbolTable);
}
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 357 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 358 "pointer.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 360 "pointer.y" /* yacc.c:1646  */
    {(yyval.node)= get_new_node(yylval.str,0,NULL,ID);(yyval.node)->core_type = ID;push_value((yyval.node));(yyval.node)->PTR.st_ptr = lookup_ST(&symbolTable,yylval.str,scope);}
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 362 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0, NULL,ID);(yyval.node)->core_type = ID;push_value((yyval.node));(yyval.node)->PTR.st_ptr = lookup_ST(&symbolTable,yylval.str,scope);}
#line 1773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 363 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) =get_new_node(yylval.str,0,NULL,STR);(yyval.node)->core_type = VAL;push_value((yyval.node));(yyval.node)->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 364 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0,NULL,DEC);(yyval.node)->core_type = VAL;push_value((yyval.node));(yyval.node)->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
#line 1785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 365 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0,NULL,FLT);(yyval.node)->core_type = VAL;push_value((yyval.node));(yyval.node)->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 366 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0,NULL,CHAR);(yyval.node)->core_type = VAL;push_value((yyval.node));(yyval.node)->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 368 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0, NULL,NUM);(yyval.node)->core_type = OP;push_value((yyval.node));}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 369 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0, NULL, NUM);(yyval.node)->core_type = OP;push_value((yyval.node));}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 370 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0, NULL,REL);(yyval.node)->core_type = OP;push_value((yyval.node));}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 372 "pointer.y" /* yacc.c:1646  */
    {(yyval.node) = get_new_node(yylval.str,0, NULL,NUM);(yyval.node)->core_type = OP;push_value((yyval.node));}
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 374 "pointer.y" /* yacc.c:1646  */
    {
  
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*3);
  NODE** assign_kids = (NODE**)malloc(sizeof(NODE*)*2);
  assign_kids[0] = (yyvsp[-3].node); assign_kids[1] = (yyvsp[-1].node);
  kids[0]= get_new_node("LET",0,NULL,KW); kids[1]=get_new_node("=",2,assign_kids,KW); kids[2] = get_new_node(";",0,NULL,KW);
  (yyval.node) = get_new_node("VARDEC",3,kids,KW);
  
  if ((yyvsp[-1].node)->core_type == ID){
        (yyvsp[-3].node)->type = (yyvsp[-1].node)->type;
        //write changes to ST
        struct id * record = lookup_ST(&symbolTable,(yyvsp[-3].node)->value.value.string,scope);
        if (record != NULL){
               if ((yyvsp[-3].node)->type == DEC){
                    strcpy(record->type, "DECIMAL");
                    record->value.discriminator = 0;
                }
                if ((yyvsp[-3].node)->type == FLT){
                    strcpy(record->type, "FLOAT");
                    record-> value.discriminator = 1;
                }
                if ((yyvsp[-3].node)->type == CHAR){
                  strcpy(record->type, "CHARACTER");
                  record->value.discriminator = 2;
                }
                if ((yyvsp[-3].node)->type == STR){
                  strcpy(record->type, "STRING");
                  record->value.discriminator = 3;
                }
               (yyvsp[-3].node)->PTR.st_ptr = record;
        }
  }else{
    
  int literal_assign = 0;
  struct literal * assigned = NULL;
  struct id* record = lookup_ST(&symbolTable,(yyvsp[-3].node)->value.value.string,scope);
  (yyvsp[-3].node)->PTR.st_ptr = record;
  if (record != NULL){
    //printf("Record found\n");fflush(stdout);
      for (int k = 0; k < symbolTable.literal_count;k++){
        if (symbolTable.literalTable[k].discriminator == 0){
          if(symbolTable.literalTable[k].value.integer == atoi((yyvsp[-1].node)->value.value.string)){
            record->value.discriminator = 0;
            literal_assign = 1;
            assigned = symbolTable.literalTable +k;
            (yyvsp[-3].node)->type = DEC;
            strcpy(record->type, symbolTable.literalTable[k].type);
            record->value.value.integer= atoi((yyvsp[-1].node)->value.value.string);
            break;
          }
        }else{
          if (symbolTable.literalTable[k].discriminator == 1){
            
            if(symbolTable.literalTable[k].value.floating == atof((yyvsp[-1].node)->value.value.string)){
              record->value.discriminator = 1;
              literal_assign = 1;
              assigned = symbolTable.literalTable+k;
              (yyvsp[-3].node)->type = FLT;
              strcpy(record->type, symbolTable.literalTable[k].type);
              record->value.value.floating= atof((yyvsp[-1].node)->value.value.string);
              break;
            }
          }else{
            if (symbolTable.literalTable[k].discriminator == 2){
              if(strcmp(symbolTable.literalTable[k].value.character,(yyvsp[-1].node)->value.value.string)==0){
                record->value.discriminator = 2;
                literal_assign= 1;
                assigned = symbolTable.literalTable +k;
                (yyvsp[-3].node)->type = CHAR;
                strcpy(record->type, symbolTable.literalTable[k].type);
                strcpy(record->value.value.character,(yyvsp[-1].node)->value.value.string);
                break;
              }
            }else{
              if (symbolTable.literalTable[k].discriminator == 3){
                if(strcmp(symbolTable.literalTable[k].value.string, (yyvsp[-1].node)->value.value.string)==0){
                  record->value.discriminator = 3;
                  literal_assign = 1;
                  assigned = symbolTable.literalTable+k;
                  (yyvsp[-3].node)->type = STR;
                  strcpy(record->type, symbolTable.literalTable[k].type);
                  record->value.value.string = (char*)malloc(sizeof(char)*strlen((yyvsp[-1].node)->value.value.string));
                  strcpy(record->value.value.string,(yyvsp[-1].node)->value.value.string);
                  break;
                }
              }
            }
          }
        }
      
    }
    if (literal_assign ==1){
        //printf("Literal assigned with value\n");fflush(stdout);
        (yyvsp[-1].node)->PTR.lt_ptr = assigned;
      }
  }else{
    printf("RET NULL\n"); fflush(stdout);
  }
  }
  codegen_assign(scope,st,&top,&head_quad);
}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 481 "pointer.y" /* yacc.c:1646  */
    {lab1(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 481 "pointer.y" /* yacc.c:1646  */
    {
    NODE** kids = (NODE**)malloc(sizeof(NODE*)*5);
    kids[0]= (yyvsp[-5].node); kids[1]=get_new_node("{",0,NULL,KW);kids[2] = (yyvsp[-2].node); kids[3]=get_new_node("}",0,NULL,KW);kids[4] = (yyvsp[0].node);
    (yyval.node) = get_new_node("IF",5,kids,KW);
    if ((yyvsp[-5].node)->type != BOOL){
        error_count ++;
        printf("ERROR - Incorrect IF - CONDITION does not evaluate to Boolean Line no: %d\n",yylineno);
    }
}
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 491 "pointer.y" /* yacc.c:1646  */
    {lab2_else(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);}
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 491 "pointer.y" /* yacc.c:1646  */
    {
    lab3(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);
    NODE** kids = (NODE**)malloc(sizeof(NODE*)*3);
    kids[0]= get_new_node("{",0,NULL,KW); kids[1]=(yyvsp[-1].node); kids[2] =get_new_node("}",0,NULL,KW);
    (yyval.node) = get_new_node("ELSE",3,kids,KW);
}
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 497 "pointer.y" /* yacc.c:1646  */
    {lab2_noelse(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);(yyval.node) = get_new_node("LAMBDA",0,NULL,KW);}
#line 1970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 499 "pointer.y" /* yacc.c:1646  */
    {while_lab1(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);}
#line 1976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 499 "pointer.y" /* yacc.c:1646  */
    {while_lab2(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);}
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 499 "pointer.y" /* yacc.c:1646  */
    {
   while_lab3(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);
   NODE** kids = (NODE**)malloc(sizeof(NODE*)*4);
    kids[0]= (yyvsp[-4].node); kids[1]=get_new_node("{",0,NULL,KW);kids[2] = (yyvsp[-1].node); kids[3]=get_new_node("}",0,NULL,KW);//kids[4] = $5;
    (yyval.node) = get_new_node("WHILE",4,kids,KW);
    if ((yyvsp[-4].node)->type != BOOL){
        error_count ++;
        printf("ERROR - Incorrect WHILE - CONDITION does not evaluate to Boolean Line no: %d\n",yylineno);
    }
}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 510 "pointer.y" /* yacc.c:1646  */
    {for_lab1(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);}
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 510 "pointer.y" /* yacc.c:1646  */
    {for_lab2(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 510 "pointer.y" /* yacc.c:1646  */
    {
   for_lab3(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);
   NODE** kids = (NODE**)malloc(sizeof(NODE*)*6);
   NODE** range_kids = (NODE**)malloc(sizeof(NODE*)*2);
    range_kids[0] = (yyvsp[-7].node); range_kids[1] = (yyvsp[-4].node);
    kids[0]= (yyvsp[-9].node); kids[1]=get_new_node("IN",0,NULL,KW);kids[2] = get_new_node("RANGE",2,range_kids,KW); 
    kids[3]=get_new_node("{",0,NULL,KW);kids[4] = (yyvsp[-1].node);kids[5] = get_new_node("}",0,NULL,KW);
    (yyval.node) = get_new_node("FOR",6,kids,KW);
    //write changes to ST
    (yyvsp[-9].node)->type = DEC;
    
    if ((yyvsp[-7].node)->type !=DEC || (yyvsp[-4].node)->type!=DEC){
      printf("ERROR - Loop range must have DECIMALS given types %s and %s\n",CUSTYPES[(yyvsp[-7].node)->type],CUSTYPES[(yyvsp[-4].node)->type]);
      error_count++;
    }
    struct id* record = lookup_ST(&symbolTable,(yyvsp[-9].node)->value.value.string,scope);
    if (record != NULL){
              strcpy(record->type,"DECIMAL");
              record->value.discriminator = 0;
    }
}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2039 "y.tab.c" /* yacc.c:1646  */
      default: break;
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 532 "pointer.y" /* yacc.c:1906  */


int main(){
        head_quad = NULL;
        top = 0;
        temp_count = 0;
        label_count = 0;
        queue.queue = NULL;
        queue.queue_front = -1;
        queue.queue_rear = -1;
        symbolTable.literal_count = 0;
        symbolTable.literalTable = (struct literal*)malloc(sizeof(struct literal)*100);
        installLiteral(&symbolTable,"1","DECIMAL");
        yyparse();
        if (error_count > 0){
          printf("Compilation Errors - Will not generate ICG\n");
        }else{
          //display_quad(head_quad);
          //printf("After Removal of temp assigns\n\n");
          remove_temp_assigns(head_quad);
          //display_quad(head_quad);
          CSE(head_quad);
          //printf("\n After CSE\n\n");
          //display_quad(head_quad);
          int prop = 1;
          int fold = 1;
          while (prop == 1 && fold == 1){
            prop = const_prop(head_quad);
            fold = const_fold(head_quad,&symbolTable);
          }
          //printf("\nAfter Propagating and Folding\n");
          //display_quad(head_quad);
          deadcode_removal(head_quad);
          //printf("\nAfter dead code removal\n");
          //display_quad(head_quad);
          remove_dead_variables(&head_quad);
          //printf("After Removal dead variables\n\n");
          //printf("@\n");
          display_quad(head_quad);
          //dispLit(&symbolTable);
          //dispST(&symbolTable,max_depth);
         }
        return 0;
}

void yyerror(char *s){
	printf("ERROR: \"%s\" on line: %d\n",s, yylineno);
  yyparse();
}

char* get_new_temp(int count){
  char* new_temp;
  char buff[3];
  if (count < 9){
    new_temp = (char*)malloc(sizeof(char)*2);
  }else{
    new_temp = (char*)malloc(sizeof(char)*3);
  }
  snprintf(buff,3,"%d",count);
  strcpy(new_temp,"t");
  strcat(new_temp, buff);
  return new_temp;
}

char* get_new_label(int count){
  char* new_label;
  char buff[3];
  if (count < 9){
    new_label = (char*)malloc(sizeof(char)*2);
  }else{
    new_label = (char*)malloc(sizeof(char)*3);
  }
  snprintf(buff,3,"%d",count);
  strcpy(new_label,"L");
  strcat(new_label, buff);
  return new_label;
}

void push_value(NODE* value) {
  st[++top] = value;
}




