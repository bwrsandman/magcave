#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <curses.h>

class Gameboard
{
	const WINDOW * const wnd;
	const static unsigned char width = 8;
	const static unsigned char height = 8;
	public:
		Gameboard(void);
		~Gameboard(void);
		void draw(void);
};

#endif
