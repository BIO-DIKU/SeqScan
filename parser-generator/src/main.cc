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


#include <iostream>
#include <sstream>
#include <string>

#include "scanner.h"
#include "parser.hh"
#include "interpreter.h"

using namespace SeqScan;
using namespace std;

int main(int argc, char **argv) {
  Interpreter i;

  if(argc==0){
    cout<<"Usage: "<<argv[0]<<" \"seqscan pattern\""<<endl;
  }

  try{
	  ParseTreeUnit* parsetree = i.parse(argv[1]);
	  cout << "Parse complete. Parse tree:"<< endl;
	  cout << parsetree->str(0)<<endl;
  }
  catch (PatternParseException& exc){
	  cerr << "SeqScan: " << exc.exceptionMsg << endl;
	  cerr << argv[1] << endl;
	  for(int i=0;i<exc.position-1;i++)
		  cerr<<" ";
	  cerr << "^"<<endl;
  }
}
