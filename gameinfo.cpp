#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "gameinfo.h"

/*
** TODO: Replace 16 & 64 with const
** Actually have something happen if a player wins or picks an invalid location
**/

LineChecker::LineChecker(const GameInfo * const g, const unsigned char p, const unsigned char m)
	: game(g)
	, pos(p)
	, mul(m)
{
}

GameInfo::GameInfo()
{	
	//Fill all available starting positions
	for(unsigned char i = 0; i < 16; ++i)
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
	
	for(unsigned char i = 0; i < 64; ++i)
	{
		board[i] = 0;
	}
}

GameInfo::~GameInfo(void)
{

}

bool GameInfo::move(unsigned char posx, unsigned char posy, bool left_player)
{
	signed char posindex = -1;
	unsigned char position = getposition(posx, posy);
	
	/* ----------------------
	** Switch to next player
	** ----------------------
	***/
	player_no = (left_player) ? 1 : 2;

	/* -----------------------------------
	** Check that a position is available
	** ----------------------------------
	***/
	for(unsigned char i = 0; i < 16; ++i)
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

void *checkline(void *plnchk)
{
	LineChecker *lnchk = (LineChecker*) plnchk;
	char wincount = 1;
	unsigned char position = lnchk->pos;
	
	// Backwards
	for(char i = 1; i < 6; ++i)
	{
		position = lnchk->pos - lnchk->mul * i;
		if(position < 0 || lnchk->game->get_board_at(position) != lnchk->game->get_player_no())
			break;
		else
			++wincount;
	}
	// Forwards
	for(char i = 1; i < 6; ++i)
	{
		position = lnchk->pos + lnchk->mul * i;
		if(position > 63 || lnchk->game->get_board_at(position) != lnchk->game->get_player_no())
			break;
		else
			++wincount;
	}
	delete(lnchk); lnchk = 0; /* Free memory */
	return (void *) new bool(wincount >= 5);
}

unsigned char GameInfo::checkwin(unsigned char posx, unsigned char posy) const
{
	/* ----------------------------------------------------------------
	** Check if this new placement results in a win
	** Check horizontally, vertically, and diagonally around placement
	** -----------------------------------------------------------------
	***/

	unsigned char position = getposition(posx, posy);
	unsigned char mults[4] = {1, 8, 7, 9};
	unsigned char ret = false;
	int rc;

	// Scatter
	for(unsigned char i = 0; i < 4; ++i)
	{
		LineChecker *c = new LineChecker(this, (unsigned char)(position), mults[i]);
		rc = pthread_create(&threads[i], NULL, checkline, c);
		assert(rc == 0);
	}

	// Gather: Check for win
	for(unsigned char i = 0; i < 4; ++i)
	{
		bool* pchk; rc = pthread_join(threads[i], (void **) &pchk);
		assert(rc == 0);
		if(*pchk)
		{
			ret = 1 + i;
		}
		delete(pchk); pchk = 0; /* Free memory */
	}

	return ret;
}

bool GameInfo::check_stalemate(void) const
{
	for (unsigned char i = 0; i < 64; ++i)
		if (board[i] == 0)
			return false;
	return true;
}
