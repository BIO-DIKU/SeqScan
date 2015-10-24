/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#include "parse_tree_unit.h"
#include "parse_tree_list.h"

#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SLASH = 258,
     COMMA = 259,
     SPACE = 260,
     LCURLY = 261,
     RCURLY = 262,
     ST = 263,
     TILDE = 264,
     OR = 265,
     QMARK = 266,
     DOT = 267,
     LPAR = 268,
     RPAR = 269,
     EQUAL = 270,
     LBRACK = 271,
     RBRACK = 272,
     PLUS = 273,
     HAT = 274,
     DOLLAR = 275,
     MULT = 276,
     INT = 277,
     STRING = 278,
     LABEL = 279
   };
#endif
/* Tokens.  */
#define SLASH 258
#define COMMA 259
#define SPACE 260
#define LCURLY 261
#define RCURLY 262
#define ST 263
#define TILDE 264
#define OR 265
#define QMARK 266
#define DOT 267
#define LPAR 268
#define RPAR 269
#define EQUAL 270
#define LBRACK 271
#define RBRACK 272
#define PLUS 273
#define HAT 274
#define DOLLAR 275
#define MULT 276
#define INT 277
#define STRING 278
#define LABEL 279



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "seq_par.y"
{
  int inval;
  char* stval;
  ParseTreeUnit* panit;
  ParseTreeList* palis;
}
/* Line 1529 of yacc.c.  */
#line 104 "seq_par.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

