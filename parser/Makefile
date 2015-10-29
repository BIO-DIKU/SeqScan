CPP         = g++
SRC_DIR     = ../src
PARSER_FILE = seq_par.y
LEXER_FILE  = seq_lex.l
BIN_FILE    = seqscan
CPP_FLAGS   = -std=c++11

all: parser lexer
	$(CPP) $(CPP_FLAGS) parse_tree_unit.cpp parse_tree_list.cpp seq_par.tab.c lex.yy.c main.cpp -lfl -o $(BIN_FILE)
	

parser:
	bison -d $(PARSER_FILE)

lexer:
	flex $(LEXER_FILE)

clean:
	rm lex.yy.c seq_par.tab.c seq_par.tab.h $(BIN_FILE)
