#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <curses.h>

class GameWindow
{
    WINDOW * const  wnd;
    const static unsigned char width = 8;
    const static unsigned char height = 8;
    const static unsigned char hscale = 5, vscale = 2, hpad = 25, vpad = 5;
    const unsigned int max_x, max_y;
    void move(unsigned int a, unsigned int b){wmove(this->wnd, a, b);}
    void refresh(){wrefresh(this->wnd);}
    void clear(){wclear(this->wnd);}
public:
    GameWindow(unsigned int, unsigned int);
    ~GameWindow(void);
    void draw(void);
};

class GameScreen
{
    const WINDOW * const scr;
    GameWindow * gwnd;
    unsigned int width, height;
    void move(unsigned int a, unsigned int b) const {move(a, b);}
    void refresh() const {refresh();}
    void clear() const {clear();}
public:
    GameScreen(void);
    ~GameScreen(void);
    void build_window();
    void destroy_window();
    void draw(void);
};

#endif
