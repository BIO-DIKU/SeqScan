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

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>

#include "scanner.h"
#include "parser.hh"

namespace SeqScan {



/**
 * @brief PatternParseException class for Interpreter class.
 */
class PatternParseException : public std::exception {
 public:

  PatternParseException(const std::string &msg, const int pos) :
    exceptionMsg(msg),
    position(pos)
  {}
  PatternParseException(const std::string &&msg, const int pos) :
    exceptionMsg(msg),
    position(pos)
  {}
  PatternParseException(const PatternParseException &e) :
    exceptionMsg(e.exceptionMsg),
    position(e.position)
  {}
  virtual const char* what() const noexcept{ 
    return exceptionMsg.c_str(); 
  }

  const std::string exceptionMsg;
  const int position;
};


/**
 * This class is the interface for our scanner/lexer. The end user
 * is expected to use this. It drives scanner/lexer, and returns a 
 * parse tree. Both parser and lexer have access to it via internal 
 * references.
 */
class Interpreter
{
public:
    Interpreter();
    
    /**
     * Run parser on pattern. Returns a ParseTreeUnit pointer on success, 
     * NULL on failure.
     */
    ParseTreeUnit* parse(const std::string& raw_pattern);
    
    
    /**
     * This is needed so that Scanner and Parser can call some
     * methods that we want to keep hidden from the end user.
     */
    friend class Parser;
    friend class Scanner;
    
private:
    // Used internally by Parser to set the main parse tree.
    void set_parse_tree(ParseTreeUnit* ptree);
    
    // Used internally by Scanner YY_USER_ACTION to update location indicator
    void increaseLocation(unsigned int loc);
    
    // Used to get last Scanner location. Used in error messages.
    unsigned int location() const;

    
    /**
     * Switch scanner input stream. Default is standard input (std::cin).
     */
    void switchInputStream(std::istream *is);
private:
    Scanner scanner_;
    Parser parser_;
    ParseTreeUnit* parse_tree_;
    unsigned int location_;          // Used by scanner
};

}

#endif // INTERPRETER_H
