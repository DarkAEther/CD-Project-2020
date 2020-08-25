/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 69 "pointer.y"

  char *str;
  struct node* node;

#line 192 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
