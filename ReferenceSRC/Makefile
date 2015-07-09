
CPP=g++
CFLAGS=-std=c++11 -Ofast

all: kmp bitap manachers naivePalindrome

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $^

bitap: bitap.o 
	g++ $(CFLAGS) -o $@ $^

kmp: kmp.o 
	g++ $(CFLAGS) -o $@ $^

manachers: manachers.o 
	g++ $(CFLAGS) -o $@ $^

naivePalindrome: naivePalindrome.o 
	g++ $(CFLAGS) -o $@ $^


clean:
	rm -f manachers kmp bitap *.o
