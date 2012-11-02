#include "gameboard.h"

GameScreen::GameScreen(void)
    : scr(initscr())                   /* Initialize screen */
{
    /* Make window for game */
    int x, y;
    getmaxyx(scr, y, x);
    gwnd = new GameWindow(x, y);
    cbreak();                           /* No waiting for the Enter key */
    noecho();                          /* No echoing entered keys */
    clear();                           /* Clear screen */
    this->draw();
}

GameScreen::~GameScreen(void)
{
    delete gwnd; gwnd = NULL;          /* Free memory of GameWindow */
    endwin();                          /* Restore orignial screen */
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
        delch(); insch(i + 'A');       /* Clear cell and add letter */
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

GameWindow::GameWindow(int mx, int my)
    : max_x(mx)
    , max_y(my)
    , wnd(NULL) /* TODO TMP */
{

}

GameWindow::~GameWindow(void)
{

    /* Remove WINDOW */
}
