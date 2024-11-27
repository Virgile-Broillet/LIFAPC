all: main

main: main.cpp cpp/Image1D.cpp hpp/Image1D.hpp
	g++ -o main main.cpp cpp/Image1D.cpp

clean:
	rm -f main