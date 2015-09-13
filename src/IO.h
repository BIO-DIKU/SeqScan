//
// Created by Rasmus Fonseca on 13/09/15.
//

#ifndef SEQSCAN_IO_H
#define SEQSCAN_IO_H


#include <iosfwd>
#include <utility>
#include <vector>

class IO {
public:
  static std::vector< std::pair<std::string,std::string>> read_fasta(const std::string& fname);

};


#endif //SEQSCAN_IO_H
