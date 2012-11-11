#include "gameboard.h"

GameScreen::GameScreen(void)
    : scr(initscr())                   /* Initialize screen                  */
{
    start_color();                     /* Set Colors                         */
    use_default_colors();
    init_pair(1, -1, COLOR_BLUE);      /* Background                         */
    init_pair(2, COLOR_BLACK, COLOR_WHITE); /* Window                        */
    //    assume_default_colors(COLOR_WHITE, COLOR_BLUE);
    cbreak();                          /* No waiting for the Enter key       */
    noecho();                          /* No echoing entered keys            */
	keypad(scr, TRUE);
    clear();                           /* Clear screen                       */

    this->draw();
    this->build_window();
}

void GameScreen::build_window()
{
    /* Make window for game */
    getmaxyx(this->scr, this->height, this->width);
    gwnd = new GameWindow(this->width, this->height);
}

GameScreen::~GameScreen(void)
{
    this->destroy_window();
    endwin();                          /* Restore orignial screen            */
}

void GameScreen::destroy_window()
{
    delete gwnd; gwnd = NULL;
    this->draw();
}

void GameScreen::draw(void)
{
    getmaxyx(this->scr, this->height, this->width);
    /* Fill background color */
    for(unsigned int i = 0; i < this->height; ++i)
    {
        mvchgat(i, 0, -1, 0, 1, NULL);
    }
    move(0,0);
    refresh();
    /* do Window now */
    if (this->gwnd)
        this->gwnd->draw();
}

void GameScreen::mainloop(void)
{
	/* Process keyboard input */
    int ch = 0;
    while((ch = getch()) != 'q')       /* Press q to exit                    */
    {
		switch(ch)
		{
			case 'k':
        		this->destroy_window();
				break;
			default:
				this->movecur(ch);
		}
    }
}

void GameScreen::movecur(int ch)
{
    if(gwnd)
        gwnd->movecur(ch);
}

GameWindow::GameWindow(unsigned int mx, unsigned int my)
	:sz_x((width + 1) * hscale + 3) 
	, sz_y((height + 1) * vscale + 3)
	, wnd(newwin(sz_y, sz_x, 
                 vpad - 1, hpad - 1))
    , max_x(mx)
    , max_y(my)
	, cur_x(1)
    , cur_y(1)
{
    this->draw();                      /* Show that box                      */

}

GameWindow::~GameWindow(void)
{
    /* Erase the contents of the window */
    this->clear();
    this->refresh();
    /* TODO: How do you free this->wnd); */
}

void GameWindow::draw(void)
{
    /* TODO: Some sort of centering, maybe use printw */
    unsigned int pos = 0;
    char c = 0;
    /* 1, 1 avoids overwriting the borders */
    for(int i = 0; i < width; ++i)
    {
        pos = 1 + (i + 1) * hscale;
        c = 'A' + i;
        mvwdelch(this->wnd, 1, pos); 
        winsch(this->wnd, c);
        mvwdelch(this->wnd, (height + 1) * vscale + 1, pos); 
        winsch(this->wnd, c);
    }
    for(int i = 0; i < height; ++i)
    {
        pos = 1 + (i + 1) * vscale;
        c = '0' + height - i;
        mvwdelch(this->wnd, pos, 1); 
        winsch(this->wnd, c);
        mvwdelch(this->wnd, pos, (width + 1) * hscale + 1); 
        winsch(this->wnd, c);
    }
	
	//Draw lines in window
	for(int i = 0; i <= height; ++i)
    {
		pos = (i + 1) * vscale;
		wmove(this->wnd, pos, hscale - 1);
		whline(this->wnd, '_', (width*hscale));
	}
	for(int i = 0; i <= width + 1; ++i)
    {
        pos = (i) * hscale - 1;
        wmove(this->wnd, vscale + 1, pos);
		wvline(this->wnd, '|', (height*vscale));
    }
	
    for(int i = 0; i < this->height * hscale; ++i)
    {
        mvwchgat(this->wnd, i, 0, -1, 0, 2, NULL);
    }
    wattron(this->wnd, COLOR_PAIR(2));
    wattron(this->wnd, A_BOLD); 
    box(this->wnd, 0, 0);             /* 0, 0 gives default characters for
                                       * the vertical and horizontal lines  */
    wattroff(this->wnd, A_BOLD); 
    wattroff(this->wnd, COLOR_PAIR(2));
    this->move();
    this->refresh();
}

void GameWindow::move(void) const
{
	wmove(this->wnd, cur_y, cur_x);
}

void GameWindow::move(unsigned int x, unsigned int y)
{
	if (x < 1)
		cur_x = 1;
	else if (x >= sz_x - 1)
		cur_x = sz_x - 2;
	else
		cur_x = x;

	if (y < 1)
		cur_y = 1;
	else if (y >= sz_y - 1)
		cur_y = sz_y - 2;
	else
		cur_y = y;

	this->draw();
}

void GameWindow::movecur(int ch)
{
	switch(ch)
	{
		case KEY_UP:
		case 'w':
		case 'W':
			this->move(cur_x, cur_y-1);
			break;
		case KEY_LEFT:
		case 'a':
		case 'A':
			this->move(cur_x-1, cur_y);
			break;
		case KEY_DOWN:
		case 's':
		case 'S':
			this->move(cur_x, cur_y+1);
			break;
		case KEY_RIGHT:
		case 'd':
		case 'D':
			this->move(cur_x+1, cur_y);
			break;
	}
}