LEXYAC = scanner.l parser.y
LEXYAC_SOURCES = parser.cc scanner.cc
LEXYAC_HEADERS = include/location.hh include/parser.hh include/position.hh include/stack.hh
HEADERS = $(wildcard include/*.h) $(wildcard include/*.hh)
SOURCES = $(LEXYAC_SOURCES) $(wildcard *.cc) 
OBJECTS = $(subst .cc,.o,$(SOURCES))
LIBFILE = lib/libseqscanparser.a

all: $(LIBFILE) main

scanner.cc: scanner.l
	flex -o $@ $<

parser.cc: parser.y
	bison -o $@ $<
	mv -f *.hh include/

%.o: %.cc
	g++ -Wall -O3 -c -I ./include $< -o $@


$(LIBFILE): $(OBJECTS)
	mkdir -p lib
	ar rcs $@ $(OBJECTS)

main: $(LIBFILE)
	g++ -Wall -I ./include -L ./lib -lseqscanparser main.cpp -o main

clean:
	rm -rf $(LEXYAC_SOURCES) $(LEXYAC_HEADERS) $(OBJECTS)
	rm -rf main main.dSYM
	rm -rf $(LIBFILE)
