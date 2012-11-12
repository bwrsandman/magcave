#include <iostream>           /* For cout and cin */
#include <unistd.h>           /* For sleep */
#include "gameboard.h"        /* For game board drawing using curses */
#include "minimax.h"

int main()
{
    /* Display board */
    GameScreen* pscreen = new GameScreen();
    pscreen->mainloop();
    delete pscreen; pscreen = NULL;

    return 0;
}
