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

#include "io.h"

#include <algorithm>
#include <string>
#include <fstream>

using namespace std;
/**
 * @brief read_file reads a fasta-formatted file.
 * All characters are converted to upper-case.
 * @param fname Path to file
 * @return a list of pairs representing each entry in the fasta file. The first member is the
 * header line and the second entry is the full sequence.
 */
vector<pair<string,string>> IO::read_fasta(const string& fname){
  ifstream in(fname.c_str(), std::ios::in | std::ios::binary);
  vector<pair<string,string>> ret;
  pair<string, string> record("","");

  //This is more efficient, but doesnt check for headers
  //From http://insanecoding.blogspot.dk/2011/11/how-to-read-in-file-in-c.html
  //if (in){
  //    //std::string contents;
  //    in.seekg(0, std::ios::end);
  //    record.second.resize(in.tellg());
  //    in.seekg(0, std::ios::beg);
  //    in.read(&record.second[0], record.second.size());
  //    in.close();
  //    record.second.erase(std::remove_if(record.second.begin(), record.second.end(), [](char x){return std::isspace(x);}), record.second.end());
  //    std::transform(record.second.begin(), record.second.end(), record.second.begin(), [](char x){return std::toupper(x);});
  //    ret.push_back(std::move(record));
  //    return std::move(ret);
  //    //return std::move(contents);
  //}
  //throw(errno);


  string line;
  while (!in.eof()){
    getline(in,line);

    if (line[0] == '>'){
      if(!record.first.empty())
        ret.push_back( std::move(record) );

      record = std::make_pair(line, "");
      continue;
    }

    std::transform(line.begin(), line.end(), line.begin(), [](char x){return std::toupper(x);});
    record.second.append(line);
  }
  in.close();
  ret.push_back( std::move(record) );
  return std::move(ret);

}
