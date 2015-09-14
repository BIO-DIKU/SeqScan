%{
#include <cstdio>
#include <iostream>
using namespace std;
#include "../modifiers.h"
#include "../match.h"
#include "../pu/backtrack_unit.h"
#include "punit_list.h"
#include <utility>

// Stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;  
void yyerror(const char *s);

// The final list of PatternUnit objects
PunitList* plist;
%}

/* Defining token types */
%union {
  int inval;
  char* stval;
  struct {
    int mis;
    int ins;
    int del;
  } edits;
  struct {
    int min;
    int max;
  } multi;
  class BacktrackUnit* punit;
  class PunitList* pulis;
}

/* Defining invariable terminal symbols */
%token SLASH COMMA SPACE LCURLY RCURLY GT TILDE OR QMARK DOT 

/* Defining variable terminal symbols and associating them with token types */
%token <inval> INT
%token <stval> STRING

%type <punit> pattern_unit
%type <edits> misindel
%type <multi> multipliers
%type <pulis> unit_list 


/* Double '%' initiates parser grammar section */ 
%%
pattern:
  unit_list                       { plist = $1; }
  ;

unit_list:
  unit_list SPACE pattern_unit    { $1->push_back($3);
                                    $$ = $1; }
 
| pattern_unit                    { PunitList* punitlist = new PunitList();
                                    punitlist->push_back($1);
                                    $$ = punitlist; }
;

pattern_unit:
  STRING multipliers misindel     { Modifiers* modifiers = 
                                    new Modifiers(0,$3.mis,$3.ins,$3.del,$2.min,$2.max,false,false,false);
                                    $$ = new BacktrackUnit(*modifiers, $1); }

| STRING misindel multipliers     { Modifiers* modifiers = 
                                    new Modifiers(0,$2.mis,$2.ins,$2.del,$3.min,$3.max,true,false,false);
                                    $$ = new BacktrackUnit(*modifiers, $1); }

| STRING multipliers              { Modifiers* modifiers = 
                                    new Modifiers(0,0,0,0,$2.min,$2.max,false,false,false);
                                    $$ = new BacktrackUnit(*modifiers, $1); }

| STRING misindel                 { Modifiers modifiers = Modifiers::CreateMIDModifiers($2.mis,$2.ins,$2.del);
                                    $$ = new BacktrackUnit(modifiers, $1); }

| STRING                          { Modifiers modifiers = Modifiers::CreateStdModifiers();
                                    $$ = new BacktrackUnit(modifiers, $1); }
;
multipliers:
  LCURLY INT COMMA INT RCURLY     { $$.min = $2;
                                    $$.max = $4; }
;
misindel:
  SLASH INT COMMA INT COMMA INT   { $$.mis = $2;
                                    $$.ins = $4;
                                    $$.del = $6; }

| SLASH INT COMMA INT             { ; }

| SLASH INT                       { ; }
;
%%

/* Double '%' ends parser grammer section, and begins C code section */



int main(int, char**) {
  FILE *myfile = fopen("input.txt", "r");
  if (!myfile) {
    cout << "cannot open input.txt\n";
    return -1;
  }
  yyin = myfile;
  do {
    yyparse();
  } while (!feof(yyin));
  for (int i = 0; i < plist->get_size(); i++) { 
    plist->get_punit(i)->Print(cout);
    cout << "\n";
  }
}

void yyerror(const char *s) {
  cout << "EEK, parse error!  Message: " << s << endl;
  exit(-1);
}
