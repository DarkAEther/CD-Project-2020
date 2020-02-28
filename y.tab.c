/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 3 "yacc.y"
#include <stdio.h>
#include <stdlib.h>
#include "header.h" 
void yyerror();
int line_num=1;    

#line 28 "y.tab.c"

#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_AS 257
#define KW_BREAK 258
#define KW_CONST 259
#define KW_CONTINUE 260
#define KW_CRATE 261
#define KW_ELSE 262
#define KW_ENUM 263
#define KW_EXTERN 264
#define KW_FALSE 265
#define KW_FN 266
#define KW_FOR 267
#define KW_IF 268
#define KW_IMPL 269
#define KW_IN 270
#define KW_LET 271
#define KW_MATCH 272
#define KW_MOD 273
#define KW_MOVE 274
#define KW_MUT 275
#define KW_PUB 276
#define KW_REF 277
#define KW_RETURN 278
#define KW_SELFVALUE 279
#define KW_SELFTYPE 280
#define KW_STATIC 281
#define KW_STRUCT 282
#define KW_SUPER 283
#define KW_TRAIT 284
#define KW_TRUE 285
#define KW_TYPE 286
#define KW_UNSAFE 287
#define KW_USE 288
#define KW_WHERE 289
#define KW_WHILE 290
#define KW_LOOP 291
#define CHARACTER 292
#define STRING 293
#define RAW_STRING 294
#define BYTE 295
#define BYTE_STRING 296
#define RAW_BYTE_STRING 297
#define DECIMAL 298
#define HEX_INT 299
#define OCTAL_INT 300
#define BIN_INT 301
#define FLOAT 302
#define ARITH 303
#define BITWISE 304
#define ASSIGN_OPS 305
#define ASSIGN 306
#define RELATIONAL 307
#define IDENTIFIER 308
#define STMT_TERMINATOR 309
#define RANGE 310
#define ERROR 311
#define OPEN_BLOCK 312
#define CLOSE_BLOCK 313
#define OPEN_PARANTHESIS 314
#define CLOSE_PARANTHESIS 315
#define COMMA 316
#define KW_MAIN 317
#define KW_PRINTLN 318
#define EOF 319
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    2,    2,    2,    2,    2,    3,    3,
    3,    3,    7,    9,    9,    9,   11,   11,   11,   11,
   12,   12,   12,   10,    8,   13,   13,   13,    4,   14,
   14,    5,    6,
};
static const YYINT yylen[] = {                            2,
    2,    0,    7,    2,    2,    2,    2,    0,    1,    1,
    1,    1,    4,    3,    3,    1,    1,    1,    1,    1,
    1,    1,    1,    5,    5,    1,    3,    0,    6,    4,
    0,    5,    9,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    1,    0,    0,    0,    0,    0,
    0,    0,   18,   19,   20,    0,    0,    0,    0,    0,
    0,    0,    0,    9,   10,   11,   12,    0,    0,   17,
    0,    0,    0,    0,    0,    0,    3,    4,    5,    6,
    7,   21,   22,   23,    0,    0,    0,    0,    0,    0,
   15,    0,    0,   14,    0,    0,    0,    0,   13,    0,
    0,    0,    0,   24,   32,   27,   25,    0,    0,   29,
    0,    0,    0,    0,   33,   30,
};
static const YYINT yydgoto[] = {                          2,
    3,   19,   20,   21,   22,   23,   24,   25,   26,   27,
   28,   45,   53,   70,
};
static const YYINT yysindex[] = {                      -261,
 -311,    0, -309, -302,    0, -299, -284, -197, -285, -289,
 -277, -289,    0,    0,    0, -272, -289, -279, -274, -197,
 -197, -197, -197,    0,    0,    0,    0, -283, -234,    0,
 -271, -256, -266, -289, -258, -227,    0,    0,    0,    0,
    0,    0,    0,    0, -289, -230, -197, -289, -197, -240,
    0, -244, -242,    0, -235, -237, -232, -231,    0, -276,
 -228, -219, -179,    0,    0,    0,    0, -225, -224,    0,
 -197, -197, -229, -223,    0,    0,
};
static const YYINT yyrindex[] = {                        91,
    0,    0,    0,    0,    0,    0,    0, -221,    0,    0,
    0,    0,    0,    0,    0, -260,    0,    0,    0, -221,
 -221, -221, -221,    0,    0,    0,    0, -253,    0,    0,
    0,    0,    0,    0,    0, -220,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -221,    0, -221,    0,
    0, -218,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -204,    0,    0,    0,    0,    0,    0,    0,
 -221, -221,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,  -20,    0,    0,    0,    0,    0,    0,   68,    0,
   39,    0,    0,    0,
};
#define YYTABLESIZE 121
static const YYINT yytable[] = {                         38,
   39,   40,   41,   13,    1,    4,   17,   17,   14,    5,
   17,    6,   15,   16,   16,    7,   13,   16,   30,   42,
   43,   14,   29,   44,   17,   15,   56,    8,   58,   17,
   32,   30,   17,   34,   36,   46,   16,   17,   37,   16,
   47,   17,   17,   17,   16,   49,   17,   17,   16,   48,
   73,   74,   17,   17,   16,   16,   51,   17,   16,   16,
   16,   16,   31,   31,   16,   52,   31,   55,   59,    9,
   10,   60,   61,   11,   62,   63,   64,   31,   68,   33,
   67,   65,   69,   75,   35,   31,   71,   72,   31,   76,
    2,    8,   12,   31,   28,   13,   26,   31,   66,    0,
   14,   50,    0,   31,   15,    0,    0,    0,   31,   31,
   16,    0,   54,   31,    0,   57,   17,    0,    0,    0,
   18,
};
static const YYINT yycheck[] = {                         20,
   21,   22,   23,  293,  266,  317,  267,  268,  298,  319,
  271,  314,  302,  267,  268,  315,  293,  271,  308,  303,
  304,  298,  308,  307,  314,  302,   47,  312,   49,  290,
  308,  308,  293,  306,  314,  270,  290,  298,  313,  293,
  312,  302,  303,  304,  298,  312,  307,  308,  302,  306,
   71,   72,  313,  314,  308,  309,  315,  318,  312,  313,
  314,  315,  267,  268,  318,  293,  271,  298,  309,  267,
  268,  316,  315,  271,  310,  313,  309,   10,  298,   12,
  309,  313,  262,  313,   17,  290,  312,  312,  293,  313,
    0,  313,  290,  298,  315,  293,  315,  302,   60,   -1,
  298,   34,   -1,  308,  302,   -1,   -1,   -1,  313,  314,
  308,   -1,   45,  318,   -1,   48,  314,   -1,   -1,   -1,
  318,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 319
#define YYUNDFTOKEN 336
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_AS","KW_BREAK","KW_CONST",
"KW_CONTINUE","KW_CRATE","KW_ELSE","KW_ENUM","KW_EXTERN","KW_FALSE","KW_FN",
"KW_FOR","KW_IF","KW_IMPL","KW_IN","KW_LET","KW_MATCH","KW_MOD","KW_MOVE",
"KW_MUT","KW_PUB","KW_REF","KW_RETURN","KW_SELFVALUE","KW_SELFTYPE","KW_STATIC",
"KW_STRUCT","KW_SUPER","KW_TRAIT","KW_TRUE","KW_TYPE","KW_UNSAFE","KW_USE",
"KW_WHERE","KW_WHILE","KW_LOOP","CHARACTER","STRING","RAW_STRING","BYTE",
"BYTE_STRING","RAW_BYTE_STRING","DECIMAL","HEX_INT","OCTAL_INT","BIN_INT",
"FLOAT","ARITH","BITWISE","ASSIGN_OPS","ASSIGN","RELATIONAL","IDENTIFIER",
"STMT_TERMINATOR","RANGE","ERROR","OPEN_BLOCK","CLOSE_BLOCK","OPEN_PARANTHESIS",
"CLOSE_PARANTHESIS","COMMA","KW_MAIN","KW_PRINTLN","EOF",0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : start",
"start : Main EOF",
"start :",
"Main : KW_FN KW_MAIN OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BLOCK Blk CLOSE_BLOCK",
"Blk : Code Blk",
"Blk : If Blk",
"Blk : While Blk",
"Blk : For Blk",
"Blk :",
"Code : Eval",
"Code : Out",
"Code : Exp",
"Code : Var_dec",
"Eval : IDENTIFIER ASSIGN Exp STMT_TERMINATOR",
"Exp : Val op Exp",
"Exp : OPEN_PARANTHESIS Exp CLOSE_PARANTHESIS",
"Exp : Val",
"Val : IDENTIFIER",
"Val : STRING",
"Val : DECIMAL",
"Val : FLOAT",
"op : ARITH",
"op : BITWISE",
"op : RELATIONAL",
"Var_dec : KW_LET IDENTIFIER ASSIGN Exp STMT_TERMINATOR",
"Out : KW_PRINTLN OPEN_PARANTHESIS Body CLOSE_PARANTHESIS STMT_TERMINATOR",
"Body : STRING",
"Body : STRING COMMA Val",
"Body :",
"If : KW_IF Exp OPEN_BLOCK Blk CLOSE_BLOCK Else",
"Else : KW_ELSE OPEN_BLOCK Blk CLOSE_BLOCK",
"Else :",
"While : KW_WHILE Exp OPEN_BLOCK Blk CLOSE_BLOCK",
"For : KW_FOR IDENTIFIER KW_IN DECIMAL RANGE DECIMAL OPEN_BLOCK Blk CLOSE_BLOCK",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 119 "yacc.y"

void main(){
        yyparse();
}
#line 318 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 76 "yacc.y"
	{printf("\n-------------ACCEPTED----------------\n");}
break;
case 3:
#line 79 "yacc.y"
	{printf("%s", yyval);}
break;
#line 528 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
