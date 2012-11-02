#include <iostream>           /* For cout and cin */
#include <unistd.h>           /* For sleep */
#include "gameboard.h"        /* For game board drawing using curses */
#include "minimax.h"
#include "readxml.h"

int main(int argc, char * argv[])
{
    const char depth = (argc == 1)? DEPTH_DEFAULT: atoi(argv[1]);
    
    /* Display board */
    GameScreen* pscreen = new GameScreen();
    sleep(2);
    delete pscreen; pscreen = NULL;
    
    /* Load minimax tree from xml file. */
    const minimaxNode* n = readxmltree(xmlfilename);
    /* Perform minimax, print result. */
    std::cout << int(minimax(n, depth)) << std::endl;
    return 0;
}
