.PHONY: all

all: clean
	g++ -std=c++1y -o panorama.o -c panorama.cpp -Wall -O `pkg-config --cflags --libs opencv`
	g++ -o panorama panorama.o `pkg-config --cflags --libs opencv`

clean:
	rm -f *.o panorama 

