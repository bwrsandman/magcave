#include <iostream>           /* For cout and cin */
#include <unistd.h>           /* For sleep */
#include "gameboard.h"        /* For game board drawing using curses */
#include "minimax.h"
#include "readxml.h"

int main(int argc, char * argv[])
{
    const char depth = (argc == 1)? DEPTH_DEFAULT: atoi(argv[1]);
    
    /* Load minimax tree from xml file. */
    const minimaxNode* n = readxmltree(xmlfilename);
    /* Perform minimax, print result. */
	MinimaxParams *p;
	signed char *pp;
    std::cout << int(*(pp=minimax(p=(new MinimaxParams(n, depth))))) << std::endl;
	delete(p);
    return 0;
}
