.PHONY: all

all: clean
	g++ -std=c++1y -o ld.o -c ld.cpp -Wall -O `pkg-config --cflags --libs opencv`
	g++ -o ld ld.o `pkg-config --cflags --libs opencv`

clean:
	rm -f *.o ld

