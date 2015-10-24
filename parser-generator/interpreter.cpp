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
#include "command.h"

#include <sstream>

using namespace EzAquarii;

Interpreter::Interpreter() :
    m_scanner(*this),
    m_parser(m_scanner, *this),
    parse_tree_(NULL),
    m_location(0)
{

}

int Interpreter::parse() {
    m_location = 0;
    return m_parser.parse();
}

void Interpreter::clear() {
    m_location = 0;
	if(parse_tree_) delete parse_tree_;
	parse_tree_ = NULL;
}

std::string Interpreter::str() const {
    std::stringstream s;
    s << "Interpreter. ";
   	if(parse_tree_)
	  s<<"Parsed: "<<parse_tree_->str();
	return s.str();
}

void Interpreter::switchInputStream(std::istream *is) {
    m_scanner.switch_streams(is, NULL);
	if(parse_tree_) delete parse_tree_;
	parse_tree_ = NULL;
}

PTNode* Interpreter::parse_tree() const
{
	return parse_tree_;
}

void Interpreter::set_parse_tree(PTNode* ptree)
{
	if(parse_tree_) delete parse_tree_;
	parse_tree_ = ptree;
}

void Interpreter::increaseLocation(unsigned int loc) {
    m_location += loc;
    cout << "increaseLocation(): " << loc << ", total = " << m_location << endl;
}

unsigned int Interpreter::location() const {
    return m_location;
}
