.PHONY: all

all: clean
	g++ -std=c++1y -o canny.o -c canny.cpp -Wall -O `pkg-config --cflags --libs opencv`
	g++ -o canny canny.o `pkg-config --cflags --libs opencv`

clean:
	rm -f *.o canny 

