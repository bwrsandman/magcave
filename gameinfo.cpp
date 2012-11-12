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

bool GameInfo::move(int posx, int posy)
{
	int posindex = -1;
	int position = getposition(posx, posy);
	
	/* ----------------------
	** Switch to next player
	** ----------------------
	***/
	player_no ^= 3; /* flip the last 2 bits */

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
		cout << "You have selected an unavailable position" << endl;
		// *TODO: Actually do something here
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

bool GameInfo::checkwin(int posx, int posy) const
{
	/* ----------------------------------------------------------------
	** Check if this new placement results in a win
	** Check horizontally, vertically, and diagonally around placement
	** -----------------------------------------------------------------
	***/

	int position = getposition(posx, posy);
	
	//Check for horizontal win 
	int wincount = 1;	
	//Backwards: (position -1 * i)
	for(int i = 1; i < 6; ++i)
	{
		if ((position - i) < 0 || (position-i)%8 == 7 || board[position-i] != player_no) //don't go outside the range or wrap
			break;
		else
			wincount++;
	}
	//Forwards: (position + 1 * i)
	for(int i = 1; i < 6; ++i)
	{
		if ((position + i) > 63 || (position+i)%8 == 0 || board[position+i] != player_no) //don't go outside the range or wrap
			break;
		else
			wincount++;
	}
	
	if (wincount == 5)
	{
		cout << "Player # " << player_no << " wins " << " by horizontal!" << endl;
		return true;
	}

	//Check for vertical win 
	wincount = 1;	
	// Upwards: ( (position - 8) * i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position - 8*i) < 0 || board[position - 8*i] != player_no)//don't go outside the vertical range
			break;
		else
			wincount++;	
	}
	//Downwards: ( (position + 8) * i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position + 8*i) > 63 || board[position + 8*i] != player_no)//don't go outside the vertical range
			break;
		else
			wincount++;	
	}
	
	if (wincount == 5)
	{
		cout << "Player # " << player_no << " wins " << " by vertical!" << endl;
		return true;
	}

	//Check for diagonal down win 
	wincount = 1;
	//Downwards: (position + 9 * i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position + 9 * i) > 63 || board[position + 9 * i] != player_no)//don't go outside the board
			break;
		else
			wincount++;	
	}
	//Upwards: (position - 9 * i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position - 9 * i) < 0 || board[position - 9 * i] != player_no)//don't go outside the board
			break;
		else
			wincount++;	
	}
	
	if (wincount == 5)
	{
		cout << "Player # " << player_no << " wins " << " by downward diagonal!" << endl;
		return true;
	}
	
	//Check for diagonal up win
	wincount = 1;	
	//Upwards: (position - 7 * i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position -7 * i) < 0 || board[position - 7 * i] != player_no)//don't go outside the board
			break;
		else
			wincount++;
	}
	//Downwards: (position + 7 * i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position + 7 * i) > 63 || board[position + 7 * i] != player_no)//don't go outside the board
			break;
		else
			wincount++;	
	}
	
	if (wincount == 5)
	{
		cout << "Player # " << player_no << " wins " << " by upward diagonal!" << endl;
		return true;
	}

	/* All tests have failed */
	return false;
}
