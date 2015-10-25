all:
	flex -o scanner.cc scanner.l
	bison -o parser.cc parser.y
	g++ -g -Wall main.cc scanner.cc parser.cc interpreter.cc ptnode.cc -o main
	#cp *.cc *.h *.hh ../src/parser/

clean:
	rm -rf scanner.cc
	rm -rf parser.cc parser.hpp location.hh position.hh stack.hh
	rm -rf main
