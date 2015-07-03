#ifndef FASTA_H_
#define FASTA_H_

#include <vector>
#include <string>
#include <utility>
#include <fstream>


/**
 * @brief read_file reads a fasta-formatted file.
 * All characters are converted to upper-case.
 * @param fname Path to file
 * @return a list of pairs representing each entry in the fasta file. The first member is the
 * header line and the second entry is the full sequence.
 */
std::vector< std::pair<std::string,std::string> > read_file(std::string fname){
	std::ifstream in(fname.c_str(), std::ios::in | std::ios::binary);
    std::vector< std::pair<std::string,std::string> > ret;
    std::pair<std::string, std::string> record("","");

	std::string line;
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


#endif
