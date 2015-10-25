/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { SeqScan }
%code requires
{
  #include <iostream>
  #include <string>
  #include <vector>
  #include <stdint.h>

  #include "ptnode.h"

  namespace SeqScan {
	class Scanner;
	class Interpreter;
  }
}

// Bison calls yylex() function that must be provided by us to suck tokens
// from the scanner. This block will be placed at the beginning of IMPLEMENTATION file (cpp).
// We define this function here (function! not method).
// This function is called only inside Bison, so we make it static to limit symbol visibility for the linker
// to avoid potential linking conflicts.
%code top
{
  #include <iostream>

  #include "scanner.h"
  #include "parser.h"
  #include "interpreter.h"
  #include "location.hh"
  
  // yylex() arguments are defined in parser.y
  static SeqScan::Parser::symbol_type yylex(SeqScan::Scanner &scanner, SeqScan::Interpreter &driver) {
      return scanner.get_next_token();
  }
  
  // you can accomplish the same thing by inlining the code using preprocessor
  // x and y are same as in above static function
  // #define yylex(x, y) scanner.get_next_token()
  
}

%lex-param { SeqScan::Scanner &scanner }
%lex-param { SeqScan::Interpreter &driver }
%parse-param { SeqScan::Scanner &scanner }
%parse-param { SeqScan::Interpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"
%token <std::string> STRING "string";
%token <std::string> LABEL "label";
%token <uint64_t> INT "number";

%token SLASH "slash";
%token COMMA "comma";
%token SPACE "space";
%token LCURLY "lcurly";
%token RCURLY "rcurly";
%token LESS "less";
%token TILDE "tilde";
%token OR "or";
%token QMARK "qmark";
%token DOT "dot";
%token LPAR "lpar";
%token RPAR "rpar";
%token EQUAL "equal";
%token LBRACK "lbrack";
%token RBRACK "rbrack";
%token PLUS "plus";
%token HAT "hat";
%token DOLLAR "dollar";
%token STAR "star";

%left EQUAL
%left OR


%type< PTNode* > unit_list;
%type< PTNode* > punit;
%type< PTSufModifier* > suffix_modifier;
%type< PTPreModifier* > prefix_modifier;

%start pattern

%%

pattern:  
  unit_list 
  { 
    driver.set_parse_tree($1);
  } 
;

unit_list : 
  unit_list SPACE punit 
  {
    $1->children_.push_back($3);
	$$ = $1;
  }
| punit	
  {
    $$ = new PTNode(PTNode::kComposite);
	$$->children_.push_back($1);
  }
;

punit : 
  STRING 
  {
    $$ = new PTNode($1);
  }
| LABEL
  {
    $$ = new PTNode(PTNode::kReference);
    $$->referenced_label_ = $1;
  }
| punit LCURLY INT COMMA INT RCURLY
  {
    $$ = new PTNode(PTNode::kRepeat);
    $$->min_repeats_ = $3;
    $$->max_repeats_ = $5;
    $$->children_.push_back($1);
  }
| punit LCURLY INT COMMA RCURLY
  {
    $$ = new PTNode(PTNode::kRepeat);
    $$->min_repeats_ = $3;
    $$->max_repeats_ = -1;
    $$->children_.push_back($1);
  }
| punit LCURLY INT RCURLY
  {
    $$ = new PTNode(PTNode::kRepeat);
    $$->min_repeats_ = $3;
    $$->max_repeats_ = $3;
    $$->children_.push_back($1);
  }
| prefix_modifier punit 
  {
    $2->add_modifier($1);
    delete $1;
    $$ = $2;
  }
| punit suffix_modifier
  {
    $1->add_modifier($2);
    delete $2;
    $$ = $1;
  }
| LABEL EQUAL punit
  {
    $3->label_ = $1;
    $$ = $3;
  }
| LPAR unit_list RPAR 
  {
    $$ = $2;
  }
| INT DOT DOT DOT INT 
  {
    $$ = new PTNode(PTNode::kRepeat);
	$$->min_repeats_ = $1;
	$$->max_repeats_ = $5;
  }
| INT DOT DOT INT 
  {
    $$ = new PTNode(PTNode::kRepeat);
	$$->min_repeats_ = $1;
	$$->max_repeats_ = $4;
  }
;

suffix_modifier :
  SLASH INT COMMA INT COMMA INT
  {
    $$ = new PTSufModifier();
    $$->mismatches_ = $2;
    $$->insertions_ = $4;
    $$->deletions_  = $6;
  }
| SLASH INT COMMA INT
  {
    $$ = new PTSufModifier();
    $$->mismatches_ = $2;
    $$->indels_     = $4;
  }
| SLASH INT
  {
    $$ = new PTSufModifier();
    $$->errors_ = $2;
  }
;

prefix_modifier :
  LESS TILDE
  {
    $$ = new PTPreModifier();
    $$->complement_ = true;
  }
| LESS
  {
    $$ = new PTPreModifier();
    $$->reverse_ = true;
  }
| TILDE
  {
    $$ = new PTPreModifier();
    $$->reverse_ = true;
    $$->complement_ = true;
  }
;

    
%%

// Bison expects us to provide implementation - otherwise linker complains
void SeqScan::Parser::error(const location &loc , const std::string &message) {
  std::cout << "Error: " << message << std::endl << "Error location: " << driver.location() << std::endl;
}
