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

#include "interpreter.h"
#include "ptnode.h"

#include <sstream>

namespace SeqScan {

Interpreter::Interpreter() :
  scanner_(*this),
  parser_(scanner_, *this),
  parse_tree_(NULL),
  location_(0)
{

}

PTNode* Interpreter::parse(const std::string& raw_pattern) {
  parse_tree_ = NULL;
  location_ = 0;

  //Set the input stream to read from raw_pattern
  std::istringstream string_stream(raw_pattern);
  switchInputStream(&string_stream);

  int status = parser_.parse();
  if(status==0)
    return parse_tree_;
  else
    return NULL;
}

void Interpreter::switchInputStream(std::istream *is) {
  scanner_.switch_streams(is, NULL);
}


void Interpreter::set_parse_tree(PTNode* ptree)
{
  parse_tree_ = ptree;
}

void Interpreter::increaseLocation(unsigned int loc) {
  location_ += loc;
}

unsigned int Interpreter::location() const {
  return location_;
}

} // namespace SeqScan
