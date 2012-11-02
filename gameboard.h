#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <curses.h>

class GameWindow
{
    const WINDOW * const wnd;
    const static unsigned char width = 8;
    const static unsigned char height = 8;
    const unsigned int max_x, max_y;
public:
    GameWindow(int, int);
    ~GameWindow(void);

};

class GameScreen
{
    const WINDOW * const scr;
    GameWindow * gwnd;
public:
    GameScreen(void);
    ~GameScreen(void);
    void draw(void);
};

#endif
