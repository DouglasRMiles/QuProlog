/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 2000-Wednesday 16 May  13:50:25 AEST 2018 

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "qa.y" /* yacc.c:339  */

/*
 * Copyright (C) 2000-Wednesday 16 May  13:50:25 AEST 2018 
 * Department of Computer Science and Electrical Engineering, 
 * The University of Queensland
 */


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "asm_objects.h"
#include "asm_string_table.cc"
#include "code.h"
#include "code_block.h"
#include "errors.h"
#include "indexing.h"

const char *Program = "qa";

extern "C" int yylex();

int yyerror(const char *);

ASMStringTable *asm_string_table = NULL;

CodeBlock *query_code_block = NULL;
vector<CodeBlock *> *predicate_code_blocks = NULL;

CodeBlock *code_block = NULL;

LabelTable *labels = NULL;


#line 103 "qa.cc" /* yacc.c:339  */

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
    put_x_variable = 258,
    put_y_variable = 259,
    put_x_value = 260,
    put_y_value = 261,
    put_constant = 262,
    put_integer = 263,
    put_double = 264,
    put_string = 265,
    put_list = 266,
    put_structure = 267,
    put_x_object_variable = 268,
    put_y_object_variable = 269,
    put_x_object_value = 270,
    put_y_object_value = 271,
    put_quantifier = 272,
    check_binder = 273,
    put_substitution = 274,
    put_x_term_substitution = 275,
    put_y_term_substitution = 276,
    put_initial_empty_substitution = 277,
    get_x_variable = 278,
    get_y_variable = 279,
    get_x_value = 280,
    get_y_value = 281,
    get_constant = 282,
    get_integer = 283,
    get_double = 284,
    get_string = 285,
    get_list = 286,
    get_structure = 287,
    get_structure_frame = 288,
    get_x_object_variable = 289,
    get_y_object_variable = 290,
    get_x_object_value = 291,
    get_y_object_value = 292,
    unify_x_variable = 293,
    unify_y_variable = 294,
    unify_x_value = 295,
    unify_y_value = 296,
    unify_void = 297,
    unify_constant = 298,
    unify_integer = 299,
    unify_double = 300,
    unify_string = 301,
    unify_x_ref = 302,
    unify_y_ref = 303,
    set_x_variable = 304,
    set_y_variable = 305,
    set_x_value = 306,
    set_y_value = 307,
    set_x_object_variable = 308,
    set_y_object_variable = 309,
    set_x_object_value = 310,
    set_y_object_value = 311,
    set_constant = 312,
    set_integer = 313,
    set_double = 314,
    set_string = 315,
    set_void = 316,
    set_object_void = 317,
    wam_allocate = 318,
    wam_deallocate = 319,
    call_predicate = 320,
    call_address = 321,
    call_escape = 322,
    execute_predicate = 323,
    execute_address = 324,
    execute_escape = 325,
    noop = 326,
    jump = 327,
    proceed = 328,
    wam_fail = 329,
    halt = 330,
    wam_exit = 331,
    try_me_else = 332,
    retry_me_else = 333,
    trust_me_else_fail = 334,
    wam_try = 335,
    retry = 336,
    trust = 337,
    neck_cut = 338,
    get_x_level = 339,
    get_y_level = 340,
    cut = 341,
    switch_on_term = 342,
    switch_on_constant = 343,
    switch_on_structure = 344,
    switch_on_quantifier = 345,
    pseudo_instr0 = 346,
    pseudo_instr1 = 347,
    pseudo_instr2 = 348,
    pseudo_instr3 = 349,
    pseudo_instr4 = 350,
    pseudo_instr5 = 351,
    INTEGER_TOKEN = 352,
    DOUBLE_TOKEN = 353,
    STRING_TOKEN = 354,
    ATOM_TOKEN = 355,
    LABEL_TOKEN = 356,
    END_TOKEN = 357
  };
#endif
/* Tokens.  */
#define put_x_variable 258
#define put_y_variable 259
#define put_x_value 260
#define put_y_value 261
#define put_constant 262
#define put_integer 263
#define put_double 264
#define put_string 265
#define put_list 266
#define put_structure 267
#define put_x_object_variable 268
#define put_y_object_variable 269
#define put_x_object_value 270
#define put_y_object_value 271
#define put_quantifier 272
#define check_binder 273
#define put_substitution 274
#define put_x_term_substitution 275
#define put_y_term_substitution 276
#define put_initial_empty_substitution 277
#define get_x_variable 278
#define get_y_variable 279
#define get_x_value 280
#define get_y_value 281
#define get_constant 282
#define get_integer 283
#define get_double 284
#define get_string 285
#define get_list 286
#define get_structure 287
#define get_structure_frame 288
#define get_x_object_variable 289
#define get_y_object_variable 290
#define get_x_object_value 291
#define get_y_object_value 292
#define unify_x_variable 293
#define unify_y_variable 294
#define unify_x_value 295
#define unify_y_value 296
#define unify_void 297
#define unify_constant 298
#define unify_integer 299
#define unify_double 300
#define unify_string 301
#define unify_x_ref 302
#define unify_y_ref 303
#define set_x_variable 304
#define set_y_variable 305
#define set_x_value 306
#define set_y_value 307
#define set_x_object_variable 308
#define set_y_object_variable 309
#define set_x_object_value 310
#define set_y_object_value 311
#define set_constant 312
#define set_integer 313
#define set_double 314
#define set_string 315
#define set_void 316
#define set_object_void 317
#define wam_allocate 318
#define wam_deallocate 319
#define call_predicate 320
#define call_address 321
#define call_escape 322
#define execute_predicate 323
#define execute_address 324
#define execute_escape 325
#define noop 326
#define jump 327
#define proceed 328
#define wam_fail 329
#define halt 330
#define wam_exit 331
#define try_me_else 332
#define retry_me_else 333
#define trust_me_else_fail 334
#define wam_try 335
#define retry 336
#define trust 337
#define neck_cut 338
#define get_x_level 339
#define get_y_level 340
#define cut 341
#define switch_on_term 342
#define switch_on_constant 343
#define switch_on_structure 344
#define switch_on_quantifier 345
#define pseudo_instr0 346
#define pseudo_instr1 347
#define pseudo_instr2 348
#define pseudo_instr3 349
#define pseudo_instr4 350
#define pseudo_instr5 351
#define INTEGER_TOKEN 352
#define DOUBLE_TOKEN 353
#define STRING_TOKEN 354
#define ATOM_TOKEN 355
#define LABEL_TOKEN 356
#define END_TOKEN 357

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 37 "qa.y" /* yacc.c:355  */

  long int_value;
  double double_value;

  string *label_name;
  string *atom_name;
  string *string_value;

  ASMLoc loc;

  ASMInt<Code::InstructionSizedType> *instruction;
  ASMInt<Code::ConstantSizedType> *constant;
  ASMDouble<double> *double_num;
  ASMInt<long> *int_num;
  ASMInt<Code::RegisterSizedType> *reg;
  ASMInt<Code::NumberSizedType> *number;
  ASMInt<Code::AddressSizedType> *address;
  ASMInt<Code::OffsetSizedType> *offset;
  ASMInt<Code::PredSizedType> *pred;
  ASMInt<Code::TableSizeSizedType> *table_size;

  vector<ConstantLabel *> *cl_list;
  ConstantLabel *cl;
  
  vector<AtomArityLabel *> *aal_list;
  AtomArityLabel *aal;

#line 372 "qa.cc" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 387 "qa.cc" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   592

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  572

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     105,   106,     2,   110,   107,   111,     2,   103,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   104,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   108,     2,   109,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   204,   204,   207,   208,   211,   214,   245,   271,   272,
     275,   276,   279,   285,   292,   299,   306,   313,   320,   326,
     332,   344,   350,   357,   364,   371,   378,   385,   391,   397,
     404,   411,   418,   424,   431,   438,   445,   452,   459,   466,
     473,   485,   491,   499,   506,   513,   520,   527,   534,   540,
     546,   552,   558,   564,   570,   576,   587,   593,   599,   605,
     611,   617,   623,   629,   635,   641,   647,   653,   659,   665,
     671,   682,   688,   694,   700,   705,   713,   720,   727,   734,
     740,   746,   751,   757,   762,   767,   772,   777,   789,   799,
     804,   816,   826,   836,   841,   847,   853,   859,   883,   911,
     939,   967,   973,   980,   988,   997,  1007,  1021,  1024,  1030,
    1038,  1046,  1054,  1057,  1063,  1071,  1078,  1094,  1097,  1103,
    1111,  1119,  1133,  1134,  1144,  1151,  1156,  1161,  1168,  1175,
    1180,  1185,  1192,  1197,  1202,  1209,  1216,  1223,  1231
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "put_x_variable", "put_y_variable",
  "put_x_value", "put_y_value", "put_constant", "put_integer",
  "put_double", "put_string", "put_list", "put_structure",
  "put_x_object_variable", "put_y_object_variable", "put_x_object_value",
  "put_y_object_value", "put_quantifier", "check_binder",
  "put_substitution", "put_x_term_substitution", "put_y_term_substitution",
  "put_initial_empty_substitution", "get_x_variable", "get_y_variable",
  "get_x_value", "get_y_value", "get_constant", "get_integer",
  "get_double", "get_string", "get_list", "get_structure",
  "get_structure_frame", "get_x_object_variable", "get_y_object_variable",
  "get_x_object_value", "get_y_object_value", "unify_x_variable",
  "unify_y_variable", "unify_x_value", "unify_y_value", "unify_void",
  "unify_constant", "unify_integer", "unify_double", "unify_string",
  "unify_x_ref", "unify_y_ref", "set_x_variable", "set_y_variable",
  "set_x_value", "set_y_value", "set_x_object_variable",
  "set_y_object_variable", "set_x_object_value", "set_y_object_value",
  "set_constant", "set_integer", "set_double", "set_string", "set_void",
  "set_object_void", "wam_allocate", "wam_deallocate", "call_predicate",
  "call_address", "call_escape", "execute_predicate", "execute_address",
  "execute_escape", "noop", "jump", "proceed", "wam_fail", "halt",
  "wam_exit", "try_me_else", "retry_me_else", "trust_me_else_fail",
  "wam_try", "retry", "trust", "neck_cut", "get_x_level", "get_y_level",
  "cut", "switch_on_term", "switch_on_constant", "switch_on_structure",
  "switch_on_quantifier", "pseudo_instr0", "pseudo_instr1",
  "pseudo_instr2", "pseudo_instr3", "pseudo_instr4", "pseudo_instr5",
  "INTEGER_TOKEN", "DOUBLE_TOKEN", "STRING_TOKEN", "ATOM_TOKEN",
  "LABEL_TOKEN", "END_TOKEN", "'/'", "':'", "'('", "')'", "','", "'['",
  "']'", "'+'", "'-'", "$accept", "assembler_file", "predicate_list",
  "predicate", "predicate_start", "predicate_end", "source_line_list",
  "source_line", "label_instance", "instr", "constant_labels",
  "constant_label_list", "constant_label", "atom_arity_labels",
  "atom_arity_label_list", "atom_arity_label", "quantifier_labels",
  "quantifier_label_list", "quantifier_label", "switch_label", "constant",
  "number", "int_num", "double_num", "reg", "address", "atom",
  "table_size", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,    47,    58,    40,    41,    44,    91,    93,
      43,    45
};
# endif

#define YYPACT_NINF -421

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-421)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -421,     3,   -92,  -421,  -421,  -421,  -421,   -88,   490,   -69,
     -67,   -45,   -44,   -42,   -41,   -38,   -37,   -36,   -26,   -20,
     -19,   -12,   -11,   -10,    -5,    -1,     0,     1,     2,     6,
       8,     9,    10,    11,    12,    14,    16,    17,    18,    19,
      20,    21,    22,    23,    31,    32,    34,    35,    36,    37,
      38,    39,    40,    41,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,  -421,    61,    62,    63,    64,    65,    66,  -421,    67,
    -421,  -421,  -421,  -421,    68,    69,  -421,    70,    71,    72,
    -421,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      86,    87,    89,    90,    93,    96,  -421,  -421,  -421,  -421,
    -421,    94,   110,   110,   110,   110,   -13,   -55,   -28,   109,
     110,   -69,   110,   110,   110,   110,   110,   110,   -69,   110,
     110,   110,   110,   110,   110,   110,   -13,   -55,   -28,   113,
     110,   -13,   -69,   110,   110,   110,   110,   110,   110,   110,
     110,   -69,   -13,   -55,   -28,   122,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   -13,   -55,   -28,   123,
     -69,   -69,   -69,   -92,   131,   131,   -92,   131,   131,   131,
     -69,   128,   -69,   129,   130,   110,   110,   110,   110,   110,
     110,   110,   -69,   -69,   -69,   -69,   -69,   -69,  -421,   -92,
    -421,  -421,   125,   126,   127,   132,  -421,  -421,   138,   139,
     133,  -421,   140,   141,   134,  -421,   144,   145,   137,   142,
     146,   143,   147,   148,   149,   150,   152,   153,   154,   155,
     156,   158,   159,   160,   161,   162,   163,   164,   165,   172,
     174,   175,   176,   177,   178,   179,   180,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,  -421,   213,   214,   215,   217,   218,
     219,   220,   222,   224,   223,   226,   227,   228,   229,   230,
     231,   232,   233,   235,   236,   237,   238,   239,   240,   157,
     110,   110,   110,   110,  -421,  -421,   110,  -421,  -421,   110,
    -421,  -421,   110,   110,  -421,   110,   110,   110,   110,   110,
    -421,  -421,   110,   110,   110,  -421,   110,   110,   110,   110,
     110,   110,   110,   110,  -421,   -69,   110,   110,   110,   110,
     110,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,   -69,   -69,   -69,
     -69,  -421,  -421,  -421,   225,  -421,   241,  -421,  -421,  -421,
    -421,  -421,   -95,   151,   151,   151,  -421,   110,   110,   110,
     110,   110,   -69,   242,   243,   244,   245,   246,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   268,   269,   270,   271,   273,   274,
     275,   276,   277,   278,   280,   281,   282,   283,   284,  -421,
    -421,   285,  -421,   289,   290,   291,   293,   294,   295,   296,
     297,   299,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -421,  -421,  -421,  -421,   110,  -421,  -421,  -421,
    -421,  -421,   -69,  -421,  -421,  -421,  -421,  -421,   -95,   173,
     292,   298,  -421,   110,   110,   110,   110,   287,   301,   305,
     306,   312,   314,   315,   310,   311,   313,   316,  -421,  -421,
    -421,   -95,   317,   318,   320,  -421,   110,   110,   110,   319,
     -95,   -95,   -95,   321,   322,   323,   -95,   324,   325,   327,
    -421,   110,   110,   328,   -13,   136,   336,   308,   337,   329,
     333,   334,   -95,   335,  -421,   339,   338,   342,   340,  -421,
     343,   345,   344,  -421,   346,  -421,   110,   347,   -13,   -95,
    -421,   -69,   336,  -421,   -69,   337,  -421,   349,   -95,  -421,
    -421,   352,  -421,   353,  -421,  -421,   354,   -95,   -95,  -421,
    -421,  -421
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,   137,     4,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,     0,     0,     0,     0,     0,     0,    81,     0,
      83,    84,    85,    86,     0,     0,    89,     0,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     9,    10,    11,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       6,   135,     0,     0,     0,     0,   125,   124,     0,     0,
       0,   129,     0,     0,     0,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   126,   127,     0,   130,   131,     0,
     133,   134,     0,     0,    21,     0,     0,     0,     0,     0,
      27,    28,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    51,    56,    52,    53,    54,    55,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,     0,     0,     0,
       0,    79,    80,    82,     0,    88,     0,    91,    92,    94,
      95,    96,     0,     0,     0,     0,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   123,
     122,     0,   138,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,    14,    15,    16,    17,    18,    19,    20,
      22,    23,    24,    25,    26,    29,    30,    31,    33,    34,
      35,    36,    37,    38,    39,    40,     0,    43,    44,    45,
      46,    47,     0,    76,    77,    78,    87,    90,     0,     0,
       0,     0,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,    42,
      75,     0,     0,     0,     0,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,   112,   117,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,     0,     0,     0,   113,   114,
       0,     0,   118,   119,     0,   105,     0,     0,     0,     0,
      98,     0,     0,    99,     0,     0,   100,     0,     0,   110,
     111,     0,   115,     0,   120,   106,     0,     0,     0,    97,
     116,   121
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,  -421,
    -421,  -421,  -302,  -421,  -421,  -305,  -421,  -421,  -304,  -420,
    -112,   -62,  -114,   -97,  -113,   -76,  -111,  -359
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,   106,     8,   107,   108,   109,
     525,   533,   534,   527,   538,   539,   529,   542,   543,   431,
     535,   111,   214,   218,   202,   275,     7,   433
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     203,   204,   205,     3,   210,   429,   430,   220,     4,   222,
     223,   224,   225,   226,   227,     9,   229,   230,   231,   232,
     233,   234,   235,   237,   236,   434,   435,   240,   110,   241,
     243,   244,   245,   246,   247,   248,   249,   250,   112,   253,
     252,   238,   211,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   267,   266,   212,   213,   254,   490,   221,
     113,   114,   273,   115,   116,   277,   228,   117,   118,   119,
     215,   268,   286,   287,   288,   289,   290,   291,   292,   120,
     242,   509,   216,   217,   206,   121,   122,   207,   299,   251,
     517,   518,   519,   123,   124,   125,   523,   208,   209,   276,
     126,   278,   279,   280,   127,   128,   129,   130,   270,   271,
     272,   131,   547,   132,   133,   134,   135,   136,   281,   137,
     283,   138,   139,   140,   141,   142,   143,   144,   145,   560,
     293,   294,   295,   296,   297,   298,   146,   147,   566,   148,
     149,   150,   151,   152,   153,   154,   155,   570,   571,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   393,   394,   395,
     396,   194,   195,   397,   196,   197,   398,   198,   200,   399,
     400,   199,   401,   402,   403,   404,   405,   201,   219,   406,
     407,   408,   239,   409,   410,   411,   412,   413,   414,   415,
     416,   255,   269,   418,   419,   420,   421,   422,   274,   282,
     284,   285,   300,   301,   302,   304,   305,   307,   308,   303,
     306,   309,   310,   311,   312,   536,   559,   562,   432,   313,
     315,   564,   314,     0,   316,   317,   318,   319,   320,   321,
     392,   322,   323,   324,   325,     0,   326,   327,   328,   329,
     330,   331,   332,   417,   436,   437,   438,   439,   440,   333,
     334,   491,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   423,   424,   425,   426,   358,
     359,   360,   361,   362,   363,   364,   365,   366,     0,   367,
     368,   369,   370,   371,   372,   373,   427,   374,   375,   377,
     441,   376,   378,   379,   380,   381,     0,   382,   383,   384,
     385,   386,   428,   387,   388,   389,   390,   391,   442,   443,
     444,   445,   446,   488,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   462,
     494,   495,   496,   497,   463,   464,   465,     0,   466,   467,
     468,   469,   470,   471,     0,   472,   473,   474,   475,   476,
     477,   498,   478,   513,   514,   515,   479,   480,   481,   482,
     492,   483,   484,   485,   486,   487,   493,   499,   530,   531,
     489,   500,   502,   501,   503,   504,   505,   540,   506,     0,
     507,   510,   511,   508,   512,     0,   516,   520,     0,   521,
     522,   524,   526,   557,   528,   532,   537,   541,   544,   545,
       0,   546,   548,   549,   550,   551,     0,   552,   554,   553,
       0,   555,   556,     0,   558,   565,   567,   568,     0,     0,
     569,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   561,
       0,     0,   563,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,   104,   105
};

static const yytype_int16 yycheck[] =
{
     113,   114,   115,     0,   116,   100,   101,   120,   100,   122,
     123,   124,   125,   126,   127,   103,   129,   130,   131,   132,
     133,   134,   135,   137,   136,   384,   385,   140,    97,   141,
     143,   144,   145,   146,   147,   148,   149,   150,   105,   153,
     152,   138,    97,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   167,   166,   110,   111,   154,   478,   121,
     105,   105,   173,   105,   105,   176,   128,   105,   105,   105,
      98,   168,   185,   186,   187,   188,   189,   190,   191,   105,
     142,   501,   110,   111,    97,   105,   105,   100,   199,   151,
     510,   511,   512,   105,   105,   105,   516,   110,   111,   175,
     105,   177,   178,   179,   105,   105,   105,   105,   170,   171,
     172,   105,   532,   105,   105,   105,   105,   105,   180,   105,
     182,   105,   105,   105,   105,   105,   105,   105,   105,   549,
     192,   193,   194,   195,   196,   197,   105,   105,   558,   105,
     105,   105,   105,   105,   105,   105,   105,   567,   568,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   300,   301,   302,
     303,   105,   105,   306,   105,   105,   309,   104,   104,   312,
     313,   105,   315,   316,   317,   318,   319,    97,    99,   322,
     323,   324,    99,   326,   327,   328,   329,   330,   331,   332,
     333,    99,    99,   336,   337,   338,   339,   340,    97,   101,
     101,   101,   107,   107,   107,    97,    97,    97,    97,   107,
     107,   107,    98,    98,   107,   109,   548,   552,    97,   107,
     107,   555,   106,    -1,   107,   107,   107,   107,   106,   106,
     103,   107,   107,   107,   106,    -1,   107,   107,   107,   107,
     107,   107,   107,   335,   387,   388,   389,   390,   391,   107,
     106,   108,   107,   107,   107,   107,   107,   107,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   367,   368,   369,   370,   106,
     106,   106,   106,   106,   106,   106,   106,   106,    -1,   107,
     107,   107,   107,   106,   106,   106,   101,   107,   106,   106,
     392,   107,   106,   106,   106,   106,    -1,   107,   107,   107,
     107,   106,   101,   107,   107,   107,   107,   107,   106,   106,
     106,   106,   106,   466,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     483,   484,   485,   486,   106,   106,   106,    -1,   107,   106,
     106,   106,   106,   106,    -1,   107,   106,   106,   106,   106,
     106,   104,   107,   506,   507,   508,   107,   107,   107,   106,
     108,   107,   107,   107,   107,   106,   108,   106,   521,   522,
     472,   106,   100,   107,   100,   100,   106,   109,   107,    -1,
     107,   104,   104,   107,   104,    -1,   107,   106,    -1,   107,
     107,   107,   107,   546,   107,   107,   100,   100,   109,   106,
      -1,   107,   107,   104,   106,   103,    -1,   107,   103,   106,
      -1,   107,   106,    -1,   107,   106,   104,   104,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   551,
      -1,    -1,   554,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    -1,    -1,    -1,
      -1,   101,   102
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   113,   114,     0,   100,   115,   116,   138,   118,   103,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,   101,   102,   117,   119,   120,   121,
      97,   133,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   104,   105,
     104,    97,   136,   136,   136,   136,    97,   100,   110,   111,
     132,    97,   110,   111,   134,    98,   110,   111,   135,    99,
     136,   133,   136,   136,   136,   136,   136,   136,   133,   136,
     136,   136,   136,   136,   136,   136,   132,   134,   135,    99,
     136,   132,   133,   136,   136,   136,   136,   136,   136,   136,
     136,   133,   132,   134,   135,    99,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   132,   134,   135,    99,
     133,   133,   133,   138,    97,   137,   137,   138,   137,   137,
     137,   133,   101,   133,   101,   101,   136,   136,   136,   136,
     136,   136,   136,   133,   133,   133,   133,   133,   133,   138,
     107,   107,   107,   107,    97,    97,   107,    97,    97,   107,
      98,    98,   107,   107,   106,   107,   107,   107,   107,   107,
     106,   106,   107,   107,   107,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   106,   107,   107,   107,   107,   107,
     107,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   107,   107,
     107,   106,   106,   106,   107,   106,   107,   106,   106,   106,
     106,   106,   107,   107,   107,   107,   106,   107,   107,   107,
     107,   107,   103,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   133,   136,   136,
     136,   136,   136,   133,   133,   133,   133,   101,   101,   100,
     101,   131,    97,   139,   139,   139,   136,   136,   136,   136,
     136,   133,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   107,   106,   106,   106,
     106,   106,   107,   106,   106,   106,   106,   106,   107,   107,
     107,   107,   106,   107,   107,   107,   107,   106,   136,   133,
     131,   108,   108,   108,   136,   136,   136,   136,   104,   106,
     106,   107,   100,   100,   100,   106,   107,   107,   107,   131,
     104,   104,   104,   136,   136,   136,   107,   131,   131,   131,
     106,   107,   107,   131,   107,   122,   107,   125,   107,   128,
     136,   136,   107,   123,   124,   132,   109,   100,   126,   127,
     109,   100,   129,   130,   109,   106,   107,   131,   107,   104,
     106,   103,   107,   106,   103,   107,   106,   136,   107,   124,
     131,   133,   127,   133,   130,   106,   131,   104,   104,   106,
     131,   131
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   114,   114,   115,   116,   117,   118,   118,
     119,   119,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   122,   122,   123,
     123,   124,   125,   125,   126,   126,   127,   128,   128,   129,
     129,   130,   131,   131,   132,   132,   132,   132,   133,   134,
     134,   134,   135,   135,   135,   136,   137,   138,   139
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     4,     7,     0,     2,
       1,     1,     2,     6,     6,     6,     6,     6,     6,     6,
       6,     4,     6,     6,     6,     6,     6,     4,     4,     6,
       6,     6,     4,     6,     6,     6,     6,     6,     6,     6,
       6,     4,     8,     6,     6,     6,     6,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     1,     8,     6,     6,     6,     4,
       4,     1,     4,     1,     1,     1,     1,     6,     4,     1,
       6,     4,     4,     1,     4,     4,     4,    16,    13,    13,
      13,     4,     6,     8,    10,    12,    14,     0,     2,     1,
       3,     3,     0,     2,     1,     3,     5,     0,     2,     1,
       3,     5,     1,     1,     1,     1,     2,     2,     1,     1,
       2,     2,     1,     2,     2,     1,     1,     1,     1
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
        case 6:
#line 215 "qa.y" /* yacc.c:1646  */
    {
		  labels = new LabelTable;

		  // Is it the query code block?
		  if ((*asm_string_table)[(yyvsp[-3].constant)->Value()] == "$query" &&
		      (yyvsp[-1].number)->Value() == 0)
		    {
		      if (query_code_block != NULL)
			{
			  Fatal(__FUNCTION__, 
				"more than one query code block");
			}
		      query_code_block = new CodeBlock(QUERY_BLOCK,
						       (yyvsp[-3].constant)->Value(),
						       (yyvsp[-1].number)->Value());

		      code_block = query_code_block;
		    }
		  else
		    {
		      code_block = new CodeBlock(PREDICATE_BLOCK,
						 (yyvsp[-3].constant)->Value(),
						 (yyvsp[-1].number)->Value());
		    }

		  delete (yyvsp[-3].constant);
		  delete (yyvsp[-1].number);
		}
#line 1865 "qa.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 246 "qa.y" /* yacc.c:1646  */
    {
		  if ((yyvsp[-4].constant)->Value() != code_block->Atom() ||
		      (u_int)((yyvsp[-2].number)->Value()) != code_block->Arity())
		    {
		      Fatal(__FUNCTION__, 
			    "atom or arity mismatch in predicate");
		    }

		  delete (yyvsp[-4].constant);
		  delete (yyvsp[-2].number);

		  // Resolve all the fail label references
		  labels->ResolveFail(*code_block);

		  if (code_block->Type() == PREDICATE_BLOCK)
		    {
		      predicate_code_blocks->push_back(code_block);
		    }
		  
		  // Make it difficult to reuse the label table
		  delete labels;
		  labels = NULL;
		}
#line 1893 "qa.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 280 "qa.y" /* yacc.c:1646  */
    {
		  labels->Resolve(*(yyvsp[-1].label_name), *code_block);
		}
#line 1901 "qa.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 286 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1911 "qa.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 293 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1921 "qa.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 300 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1931 "qa.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 307 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1941 "qa.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 314 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1951 "qa.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 321 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].int_num)->Put(*code_block); delete (yyvsp[-3].int_num);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1961 "qa.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 327 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].double_num)->Put(*code_block); delete (yyvsp[-3].double_num);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1971 "qa.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 333 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		  string* buff = (yyvsp[-3].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[-3].string_value);
		}
#line 1986 "qa.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 345 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 1995 "qa.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 351 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2005 "qa.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 358 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2015 "qa.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 365 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2025 "qa.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 372 "qa.y" /* yacc.c:1646  */
    {
		   (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		   (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		   (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		 }
#line 2035 "qa.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 379 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2045 "qa.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 386 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2054 "qa.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 392 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2063 "qa.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 398 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2073 "qa.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 405 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2083 "qa.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 412 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2093 "qa.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 419 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2102 "qa.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 425 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2112 "qa.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 432 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2122 "qa.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 439 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2132 "qa.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 446 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2142 "qa.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 453 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2152 "qa.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 460 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].int_num)->Put(*code_block); delete (yyvsp[-3].int_num);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2162 "qa.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 467 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].double_num)->Put(*code_block); delete (yyvsp[-3].double_num);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2172 "qa.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 474 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		  string* buff = (yyvsp[-3].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[-3].string_value);
		}
#line 2187 "qa.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 486 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2196 "qa.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 492 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-7].instruction)->Put(*code_block); delete (yyvsp[-7].instruction);
		  (yyvsp[-5].constant)->Put(*code_block); delete (yyvsp[-5].constant);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2207 "qa.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 500 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2217 "qa.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 507 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2227 "qa.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 514 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2237 "qa.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 521 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2247 "qa.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 528 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2257 "qa.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 535 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2266 "qa.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 541 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2275 "qa.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 547 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2284 "qa.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 553 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2293 "qa.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 559 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].constant)->Put(*code_block); delete (yyvsp[-1].constant);
		}
#line 2302 "qa.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 565 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].int_num)->Put(*code_block); delete (yyvsp[-1].int_num);
		}
#line 2311 "qa.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 571 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].double_num)->Put(*code_block); delete (yyvsp[-1].double_num);
		}
#line 2320 "qa.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 577 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  string* buff = (yyvsp[-1].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[-1].string_value);
		}
#line 2334 "qa.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 588 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
	        }
#line 2343 "qa.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 594 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2352 "qa.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 600 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2361 "qa.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 606 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2370 "qa.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 612 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
	        }
#line 2379 "qa.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 618 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2388 "qa.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 624 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2397 "qa.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 630 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2406 "qa.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 636 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2415 "qa.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 642 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
#line 2424 "qa.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 648 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
	        }
#line 2433 "qa.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 654 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].constant)->Put(*code_block); delete (yyvsp[-1].constant);
		}
#line 2442 "qa.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 660 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].int_num)->Put(*code_block); delete (yyvsp[-1].int_num);
		}
#line 2451 "qa.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 666 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].double_num)->Put(*code_block); delete (yyvsp[-1].double_num);
		}
#line 2460 "qa.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 672 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  string* buff = (yyvsp[-1].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[-1].string_value);
		}
#line 2474 "qa.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 683 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2483 "qa.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 689 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2492 "qa.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 695 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2501 "qa.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 701 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2509 "qa.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 706 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-7].instruction)->Put(*code_block); delete (yyvsp[-7].instruction);
		  (yyvsp[-5].constant)->Put(*code_block); delete (yyvsp[-5].constant);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2520 "qa.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 714 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction); 
		  (yyvsp[-3].address)->Put(*code_block); delete (yyvsp[-3].address);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2530 "qa.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 721 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].address)->Put(*code_block); delete (yyvsp[-3].address);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2540 "qa.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 728 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2550 "qa.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 735 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].address)->Put(*code_block); delete (yyvsp[-1].address);
		}
#line 2559 "qa.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 741 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].address)->Put(*code_block); delete (yyvsp[-1].address);
		}
#line 2568 "qa.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 747 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2576 "qa.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 752 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].address)->Put(*code_block); delete (yyvsp[-1].address);
		}
#line 2585 "qa.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 758 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2593 "qa.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 763 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2601 "qa.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 768 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2609 "qa.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 773 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2617 "qa.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 778 "qa.y" /* yacc.c:1646  */
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-5].instruction)->SizeOf() + (yyvsp[-3].number)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);

		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
#line 2632 "qa.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 790 "qa.y" /* yacc.c:1646  */
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-3].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
#line 2645 "qa.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 800 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2653 "qa.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 805 "qa.y" /* yacc.c:1646  */
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-5].instruction)->SizeOf() + (yyvsp[-3].number)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);

		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
#line 2668 "qa.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 817 "qa.y" /* yacc.c:1646  */
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-3].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
#line 2681 "qa.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 827 "qa.y" /* yacc.c:1646  */
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-3].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
#line 2694 "qa.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 837 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
#line 2702 "qa.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 842 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2711 "qa.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 848 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2720 "qa.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 854 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2729 "qa.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 866 "qa.y" /* yacc.c:1646  */
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-15].instruction)->SizeOf() + (yyvsp[-13].reg)->SizeOf() + 6 * Code::SIZE_OF_OFFSET;

		  (yyvsp[-15].instruction)->Put(*code_block); delete (yyvsp[-15].instruction);
		  (yyvsp[-13].reg)->Put(*code_block); delete (yyvsp[-13].reg);

		  labels->AddReference(*(yyvsp[-11].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-9].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-7].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-5].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-3].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
#line 2750 "qa.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 885 "qa.y" /* yacc.c:1646  */
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-12].instruction)->SizeOf() + (yyvsp[-10].reg)->SizeOf() + (yyvsp[-8].table_size)->SizeOf();

		  (yyvsp[-12].instruction)->Put(*code_block); delete (yyvsp[-12].instruction);
		  (yyvsp[-10].reg)->Put(*code_block); delete (yyvsp[-10].reg);
		  (yyvsp[-8].table_size)->Put(*code_block); 

		  if (*(yyvsp[-5].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		 ConstantSwitchTable switch_table(jump_offset_base,
							  (yyvsp[-8].table_size), (yyvsp[-3].label_name), (yyvsp[-2].cl_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[-8].table_size);
		  delete (yyvsp[-3].label_name);
		  delete (yyvsp[-2].cl_list);
		}
#line 2780 "qa.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 913 "qa.y" /* yacc.c:1646  */
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-12].instruction)->SizeOf() + (yyvsp[-10].reg)->SizeOf() + (yyvsp[-8].table_size)->SizeOf();

		  (yyvsp[-12].instruction)->Put(*code_block); delete (yyvsp[-12].instruction);
		  (yyvsp[-10].reg)->Put(*code_block); delete (yyvsp[-10].reg);
		  (yyvsp[-8].table_size)->Put(*code_block);

		  if (*(yyvsp[-5].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   (yyvsp[-8].table_size), (yyvsp[-3].label_name), (yyvsp[-2].aal_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[-8].table_size);
		  delete (yyvsp[-3].label_name);
		  delete (yyvsp[-2].aal_list);
		}
#line 2810 "qa.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 941 "qa.y" /* yacc.c:1646  */
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-12].instruction)->SizeOf() + (yyvsp[-10].reg)->SizeOf() + (yyvsp[-8].table_size)->SizeOf();

		  (yyvsp[-12].instruction)->Put(*code_block); delete (yyvsp[-12].instruction);
		  (yyvsp[-10].reg)->Put(*code_block); delete (yyvsp[-10].reg);
		  (yyvsp[-8].table_size)->Put(*code_block);

		  if (*(yyvsp[-5].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_quantifier");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   (yyvsp[-8].table_size), (yyvsp[-3].label_name), (yyvsp[-2].aal_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[-8].table_size);
		  delete (yyvsp[-3].label_name);
		  delete (yyvsp[-2].aal_list);
		}
#line 2840 "qa.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 968 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
#line 2849 "qa.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 974 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2859 "qa.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 981 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-7].instruction)->Put(*code_block); delete (yyvsp[-7].instruction);
		  (yyvsp[-5].number)->Put(*code_block); delete (yyvsp[-5].number);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2870 "qa.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 989 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-9].instruction)->Put(*code_block); delete (yyvsp[-9].instruction);
		  (yyvsp[-7].number)->Put(*code_block); delete (yyvsp[-7].number);
		  (yyvsp[-5].reg)->Put(*code_block); delete (yyvsp[-5].reg);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2882 "qa.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 999 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-11].instruction)->Put(*code_block); delete (yyvsp[-11].instruction);
		  (yyvsp[-9].number)->Put(*code_block); delete (yyvsp[-9].number);
		  (yyvsp[-7].reg)->Put(*code_block); delete (yyvsp[-7].reg);
		  (yyvsp[-5].reg)->Put(*code_block); delete (yyvsp[-5].reg);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2895 "qa.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 1009 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-13].instruction)->Put(*code_block); delete (yyvsp[-13].instruction);
		  (yyvsp[-11].number)->Put(*code_block); delete (yyvsp[-11].number);
		  (yyvsp[-9].reg)->Put(*code_block); delete (yyvsp[-9].reg);
		  (yyvsp[-7].reg)->Put(*code_block); delete (yyvsp[-7].reg);
		  (yyvsp[-5].reg)->Put(*code_block); delete (yyvsp[-5].reg);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
#line 2909 "qa.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 1021 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.cl_list) = NULL;
		}
#line 2917 "qa.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 1025 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.cl_list) = (yyvsp[0].cl_list);
		}
#line 2925 "qa.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 1031 "qa.y" /* yacc.c:1646  */
    {
		  vector<ConstantLabel *> *tmp = new vector<ConstantLabel *>;

		  tmp->push_back((yyvsp[0].cl));

		  (yyval.cl_list) = tmp;
		}
#line 2937 "qa.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 1039 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-2].cl_list)->push_back((yyvsp[0].cl));

		  (yyval.cl_list) = (yyvsp[-2].cl_list);
		}
#line 2947 "qa.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 1047 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.cl) = new ConstantLabel((yyvsp[-2].constant), (yyvsp[0].label_name));
		  
		}
#line 2956 "qa.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 1054 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.aal_list) = NULL;
		}
#line 2964 "qa.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 1058 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.aal_list) = (yyvsp[0].aal_list);
		}
#line 2972 "qa.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 1064 "qa.y" /* yacc.c:1646  */
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back((yyvsp[0].aal));

		  (yyval.aal_list) = tmp;
		}
#line 2984 "qa.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 1072 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-2].aal_list)->push_back((yyvsp[0].aal));
		  (yyval.aal_list) = (yyvsp[-2].aal_list);
		}
#line 2993 "qa.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 1079 "qa.y" /* yacc.c:1646  */
    {
		  ASMStringPointer asm_atom((yyvsp[-4].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  long arity = (yyvsp[-2].number)->Value();
		  ASMInt<Code::NumberSizedType> *carity = new ASMInt<Code::NumberSizedType>(arity);
		  (yyval.aal) = new AtomArityLabel(atom, carity, (yyvsp[0].label_name));

		}
#line 3010 "qa.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 1094 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.aal_list) = NULL;
		}
#line 3018 "qa.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 1098 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.aal_list) = (yyvsp[0].aal_list);
		}
#line 3026 "qa.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 1104 "qa.y" /* yacc.c:1646  */
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back((yyvsp[0].aal));

		  (yyval.aal_list) = tmp;
		}
#line 3038 "qa.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 1112 "qa.y" /* yacc.c:1646  */
    {
		  (yyvsp[-2].aal_list)->push_back((yyvsp[0].aal));

		  (yyval.aal_list) = (yyvsp[-2].aal_list);
		}
#line 3048 "qa.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 1120 "qa.y" /* yacc.c:1646  */
    {
		  ASMStringPointer asm_atom((yyvsp[-4].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  long arity = (yyvsp[-2].number)->Value();
		  ASMInt<Code::NumberSizedType> *carity = new ASMInt<Code::NumberSizedType>(arity);
		  (yyval.aal) = new AtomArityLabel(atom, carity, (yyvsp[0].label_name));
		}
#line 3064 "qa.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 1135 "qa.y" /* yacc.c:1646  */
    {
		  if (*(yyvsp[0].atom_name) != "fail")
		    {
		      FatalS(__FUNCTION__, "invalid switch label ",
			     (yyvsp[0].atom_name)->c_str());
		    }
		}
#line 3076 "qa.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 1145 "qa.y" /* yacc.c:1646  */
    {
		  ASMStringPointer asm_atom((yyvsp[0].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);
		}
#line 3087 "qa.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 1152 "qa.y" /* yacc.c:1646  */
    {
                  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((Code::ConstantSizedType)((yyvsp[0].int_value)), ConstEntry::INTEGER_TYPE);

                }
#line 3096 "qa.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 1157 "qa.y" /* yacc.c:1646  */
    {
                  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((Code::ConstantSizedType)((yyvsp[0].int_value)), ConstEntry::INTEGER_TYPE);

                }
#line 3105 "qa.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 1162 "qa.y" /* yacc.c:1646  */
    {
                  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((Code::ConstantSizedType)(-(yyvsp[0].int_value)), ConstEntry::INTEGER_TYPE);

                }
#line 3114 "qa.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 1169 "qa.y" /* yacc.c:1646  */
    { 
		  (yyval.number) = new ASMInt<Code::NumberSizedType>((yyvsp[0].int_value));

                }
#line 3123 "qa.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 1176 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.int_num) = new ASMInt<long>((long)((yyvsp[0].int_value)), ConstEntry::INTEGER_TYPE);

		}
#line 3132 "qa.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 1181 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.int_num) = new ASMInt<long>((long)((yyvsp[0].int_value)), ConstEntry::INTEGER_TYPE);

		}
#line 3141 "qa.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 1186 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.int_num) = new ASMInt<long>(-(long)((yyvsp[0].int_value)), ConstEntry::INTEGER_TYPE);

		}
#line 3150 "qa.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 1193 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.double_num) = new ASMDouble<double>((double)((yyvsp[0].double_value)), ConstEntry::INTEGER_TYPE);

		}
#line 3159 "qa.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 1198 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.double_num) = new ASMDouble<double>((double)((yyvsp[0].double_value)), ConstEntry::INTEGER_TYPE);

		}
#line 3168 "qa.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 1203 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.double_num) = new ASMDouble<double>((double)(-(yyvsp[0].double_value)), ConstEntry::INTEGER_TYPE);

		}
#line 3177 "qa.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 1210 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.reg) = new ASMInt<Code::RegisterSizedType>((yyvsp[0].int_value));
		  
		}
#line 3186 "qa.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 1217 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.address) = new ASMInt<Code::AddressSizedType>((yyvsp[0].int_value));

		}
#line 3195 "qa.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 1224 "qa.y" /* yacc.c:1646  */
    {
		  ASMStringPointer asm_atom((yyvsp[0].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);
		  (yyval.constant) = new ASMInt<Code::PredSizedType>(loc);
		}
#line 3205 "qa.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 1232 "qa.y" /* yacc.c:1646  */
    {
		  (yyval.table_size) = new ASMInt<Code::TableSizeSizedType>((yyvsp[0].int_value));

		}
#line 3214 "qa.cc" /* yacc.c:1646  */
    break;


#line 3218 "qa.cc" /* yacc.c:1646  */
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
#line 1238 "qa.y" /* yacc.c:1906  */

#include "lexer.cc"

#include <stdlib.h>

#include "qa_options.h"
		
QaOptions *qa_options = NULL;

int
main(int argc, char **argv)
{
  qa_options = new QaOptions(argc, argv);

  if (!qa_options->Valid())
    {
      Usage(Program, qa_options->Usage());
    }

  if (streq(qa_options->InputFile(), qa_options->OutputFile()))
    {
      Fatal(__FUNCTION__, "Input and output file names are identical");
    }

  // Should also check for suspect extensions .qg, .qi, .qs, .ql, .qx
  asm_string_table = new ASMStringTable;
  predicate_code_blocks = new vector<CodeBlock *>;

  // Read in the assembler source
  yyin = fopen(qa_options->InputFile(), "r");
  if (yyin == NULL)
    {
      perror(__FUNCTION__);
      exit(EXIT_FAILURE);
    }
      
  int result = yyparse();
  if (result)
    {
      Fatal(__FUNCTION__, "bad .qs input file");
    }
  fclose(yyin);

  // Write out the assembled object

  // First check if any compiled predicates are too big - i.e. >= 2^16
  for (vector<CodeBlock *>::iterator iter = predicate_code_blocks->begin();
       iter != predicate_code_blocks->end();
       iter++)
    {
      if ((*iter)->Current() >= (1 << (8*sizeof(Code::OffsetSizedType))))
        {
	  Fatal(__FUNCTION__, "Compiled predicate is too big");
	}
    }

  #ifdef WIN32
  ofstream ostrm(qa_options->OutputFile(), ios_base::binary);
  #else
  ofstream ostrm(qa_options->OutputFile());
  #endif


  asm_string_table->save(ostrm);

  if (query_code_block)
    {
      query_code_block->Save(ostrm);
    }
  else
    {
      IntSave<Code::OffsetSizedType>(ostrm, 0);
    }
  
  for (vector<CodeBlock *>::iterator iter = predicate_code_blocks->begin();
       iter != predicate_code_blocks->end();
       iter++)
    {
      (*iter)->Save(ostrm);
    }

  ostrm.close();

  exit(EXIT_SUCCESS);
}

int
yyerror(const char *s)
{
  Fatal(__FUNCTION__, s);
  return(1);
}
