#include "gameboard.h"

Gameboard::Gameboard(void)
	: wnd(initscr())		    	/* Initialize window */
{
	cbreak();				    	/* No waiting for the Enter key */
    noecho();                       /* No echoing entered keys */
	clear();					    /* Clear screen */
	this->draw();
}

Gameboard::~Gameboard(void)
{
	endwin();               	    /* Restore orignial window */
	//delete wnd; wnd=NULL; 	    /* Causes error */
}

void Gameboard::draw(void)
{
    const unsigned char hscale = 5, vscale = 2, hpad = 25, vpad = 5;
    unsigned int pos=0;
    /* Top and bottom label rows (double space horizontally) */
    for(int i = 0; i < width; ++i)
    {
        pos = (i + 1) * hscale + hpad;
        move(vpad, pos);
        delch(); insch(i + 'A');    /* Clear cell and add letter */
        move((height + 1) * vscale + vpad, pos);
        delch(); insch(i + 'A');    
    }
    /* Left and Right label rows */
    for(int i = 0; i < height; ++i)
    {
        pos = (i + 1) * vscale + vpad;
        move(pos, hpad);
        delch(); insch(height - i + '0');
        move(pos, (width + 1) * hscale + hpad);
        delch(); insch(height - i + '0');
    }
	refresh();
}
