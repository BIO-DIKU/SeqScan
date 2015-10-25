SEQSCAN_PARSER_DIR = ../src/parser

all:
	flex -o scanner.cc scanner.l
	bison -o parser.cc parser.y
	g++ -g -Wall main.cc scanner.cc parser.cc interpreter.cc ptnode.cc -o main
	mkdir -p $(SEQSCAN_PARSER_DIR)
	rm -f $(SEQSCAN_PARSER_DIR)/*
	cp *.cc *.h *.hh $(SEQSCAN_PARSER_DIR)/

clean:
	rm -rf scanner.cc
	rm -rf parser.cc parser.h location.hh position.hh stack.hh
	rm -rf main
