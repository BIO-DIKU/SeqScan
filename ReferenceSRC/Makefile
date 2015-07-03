
CPP=g++
CFLAGS=-std=c++11 -O2

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $^

bitap: bitap.o 
	g++ $(CFLAGS) -o $@ $^

clean:
	rm -f bitap *.o
