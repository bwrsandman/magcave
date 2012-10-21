#include <iostream>           /* For cout and cin */
#include "minimax.h"
#include "readxml.h"

int main(int argc, char * argv[])
{
    const char depth = (argc == 1)? DEPTH_DEFAULT: atoi(argv[1]);
    /* Load minimax tree from xml file. */
    const minimaxNode* n = readxmltree(xmlfilename);
    /* Perform minimax, print result. */
    std::cout << int(minimax(n, depth)) << std::endl;
    return 0;
}
