/* Initial C code is wrapped in '%{' */
%{
#include <iostream>
#include "../src/pu/backtrack_unit.h"
using namespace std;

// Just flex stuff
#define YY_DECL extern "C" int yylex()
#include "seq_par.tab.h"
%}

/* Double '%' initiates lexer rules section */
/* DNA:      AGCUTRYWSMKHDVBNagcutrywsmkhdvbn */
/* RNA:      AGCUTRYWSMKHDVBNagcutrywsmkhdvbn */
/* Protein:  FLSYCWPHQRIMTNKVADEGXflsycwphqrimtnkvadegx */
/* Combined: ABCDEFGHIKLMNPQRSTUVWXYabcdefghiklmnpqrstuvwyx /*

/* All observed chars in README examples: */
/* " $()*+,./01234568<=?ACDGHKNQRST[]^p{|}~" */
%%
[0-9]+                         { yylval.inval = atoi(yytext); return INT; }
[\.]*[acgtACGT]+[acgtACGT\.]*  { yylval.stval = strdup(yytext); return STRING; }
[a-zA-Z0-9]+                   { yylval.stval = strdup(yytext); return LABEL; }
\                              { return SPACE; }
\/                             { return SLASH; }
,                              { return COMMA; }
\{                             { return LCURLY; }
\}                             { return RCURLY; }
\<                             { return ST; }
\~                             { return TILDE; }
\|                             { return OR; }
\?                             { return QMARK; }
\.                             { return DOT; }
\(                             { return LPAR; }
\)                             { return RPAR; }
\[                             { return LBRACK; }
\]                             { return RBRACK; }
=                              { return EQUAL; }
\+                             { return PLUS; }
\^                             { return HAT; }
%%
