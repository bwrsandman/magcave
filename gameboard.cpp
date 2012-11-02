#include "gameboard.h"

GameScreen::GameScreen(void)
    : scr(initscr())                   /* Initialize screen */
{
    cbreak();                           /* No waiting for the Enter key      */
    noecho();                          /* No echoing entered keys            */
    clear();                           /* Clear screen                       */
    this->draw();
    this->build_window(16, 16);
}

void GameScreen::build_window(unsigned int w, unsigned int h)
{
    /* Make window for game */
    unsigned int max_x, max_y;
    getmaxyx(scr, max_y, max_x);
    gwnd = new GameWindow(w, h, max_x, max_y);
}

GameScreen::~GameScreen(void)
{
    this->destroy_window();
    endwin();                          /* Restore orignial screen            */
}

void GameScreen::destroy_window()
{
    delete gwnd; gwnd = NULL;
}

void GameScreen::draw(void)
{
    /* TODO: Remove width and height */
    const char width = 8;
    const char height = 8;

    const unsigned char hscale = 5, vscale = 2, hpad = 25, vpad = 5;
    unsigned int pos=0;
    /* Top and bottom label rows (double space horizontally) */
    for(int i = 0; i < width; ++i)
    {
        pos = (i + 1) * hscale + hpad;
        move(vpad, pos);
        delch(); insch(i + 'A');       /* Clear cell and add letter          */
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

GameWindow::GameWindow(unsigned w, unsigned h, unsigned int mx, unsigned int my)
    : max_x(mx)
    , max_y(my)
    , wnd(newwin(h, w, 8, 8))         /* TODO TMP */
{
    box(this->wnd, 0 , 0);             /* 0, 0 gives default characters for
                                        * the vertical and horizontal lines  */
    wrefresh(this->wnd);               /* Show that box                      */

}

GameWindow::~GameWindow(void)
{        
    /* Erase the borders */
    wborder(this->wnd, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(this->wnd);
}
