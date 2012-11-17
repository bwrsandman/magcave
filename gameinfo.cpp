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

bool GameInfo::checkline(int pos, int mul) const
{
	int wincount = 1;
	int position = pos;
	// Backwards
	for(int i = 1; i < 6; ++i)
	{
		position = pos - mul * i;
		if(position < 0 || get_board_at(position) != player_no)
			break;
		else
			++wincount;
	}
	// Forwards
	for(int i = 1; i < 6; ++i)
	{
		position = pos + mul * i;
		if(position > 63 || get_board_at(position) != player_no)
			break;
		else
			++wincount;
	}
	return wincount >= 5;
}

char GameInfo::checkwin(int posx, int posy) const
{
	/* ----------------------------------------------------------------
	** Check if this new placement results in a win
	** Check horizontally, vertically, and diagonally around placement
	** -----------------------------------------------------------------
	***/

	int position = getposition(posx, posy);
	char mults[4] = {1, 8, 6, 9};
	
	// Check for win
	for(int i = 0; i < 4; ++i)
	{
		if (checkline(position, mults[i]))
		{
			return 1 + i;
		}
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
