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

#include "interpreter.h"
#include "parse_tree_unit.h"

#include <iostream>
#include <sstream>

namespace SeqScan {

Interpreter::Interpreter() :
  scanner_(*this),
  parser_(scanner_, *this),
  parse_tree_(NULL),
  location_(0)
{

}

ParseTreeUnit* Interpreter::Parse(const std::string& raw_pattern) {
  parse_tree_ = NULL;
  location_ = 0;

  //Set the input stream to read from raw_pattern
  std::istringstream string_stream(raw_pattern);
  scanner_.switch_streams(&string_stream, NULL);

  int status = parser_.parse();
  if(status==0)
    return parse_tree_;
  else
    return NULL;
}


void Interpreter::SetParseTree(ParseTreeUnit* ptree)
{
  parse_tree_ = ptree;
}

void Interpreter::IncreaseLocation(unsigned int loc) {
  location_ += loc;
  //std::cout<<"increaseLocation("<<loc<<") .. now "<<location_<<std::endl;
}

unsigned int Interpreter::Location() const {
  return location_;
}

} // namespace SeqScan
