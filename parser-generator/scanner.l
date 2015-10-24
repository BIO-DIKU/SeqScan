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

%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"

	using namespace std;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() EzAquarii::Parser::make_END(EzAquarii::location());

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);
	
	// !!!WARNING!!!
	// Location API is used, but the location is not initialized, 'cause I'm lazy. When making
	// a token with make_{something} method you can pass detailed token location. Current location
	// is accessible with m_driver.location() method. All puzzle elements are there - just
	// pass location value in every action code block below. I'm going to waste more time writing
	// this excuse than putting this boilerplate below...
	//
	// Location class can be found in location.hh and posistion.hh files. It's just a bit too much
	// boilerplate for this small example. Bummer.
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="EzAquarii_"

%%


[a-zA-Z]+   { return EzAquarii::Parser::make_STRING(yytext, EzAquarii::location());     }
p[0-9]+     { return EzAquarii::Parser::make_LABEL(yytext, EzAquarii::location());      }
[0-9]+      { uint64_t number = strtoull(yytext, 0, 10);
              return EzAquarii::Parser::make_INT(number, EzAquarii::location());        }
\           { return EzAquarii::Parser::make_SPACE(EzAquarii::location());              }
\(          { return EzAquarii::Parser::make_LPAR(EzAquarii::location());               }
\)          { return EzAquarii::Parser::make_RPAR(EzAquarii::location());               }
\/          { return EzAquarii::Parser::make_SLASH(EzAquarii::location());              }
\=          { return EzAquarii::Parser::make_EQUAL(EzAquarii::location());              }
\*          { return EzAquarii::Parser::make_STAR(EzAquarii::location());               }
\+          { return EzAquarii::Parser::make_PLUS(EzAquarii::location());               }
\,          { return EzAquarii::Parser::make_COMMA(EzAquarii::location());              }
\.          { return EzAquarii::Parser::make_DOT(EzAquarii::location());                }
\[          { return EzAquarii::Parser::make_LBRACK(EzAquarii::location());             }
\]          { return EzAquarii::Parser::make_RBRACK(EzAquarii::location());             }
\^          { return EzAquarii::Parser::make_HAT(EzAquarii::location());                }
\{          { return EzAquarii::Parser::make_LCURLY(EzAquarii::location());             }
\}          { return EzAquarii::Parser::make_RCURLY(EzAquarii::location());             }
\|          { return EzAquarii::Parser::make_OR(EzAquarii::location());                 }
\~          { return EzAquarii::Parser::make_TILDE(EzAquarii::location());              }
\<          { return EzAquarii::Parser::make_LESS(EzAquarii::location());               }


.           { cerr << "Scanner: unknown character [" << yytext << "]" << endl;          }
[\n\r]      { return EzAquarii::Parser::make_END(EzAquarii::location());                }
<<EOF>>     { return EzAquarii::Parser::make_END(EzAquarii::location());                }


%%
//<<EOF>>     { return yyterminate(); }
