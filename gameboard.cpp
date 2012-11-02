#include "gameboard.h"

GameScreen::GameScreen(void)
    : scr(initscr())                   /* Initialize screen */
{
    cbreak();                           /* No waiting for the Enter key      */
    noecho();                          /* No echoing entered keys            */
    clear();                           /* Clear screen                       */
    this->draw();
    this->build_window();
}

void GameScreen::build_window()
{
    /* Make window for game */
    unsigned int max_x, max_y;
    getmaxyx(scr, max_y, max_x);
    gwnd = new GameWindow(max_x, max_y);
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
    refresh();
    /* do Window now */
    if (this->gwnd)
        this->gwnd->draw();
}

GameWindow::GameWindow(unsigned int mx, unsigned int my)
    : max_x(mx)
    , max_y(my)
    , wnd(newwin((height + 1) * vscale + 3, 
                 (width + 1) * hscale + 3, 
                 vpad - 1, hpad - 1))
{
    box(this->wnd, 0 , 0);             /* 0, 0 gives default characters for
                                        * the vertical and horizontal lines  */
    this->draw();                      /* Show that box                      */

}

GameWindow::~GameWindow(void)
{   
    /* Erase the contents of the window */
    wclear(this->wnd);
    wrefresh(this->wnd);
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
    wrefresh(this->wnd);
}
