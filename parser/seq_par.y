%{
#include <cstdio>
#include <iostream>
//#include "parse_tree_list.h"
#include "sanity_check.h"
using namespace std;
#include "../src/modifiers.h"
#include "../src/match.h"
#include "../src/pu/backtrack_unit.h"
#include "punit_list.h"
#include <utility>
#include <vector>
#include <map>

using namespace std;

// Stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;  
void yyerror(const char *s);

// The final list of PatternUnit objects
ParseTreeUnit* cur_unit = new ParseTreeUnit();
ParseTreeList* par_list = new ParseTreeList();
map<string, ParseTreeUnit*> vtable;
map<string, ParseTreeUnit*>::iterator vtab_it;
%}

/* Defining token types */
%union {
  int inval;
  char* stval;
  class ParseTreeUnit* panit;
  class ParseTreeList* palis;
}

/* Defining invariable terminal symbols */
%token SLASH COMMA SPACE LCURLY RCURLY ST TILDE OR QMARK DOT LPAR RPAR EQUAL LBRACK RBRACK PLUS HAT DOLLAR MULT
/* Defining variable terminal symbols and associating them with token types */
%token <inval> INT
%token <stval> STRING
%token <stval> LABEL

%type <panit> pattern_unit
%type <palis> unit_list 
%type <palis> composite

%left EQUAL
%left OR

/* Double '%' initiates parser grammar section */ 
%%
pattern:
  unit_list                              { par_list = $1; }
  ;

unit_list:
  unit_list SPACE pattern_unit           { $1->push_back($3);
                                           $$ = $1; } 
 
| HAT pattern_unit DOLLAR                { $2->start_anchor_ = true;
                                           $2->end_anchor_ = true;
                                           par_list->push_back($2);
                                           $$ = par_list; }

| HAT pattern_unit                       { $2->start_anchor_ = true;
                                           par_list->push_back($2);
                                           $$ = par_list; }

| pattern_unit DOLLAR                    { $1->end_anchor_ = true;
                                           par_list->push_back($1);
                                           $$ = par_list; }

| pattern_unit                           { par_list->push_back($1);
                                           $$ = par_list; }

;

pattern_unit:
  LBRACK group_contents RBRACK PLUS      { cur_unit->type_ = 7;
                                           cur_unit->group_greedy_ = true;
                                           $$ = cur_unit;
                                           cur_unit = new ParseTreeUnit(); }

| LBRACK group_contents RBRACK           { cur_unit->type_ = 7;
                                           $$ = cur_unit;
                                           cur_unit = new ParseTreeUnit(); }

| LPAR composite RPAR                    { ParseTreeUnit* unit = new ParseTreeUnit();
                                           unit->composite_ = $2;
                                           unit->type_ = 3;
                                           $$ = unit; }

| LABEL EQUAL pattern_unit               { $3->type_ = 4;
                                           vtable[$1] = $3;
                                           $$ = $3; }

| front_modifiers LABEL back_modifiers   { vtab_it = vtable.find($2);
                                           if (vtab_it != vtable.end()) {
                                             cur_unit->type_ = 5;
                                             cur_unit->reference_ = vtab_it->second;
                                             $$ = cur_unit;
                                           } else {
                                               cout << "Unknown pattern unit: " << $2 << "\n";
                                               return -1;
                                           } }

| LABEL back_modifiers                   { vtab_it = vtable.find($1);
                                           if (vtab_it != vtable.end()) {
                                             cur_unit->type_ = 5;
                                             cur_unit->reference_ = vtab_it->second;
                                             $$ = cur_unit;
                                           } else {
                                               cout << "Unknown pattern unit: " << $1 << "\n";
                                               return -1;
                                           } }



| pattern_unit OR pattern_unit           { ParseTreeUnit* unit = new ParseTreeUnit();
                                           unit->init_or_units();
                                           unit->type_ = 6;
                                           unit->insert_or_units($1, $3);
                                           $$ = unit; }

| front_modifiers STRING back_modifiers  { cur_unit->sequence_ = $2;
                                           cur_unit->type_ = 1;
                                           $$ = cur_unit;
                                           cur_unit = new ParseTreeUnit(); }

| STRING back_modifiers                  { cur_unit->sequence_ = $1;
                                           cur_unit->type_ = 1;
                                           $$ = cur_unit;
                                           cur_unit = new ParseTreeUnit(); }

| INT DOT DOT DOT INT                    { cur_unit->type_ = 2;
                                           cur_unit->range_min_ = $1;
                                           cur_unit->range_max_ = $5;
                                           $$ = cur_unit;
                                           cur_unit = new ParseTreeUnit(); }

| INT DOT DOT INT                        { cur_unit->type_ = 2;
                                           cur_unit->range_min_ = $1;
                                           cur_unit->range_max_ = $4; 
                                           $$ = cur_unit;
                                           cur_unit = new ParseTreeUnit(); }

;

group_contents:
  HAT STRING                             { cur_unit->group_not_ = true;
                                           cur_unit->group_ = $2; }

| STRING                                 { cur_unit->group_ = $1; }
;

front_modifiers:
  ST TILDE                               { cur_unit->complement_ = true; }

| ST                                     { cur_unit->reverse_ = true; }

| TILDE                                  { cur_unit->complement_ = true;
                                           cur_unit->reverse_ = true; }

;

back_modifiers:
  edits repeats                          { ; }

| repeats edits                          { ; }

| edits                                  { ; }

| repeats                                { ; }

|                                        { ; }
;

composite:
  composite SPACE pattern_unit           { $1->push_back($3);
                                           cur_unit = new ParseTreeUnit();
                                           $$ = $1; }

| pattern_unit                           { ParseTreeList* units = new ParseTreeList();
                                           units->push_back($1);
                                           cur_unit = new ParseTreeUnit();
                                           $$ = units; }
;

edits:
  SLASH INT COMMA INT COMMA INT          { cur_unit->mis_ = $2; 
                                           cur_unit->ins_ = $4; 
                                           cur_unit->del_ = $6; }

| SLASH INT COMMA INT                    { cur_unit->mis_ = $2; 
                                           cur_unit->indel_ = $4; }

| SLASH INT                              { cur_unit->edits_ = $2; }
;

repeats:
  LCURLY INT COMMA INT RCURLY QMARK      { cur_unit->min_repeats_ = $2; 
                                           cur_unit->max_repeats_ = $4;
                                           cur_unit->non_greedy_ = true; }

| LCURLY INT COMMA RCURLY QMARK          { cur_unit->min_repeats_ = $2;
                                           cur_unit->rep_open_ = true;
                                           cur_unit->non_greedy_ = true;  }

| LCURLY INT COMMA INT RCURLY            { cur_unit->min_repeats_ = $2; 
                                           cur_unit->max_repeats_ = $4; }

| LCURLY INT COMMA RCURLY                { cur_unit->min_repeats_ = $2;
                                           cur_unit->rep_open_ = true; }

| LCURLY INT RCURLY                      { cur_unit->min_repeats_ = $2; }
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
  for (int i = 0; i < par_list->get_size(); i++) {
    ParseTreeUnit* x = par_list->get_parse_unit(i);
    par_list->get_parse_unit(i)->pprint();
  }
  check_sanity(par_list);
}

void yyerror(const char *s) {
  cout << "EEK, parse error!  Message: " << s << endl;
  exit(-1);
}
