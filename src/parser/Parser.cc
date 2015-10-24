//
// Created by Rasmus Fonseca on 22/10/15.
//

#include "Parser.h"

#include <iostream>
#include <cstdio>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "seq_par.tab.hh"
#include "pu/backtrack_unit.h"

using namespace std;


extern "C" FILE *yyin;
extern ParseTreeList* par_list;

Parser::Parser()
{}

std::unique_ptr<PatternUnit> Parser::parse(std::string raw_pattern)
{
  first_parse(raw_pattern);

}

PatternUnit* Parser::final_parse(ParseTreeList* plist)
{

  return NULL;
}


ParseTreeList* Parser::first_parse(std::string raw_pattern)
{

  //FILE* in = fopen(raw_pattern.c_str(),"r");
  //yyin = in;
  //yyparse();
  //do {
  //  yyparse();
  //} while (!feof(yyin));
  //fclose(in);

  //for (int i = 0; i < par_list->get_size(); i++) {
  //  ParseTreeUnit* x = par_list->get_parse_unit(i);
  //  par_list->get_parse_unit(i)->pprint();
  //}

  ParseTreeList* ret = seq_par_main();
  for (int i = 0; i < ret->get_size(); i++) {
    ret->get_parse_unit(i)->pprint();
  }


  return NULL;
}
