bison -d seq_par.y
flex seq_lex.l
g++ -std=c++11 ../modifiers.cc ../match.cc ../pu/backtrack_unit.cc ../pu/pattern_unit.cc punit_list.cpp seq_par.tab.c lex.yy.c -lfl -o seqscan
