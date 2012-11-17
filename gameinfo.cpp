#include "gameinfo.h"

/*
** TODO: Replace 16 & 64 with const
** Actually have something happen if a player wins or picks an invalid location
**/

GameInfo::GameInfo()
{	
	//Fill all available starting positions
	for(int i = 0; i < 16; ++i)
	{
		//initialize A column (0,8,...,56)
		if (i < 8)
			avail_positions [i] = 8 * i;
		//initialize H column (7,15,...,63)
		else
			avail_positions [i] =  7 + 8*(i%8);
	}
	
	//Either player 1 or 2
	player_no = 2;
	
	for(int i = 0; i < 64; ++i)
	{
		board[i] = 0;
	}
}

GameInfo::~GameInfo(void)
{

}

bool GameInfo::move(int posx, int posy, bool left_player)
{
	int posindex = -1;
	int position = getposition(posx, posy);
	
	/* ----------------------
	** Switch to next player
	** ----------------------
	***/
	player_no = (left_player) ? 1 : 2;

	/* -----------------------------------
	** Check that a position is available
	** ----------------------------------
	***/
	for(int i = 0; i < 16; ++i)
	{
		if (position == avail_positions[i])
		{
			posindex = i;
			break;	
		}		
	}	
	if (posindex==-1)
	{
		return false;
	}
	
	//Take the position:	
	board[position] = player_no;
	
	/* ----------------------
	** Update available list
	** ----------------------
	***/
	//If a spot to the left or right is available, add it (make sure we are not on edge)
	if ( (position+1)%8 != 0 && board[position + 1] == 0)
		avail_positions[posindex] = position + 1;
	else if ( (position-1)%8 != 7 && board[position - 1] == 0)
		avail_positions[posindex] = position - 1;
	else
		avail_positions[posindex] = -1;
	
	return true;
}

// TODO: Fix forward diagonal
bool *checkline(struct line_checker * lnchk)
{
	int wincount = 1;
	int position = lnchk->pos;
	// Backwards
	for(int i = 1; i < 6; ++i)
	{
		position = lnchk->pos - lnchk->mul * i;
		if(position < 0 || lnchk->game->get_board_at(position) != lnchk->game->get_player_no())
			break;
		else
			++wincount;
	}
	// Forwards
	for(int i = 1; i < 6; ++i)
	{
		position = lnchk->pos + lnchk->mul * i;
		if(position > 63 || lnchk->game->get_board_at(position) != lnchk->game->get_player_no())
			break;
		else
			++wincount;
	}
	return new bool(wincount >= 5);
}

char GameInfo::checkwin(int posx, int posy) const
{
	/* ----------------------------------------------------------------
	** Check if this new placement results in a win
	** Check horizontally, vertically, and diagonally around placement
	** -----------------------------------------------------------------
	***/

	int position = getposition(posx, posy);
	
	//Check for horizontal win 
	if (checkline(this, position, 1))
	{
		return WIN_BY_HORIZONTAL;
	}

	//Check for vertical win 
	if (checkline(this, position, 8))
	{
		return WIN_BY_VERTICAL;
	}

	//Check for diagonal down win 
	if (checkline(this, position, 9))
	{
		return WIN_BY_BDIAGONAL;
	}
	
	//Check for diagonal up win
	if (checkline(this, position, 6))
	{
		return WIN_BY_FDIAGONAL;
	}

	/* All tests have failed */
	return false;
}

bool GameInfo::check_stalemate(void) const
{
	for (int i = 0; i < 64; ++i)
		if (board[i] == 0)
			return false;
	return true;
}
