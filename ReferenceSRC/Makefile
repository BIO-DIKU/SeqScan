
CPP=g++
CFLAGS=-std=c++11 -O2

all: kmp bitap

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $^

bitap: bitap.o 
	g++ $(CFLAGS) -o $@ $^

kmp: kmp.o 
	g++ $(CFLAGS) -o $@ $^

clean:
	rm -f kmp bitap *.o
