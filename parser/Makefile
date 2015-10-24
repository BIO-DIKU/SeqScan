all:
	bison -d seq_par.y
	flex seq_lex.l
	g++ -std=c++0x parse_tree_list.cpp parse_tree_unit.cpp seq_par.tab.c lex.yy.c main.cpp -lfl -o seqscan

clean:
	rm -rf lex.yy.c seq_par.tab.h seq_par.tab.c seqscan

