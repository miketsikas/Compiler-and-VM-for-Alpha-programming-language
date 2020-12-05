/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    ID = 258,
    STRING = 259,
    INTEGER = 260,
    TRUE = 261,
    FALSE = 262,
    REAL = 263,
    WHILE = 264,
    FOR = 265,
    IF = 266,
    ELSE = 267,
    FUNCTION = 268,
    RETURN = 269,
    BREAK = 270,
    CONTINUE = 271,
    AND = 272,
    OR = 273,
    NOT = 274,
    NIL = 275,
    PLUS = 276,
    MINUS = 277,
    UMINUS = 278,
    ASSERTION = 279,
    MULT = 280,
    MOD = 281,
    DIV = 282,
    EQUALS = 283,
    DIFF = 284,
    PLUS1 = 285,
    MINUS1 = 286,
    GREATER_OR_EQUAL = 287,
    LESS_OR_EQUAL = 288,
    GREATER_THAN = 289,
    LESS_THAN = 290,
    LEFT_SQUARE_BRACKET = 291,
    RIGHT_SQUARE_BRACKET = 292,
    LEFT_BRACKET = 293,
    RIGHT_BRACKET = 294,
    LEFT_PARENTHESIS = 295,
    RIGHT_PARENTHESIS = 296,
    COMMA = 297,
    SEMICOLON = 298,
    COLON = 299,
    DOUBLE_COLON = 300,
    DOT = 301,
    DOUBLE_DOT = 302,
    LOCAL = 303
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define INTEGER 260
#define TRUE 261
#define FALSE 262
#define REAL 263
#define WHILE 264
#define FOR 265
#define IF 266
#define ELSE 267
#define FUNCTION 268
#define RETURN 269
#define BREAK 270
#define CONTINUE 271
#define AND 272
#define OR 273
#define NOT 274
#define NIL 275
#define PLUS 276
#define MINUS 277
#define UMINUS 278
#define ASSERTION 279
#define MULT 280
#define MOD 281
#define DIV 282
#define EQUALS 283
#define DIFF 284
#define PLUS1 285
#define MINUS1 286
#define GREATER_OR_EQUAL 287
#define LESS_OR_EQUAL 288
#define GREATER_THAN 289
#define LESS_THAN 290
#define LEFT_SQUARE_BRACKET 291
#define RIGHT_SQUARE_BRACKET 292
#define LEFT_BRACKET 293
#define RIGHT_BRACKET 294
#define LEFT_PARENTHESIS 295
#define RIGHT_PARENTHESIS 296
#define COMMA 297
#define SEMICOLON 298
#define COLON 299
#define DOUBLE_COLON 300
#define DOT 301
#define DOUBLE_DOT 302
#define LOCAL 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 43 "parser.y" /* yacc.c:1909  */

	char* strVal;
	int intVal;
	double doubleVal;
	struct forval *forVal;
	struct stmt_t *stmtVal;
	struct expr *exprVal;
	struct node *symVal; // ST node
	//struct method_t *methodVal; //maybe later

#line 161 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
