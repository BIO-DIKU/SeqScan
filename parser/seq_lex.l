/* Initial C code is wrapped in '%{' */
%{
#include <iostream>
#include "../pu/backtrack_unit.h"
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
[0-9]+      { yylval.inval = atoi(yytext); return INT; }
[acgtACGT]+ { yylval.stval = strdup(yytext); return STRING; }
\           { return SPACE; }
\/          { return SLASH; }
,           { return COMMA; }
\{          { return LCURLY; }
\}          { return RCURLY; }
\<          { return GT; }
\~          { return TILDE; }
\|          { return OR; }
\?          { return QMARK; }
\.          { return DOT; }
%%
