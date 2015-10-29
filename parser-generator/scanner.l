/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

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
	#include "parser.hh"
	#include "location.hh"

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() SeqScan::Parser::make_END(SeqScan::location());

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
	// Location class can be found in location.hh and position.hh files. It's just a bit too much
	// boilerplate for this small example. Bummer.
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="SeqScan_"

%%

\                              { return SeqScan::Parser::make_SPACE(SeqScan::location()); }
\$                             { return SeqScan::Parser::make_DOLLAR(SeqScan::location()); } 
\(                             { return SeqScan::Parser::make_LPAR(SeqScan::location()); }
\)                             { return SeqScan::Parser::make_RPAR(SeqScan::location()); }
\*                             { return SeqScan::Parser::make_STAR(SeqScan::location()); } 
\+                             { return SeqScan::Parser::make_PLUS(SeqScan::location()); }
,                              { return SeqScan::Parser::make_COMMA(SeqScan::location()); }
\.                             { return SeqScan::Parser::make_DOT(SeqScan::location()); }
\/                             { return SeqScan::Parser::make_SLASH(SeqScan::location()); }
[0-9]+                         { uint32_t number = strtoul(yytext, NULL, 10); 
                                 return SeqScan::Parser::make_INT(number, SeqScan::location()); }
[actungACTUNG]+                { return SeqScan::Parser::make_STRING(yytext,SeqScan::location());  }
[a-zA-Z]+_?[0-9]+              { return SeqScan::Parser::make_LABEL(yytext, SeqScan::location()); }
\<                             { return SeqScan::Parser::make_LESS(SeqScan::location()); }
\=                             { return SeqScan::Parser::make_EQUAL(SeqScan::location()); }
\[                             { return SeqScan::Parser::make_LBRACK(SeqScan::location()); }
\]                             { return SeqScan::Parser::make_RBRACK(SeqScan::location()); }
\^                             { return SeqScan::Parser::make_HAT(SeqScan::location()); }
\{                             { return SeqScan::Parser::make_LCURLY(SeqScan::location()); }
\ ?\|\ ?                       { return SeqScan::Parser::make_OR(SeqScan::location()); }
\}                             { return SeqScan::Parser::make_RCURLY(SeqScan::location()); }
\~                             { return SeqScan::Parser::make_TILDE(SeqScan::location()); }


[\n\r]                         { return SeqScan::Parser::make_END(SeqScan::location());    }
<<EOF>>                        { return SeqScan::Parser::make_END(SeqScan::location());    }
.                              { throw PatternParseException("Unrecognized expression",m_driver.location()); }


%%
/*
.                              { std::cerr << "Scanner: Unknown character [" << yytext << "] ";
                                 std::cerr << "at location " << SeqScan::location() << std::endl;
                                 yyterminate();                                                    }
*/
