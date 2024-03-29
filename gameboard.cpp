#include "gameboard.h"
#include "minimax.h"

GameScreen::GameScreen(void)
    : scr(initscr())                   /* Initialize screen                  */
	, left_turn(true)
{
    start_color();                     /* Set Colors                         */
    use_default_colors();
    init_pair(1, -1, COLOR_BLUE);      /* Background                         */
    init_pair(2, COLOR_BLACK, COLOR_WHITE); /* Window                        */
    cbreak();                          /* No waiting for the Enter key       */
    noecho();                          /* No echoing entered keys            */
	keypad(scr, TRUE);
	/* Listen for left click and left double click */
	mousemask(BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED, NULL);
    clear();                           /* Clear screen                       */

	this->ginfo = new GameInfo();      /* Initialize game rules              */
    this->draw();
    this->build_window();
	draw();
}

void GameScreen::build_window()
{
    /* Make window for game */
    getmaxyx(this->scr, this->height, this->width);
    gwnd = new GameWindow(this->width, this->height);
}

GameScreen::~GameScreen(void)
{
	delete this->ginfo;
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
    move(1,2);
	printw("%s player's turn.    ",PLAYER_LABELS[!left_turn&1]);
    /* Fill background color */
    for(unsigned int i = 0; i < this->height; ++i)
    {
        mvchgat(i, 0, -1, 0, 1, NULL);
    }
    move(0,0);
    refresh();
    /* do Window now */
    if (this->gwnd)
        this->gwnd->draw(ginfo);
}

void GameScreen::mainloop(void)
{
	/* Process keyboard input */
    int ch = 0;
	int best;
	bool done = false;
    while(!done)
    {
		ch = getch();				   /* Read keyboard input                */
		switch(ch)
		{
			case 'q':                  /* Press q to exit                    */
				done = true;
				break;
			case 'k':
        		this->destroy_window();
				break;
			case 'i':
			case 'I':
				this->draw();
				best = ginfo->get_best_move(left_turn);
				if(gwnd->move_to(best) && ginfo->move(gwnd->get_x(), gwnd->get_y(), left_turn))
	                done = endturn();
				else
				{
					move(0,2);
					printw("Can't move to %c:%c(%d)!                ", 'A' + gwnd->get_x(), '8' - gwnd->get_y(), best);
   					mvchgat(1, 0, -1, 0, 1, NULL);
				}
				break;
			case KEY_MOUSE:
				if (!this->mousemove(ch))
					break;
			case '\n':
				if(ginfo->move(gwnd->get_x(), gwnd->get_y(), left_turn))
				{
					done = endturn();
				}
				else
				{
					// TODO: Some sort of notification that this is an illigal move.
					//       OR make the player lose.
				}
				break;
			default:
				this->movecur(ch);
				break;
		}
		this->draw();
    }
}

bool GameScreen::endturn(void)
{
	bool done = false;
	int ch;
	if ((ch = ginfo->checkwin(gwnd->get_x(), gwnd->get_y())))
	{
		this->draw();
		move(1,2);
		printw("%s player's has won by %s!    ", PLAYER_LABELS[!left_turn&1], WIN_LABELS[ch]);
   		mvchgat(1, 0, -1, 0, 1, NULL);
		move(2,2);
		printw("Press ENTER to continue...");
   		mvchgat(2, 0, -1, 0, 1, NULL);
		while('\n' != getch());
		done = true;
	}
	else if (ginfo->check_stalemate())
	{
		this->draw();
		move(1,2);
		printw("STALEMATE              ");
   		mvchgat(1, 0, -1, 0, 1, NULL);
		move(2,2);
		printw("Press ENTER to continue...");
   		mvchgat(2, 0, -1, 0, 1, NULL);
		while('\n' != getch());
		done = true;
	}
	else
	{
		//this->draw();
		//MinimaxNode *n = new MinimaxNode(ginfo->get_board());
		//printw("Heuristic Value for current player: %d              ", n->heur(left_turn));
   		//mvchgat(1, 0, -1, 0, 1, NULL);
		//delete(n); n = NULL;
	}
	left_turn ^= true;
	gwnd->move_to_default(left_turn);
	return done;
}

void GameScreen::movecur(int ch)
{
    if(gwnd)
        gwnd->movecur(ch);
}

bool GameScreen::mousemove(int ch)
{
	return gwnd && gwnd->mousemove(ch);
}

GameWindow::GameWindow(unsigned int mx, unsigned int my)
	: sz_x((width + 1) * hscale + 3)
	, sz_y((height + 1) * vscale + 3)
	, wnd(newwin(sz_y, sz_x,
                 vpad - 1, hpad - 1))
    , max_x(mx)
    , max_y(my)
	, cur_x(0)
    , cur_y(0)
{

}

GameWindow::~GameWindow(void)
{
    /* Erase the contents of the window */
    this->clear();
    this->refresh();
    /* TODO: How do you free this->wnd); */
}

void GameWindow::draw(const GameInfo * const ginfo)
{
    /* TODO: Some sort of centering, maybe use printw */
    unsigned int pos = 0;
    char c = 0;

	/* Draw the played areas */
	for(int i = 0; i < 64; ++i)
	{
		wmove(this->wnd, (i / 8 + 2) * vscale - 1, (i % 8 + 1) * hscale + 1);
		wdelch(this->wnd);
		c = ginfo->get_board_at(i);
		if (c == 1 || c == 2)
		{
			winsch(this->wnd, PLAYER_LABELS[c-1][0]);
		}
		else
		{
			winsch(this->wnd, ' ');
		}
	}

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
	wmove(this->wnd, (cur_y + 2) * vscale - 1, (cur_x + 1) * hscale + 1);
}

void GameWindow::move_to_default(bool left)
{
	cur_x = cur_y = 0;
	if(!left)
		cur_x += width - 1;
}

void GameWindow::move(int x, int y)
{
	x = x % width;
	y = y % height;
	if (cur_x == 0 && x < 0)
		cur_x = width;
	if (cur_y == 0 && y < 0)
		cur_y = height;
	cur_x += x;
	cur_y += y;
	cur_x %= width;
	cur_y %= height;
}

void GameWindow::movecur(int ch)
{
	switch(ch)
	{
		case KEY_UP:
		case 'w':
		case 'W':
			this->move(0, -1);
			break;
		case KEY_LEFT:
		case 'a':
		case 'A':
			this->move(-1, 0);
			break;
		case KEY_DOWN:
		case 's':
		case 'S':
			this->move(0, 1);
			break;
		case KEY_RIGHT:
		case 'd':
		case 'D':
			this->move(1, 0);
			break;
	}
}

bool GameWindow::mousemove(int ch)
{
	MEVENT event;
	if(getmouse(&event) != OK)
		return false;
	/* Find corresponding location on game grid */
	int play_x = (event.x + 1 - hpad - 5) / hscale;
	int play_y = (event.y + 1 - vpad - 3) / vscale;

	if ((event.bstate & BUTTON1_CLICKED || event.bstate & BUTTON1_DOUBLE_CLICKED)
			&& !move_to(play_x, play_y))
		return false;

	/* Place move */
	return event.bstate & BUTTON1_DOUBLE_CLICKED;

}

bool GameWindow::move_to(int x, int y)
{
	if(x < 0 || y < 0 || x >= width || y >= height)
		return false;

	cur_x = x;
	cur_y = y;

	return true;
}


