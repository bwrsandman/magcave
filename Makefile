all:
	g++ minimax.cpp readxml.cpp -I/usr/include/libxml2 -lxml2 -o minimax
