CPP         = g++
SRC_DIR     = ../src
PARSER_FILE = seq_par.yy
LEXER_FILE  = seq_lex.l
BIN_FILE    = seqscan
CPP_FLAGS   = -Wdeprecated-register -std=c++11

all: parser lexer
	$(CPP) $(CPP_FLAGS) $(SRC_DIR)/modifiers.cc $(SRC_DIR)/match.cc $(SRC_DIR)/pu/backtrack_unit.cc $(SRC_DIR)/pu/pattern_unit.cc punit_list.cpp parse_tree_unit.cpp parse_tree_list.cpp sanity_check.cpp final_parser.cpp seq_par.tab.c lex.yy.c -L/usr/local/opt/flex/lib -lfl -o $(BIN_FILE)
	

parser:
	bison -d $(PARSER_FILE)

lexer:
	flex $(LEXER_FILE)

clean:
	rm lex.yy.c seq_par.tab.c seq_par.tab.h $(BIN_FILE)
