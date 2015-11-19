#!/usr/bin/env python
#Usage: pyRegexMatch.py <regex pattern> <file>

import regex
import sys


def read_fasta(fname):
    ret = {}
    entry_pat = regex.compile(">(.*)\n([^>]*)")
    with open(fname) as fasta_file:
        for m in entry_pat.finditer(fasta_file.read()):
            ret[m.group(1)] = m.group(2).replace("\n","")
    return ret

pat = regex.compile(sys.argv[1], regex.IGNORECASE)
fasta_file = read_fasta(sys.argv[2])
for header in fasta_file:
    for m in pat.finditer(fasta_file[header]):
        print header+"\t"+str(m.start(0))+"\t"+m.group(0)


