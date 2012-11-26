#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <climits>            /* For SCHAR_MIN */
#include <unistd.h>	
#include "gameinfo.h"

/*
** TODO: Replace 16 & 64 with const
** Actually have something happen if a player wins or picks an invalid location
**/

LineChecker::LineChecker(const unsigned char * const board, const unsigned char p, const unsigned char m, const unsigned char player_no)
	: board(board)
	, pos(p)
	, mul(m)
    , player(player_no)
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
	
	update_avail_list(avail_positions, board, posindex, position);
	
	return true;
}

void update_avail_list(signed char * avail_positions, unsigned char * board, signed char posindex, unsigned char position)
{
	/* Update available list */
	//If a spot to the left or right is available, add it (make sure we are not on edge)
	if ( (position+1)%8 != 0 && board[position + 1] == 0)
		avail_positions[posindex] = position + 1;
	else if ( (position-1)%8 != 7 && board[position - 1] == 0)
		avail_positions[posindex] = position - 1;
	else
		avail_positions[posindex] = -1;
}

void *checkline(void *plnchk)
{
	LineChecker *lnchk = (LineChecker*) plnchk;
	char wincount = 1;
	signed char position = lnchk->pos;
	
	// Backwards
	for(char i = 1; i < 5; ++i)
	{
		position = lnchk->pos - mults[lnchk->mul] * i;
		if( (lnchk->mul == 0 && position % 8 == 7) || (lnchk->mul == 1 && position > lnchk->pos) ||
			(lnchk->mul == 2 && position % 8 == 0) || (lnchk->mul == 3 && position % 8 == 7) )
			break;
		else if(position < 0 || lnchk->board[position] != lnchk->player)
			break;
		else
			++wincount;
	}
	// Forwards
	for(char i = 1; i < 5; ++i)
	{
		position = lnchk->pos + mults[lnchk->mul] * i;
		if( (lnchk->mul == 0 && position % 8 == 0) || (lnchk->mul == 1 && position < lnchk->pos) ||
			(lnchk->mul == 2 && position % 8 == 7) || (lnchk->mul == 3 && position % 8 == 0) )
			break;
		else if(position > 63 || lnchk->board[position] != lnchk->player)
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

	return check_win(getposition(posx, posy), get_board(), get_player_no());
}

unsigned char check_win(unsigned char position, const unsigned char * const board, const unsigned char player_no)
{
	pthread_t threads[4];				/* For running 4 line checks in parallel*/
	unsigned char ret = false;
	int rc;

	// Scatter
	for(unsigned char i = 0; i < 4; ++i)
	{
		assert(pthread_create(&threads[i], 
					          NULL, 
							  checkline, 
							  new LineChecker(board, (unsigned char)position, i, player_no)) 
				== 0);
	}

	// Gather: Check for win
	for(unsigned char i = 0; i < 4; ++i)
	{
		bool* pchk; 
		assert(rc = pthread_join(threads[i], (void **) &pchk) == 0);
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

/* TODO: Add randomness when same scores appear */
const int GameInfo::get_best_move(bool left_player) const
{
	MinimaxNode * moves[16];
	signed char score[16];
	unsigned char max = 0;

	for(unsigned char i=0; i < 16; ++i)
	{
		if(avail_positions[i] == -1)
			continue;
		moves[i] = build_minimax_tree(board, avail_positions[i], (unsigned char)(left_player) + 1);
	}

	for(unsigned char i=0; i < 16; ++i)
	{
		if(avail_positions[i] == -1)
			continue;
		score[i] = minimax(moves[i], DEPTH_DEFAULT) * (left_player?-1:1);
		delete(moves[i]); moves[i] = NULL;
	}

	for(unsigned char i=0; i < 16; ++i)
	{
		if(avail_positions[i] == -1)
			continue;
		if (score[i] > score[max])
			max = i;
	}

	return avail_positions[max];
}

MinimaxNode * build_minimax_tree(const unsigned char * const board, const signed char new_pos, unsigned char player_no)
{
	return new MinimaxNode(board, new_pos, player_no);
}
