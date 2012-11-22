#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <ncurses.h>
#include "gameinfo.h"

const char * const PLAYER_LABELS[] = {"Left", "Right"};
const char * const WIN_LABELS[] = {"", "horizontal", "vertical", "forward diagonal", "backward diagonal"};

class GameWindow
{
	const unsigned int sz_x, sz_y;
    WINDOW * const  wnd;
    const static unsigned char width = 8;
    const static unsigned char height = 8;
    const static unsigned char hscale = 5, vscale = 2, hpad = 25, vpad = 5;
    const unsigned char max_x:4, max_y:4;
	unsigned char cur_x:4, cur_y:4;
    void move(void) const;
    void move(int, int);
    void refresh(){wrefresh(this->wnd);}
    void clear(){wclear(this->wnd);}

public:
    GameWindow(unsigned int, unsigned int);
    ~GameWindow(void);
    void draw(const GameInfo * const);
	void movecur(int);
	bool mousemove(int);
	void move_to_default(bool);
	const int get_x(){return cur_x;}
	const int get_y(){return cur_y;}
};

class GameScreen
{
    WINDOW * const scr;
    GameWindow * gwnd;
	GameInfo * ginfo;
    unsigned int width, height;
    void move(unsigned int a, unsigned int b) const {wmove(this->scr, a, b);}
    void refresh() const {wrefresh(this->scr);}
    void clear() const {wclear(this->scr);}
	bool left_turn;

public:
    GameScreen(void);
    ~GameScreen(void);
    void build_window();
    void destroy_window();
    void draw(void);
    void mainloop(void);
	void movecur(int);
	bool mousemove(int);
};

#endif
