/* Initial C code is wrapped in '%{' */
%{
// Just flex stuff
#define YY_DECL extern "C" int yylex()
#include "seq_par.tab.hh"
%}

/* Double '%' initiates lexer rules section */
/* DNA:      AGCUTRYWSMKHDVBNagcutrywsmkhdvbn */
/* RNA:      AGCUTRYWSMKHDVBNagcutrywsmkhdvbn */
/* Protein:  FLSYCWPHQRIMTNKVADEGXflsycwphqrimtnkvadegx */
/* Combined: ABCDEFGHIKLMNPQRSTUVWXYabcdefghiklmnpqrstuvwyx */

/* All observed chars in README examples: */
/* " $()*+,./01234568<=?ACDGHKNQRST[]^p{|}~" */
%%
\                              { return SPACE; }
\$                             { return DOLLAR; } 
\(                             { return LPAR; }
\)                             { return RPAR; }
\*                             { return MULT; } 
\+                             { return PLUS; }
,                              { return COMMA; }
\.                             { return DOT; }
\/                             { return SLASH; }
[0-9]+                         { yylval.inval = atoi(yytext); return INT; }
[\.]*[acgtACGT]+[acgtACGT\.]*  { yylval.stval = strdup(yytext); return STRING; }
[a-zA-Z0-9]+                   { yylval.stval = strdup(yytext); return LABEL; }
\<                             { return ST; }
=                              { return EQUAL; }
\?                             { return QMARK; }
\[                             { return LBRACK; }
\]                             { return RBRACK; }
\^                             { return HAT; }
\{                             { return LCURLY; }
\|                             { return OR; }
\}                             { return RCURLY; }
\~                             { return TILDE; }
%%
