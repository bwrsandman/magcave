#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <ncurses.h>

class GameWindow
{
	const unsigned int sz_x, sz_y;
    WINDOW * const  wnd;
    const static unsigned char width = 8;
    const static unsigned char height = 8;
    const static unsigned char hscale = 5, vscale = 2, hpad = 25, vpad = 5;
    const unsigned int max_x, max_y;
	unsigned int cur_x, cur_y;
    void move(void) const;
    void move(int, int);
    void refresh(){wrefresh(this->wnd);}
    void clear(){wclear(this->wnd);}
public:
    GameWindow(unsigned int, unsigned int);
    ~GameWindow(void);
    void draw(void);
	void movecur(int);
};

class GameScreen
{
    WINDOW * const scr;
    GameWindow * gwnd;
    unsigned int width, height;
    void move(unsigned int a, unsigned int b) const {wmove(this->scr, a, b);}
    void refresh() const {wrefresh(this->scr);}
    void clear() const {wclear(this->scr);}
public:
    GameScreen(void);
    ~GameScreen(void);
    void build_window();
    void destroy_window();
    void draw(void);
    void mainloop(void);
	void movecur(int);
};

#endif
