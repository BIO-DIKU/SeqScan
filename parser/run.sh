bison -d seq_par.y
flex seq_lex.l
g++ -std=c++11 parse_tree_list.cpp parse_tree_unit.cpp seq_par.tab.c lex.yy.c -lfl -o seqscan
