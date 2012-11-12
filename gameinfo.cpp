#include "gameinfo.h"

/*
** *TODO: Replace 16, 64 with const
** Clean up win verification
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
	player_no = 1;
	
	//will change this just couldnt rememer best way to initialize
	for(int i = 0; i < 64; ++i)
	{
		board[i] = 0;
	}
}

GameInfo::~GameInfo(void)
{

}

void GameInfo::move(int posx, int posy)
{
	int posindex = -1;
	int position = posx + 8*(posy);
	
	/* -----------------------------------
	** Check that a position is available
	** ----------------------------------
	***/
	bool avail = false;
	for(int i = 0; i < 16; ++i)
	{
		if (position == avail_positions[i])
		{
			posindex = i;
			break;	
		}		
	}	
	if (posindex==-1)
		cout << "You have selected an unavailable position" << endl;
		// *TODO: Actually do something here
	
	//Take the position:	
	board[position] = player_no;
	
	/* ----------------------------------------------------------------
	** Check if this new placement results in a win
	** Check horizontally, vertically, and diagonally around placement
	** -----------------------------------------------------------------
	***/
	
	//Check for horizontal win 
	int wincount = 1;	
		//Backwards: (position -1 ) * i
	for(int i = 1; i < 6; ++i)
	{
		if ((position - i) < 0 || (position-i)%8 == 7) //don't go outside the range or wrap
			break;
		if (board[position-i] == player_no)
			wincount++;
		else
			break; //stop lookin in that direction
	}
		//Forwards: (position + 1) * i
	for(int i = 1; i < 6; ++i)
	{
		if ((position + i) > 63 || (position+i)%8 == 0) //don't go outside the range or wrap
			break;
		if (board[position+i] == player_no)
			wincount++;
		else
			break;
	}
	
	//Check for vertical win 
	wincount = 1;	
		//Downwards: (position - 8*i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position - 8*i) < 0 )//don't go outside the vertical range
			break;
		if ((board[position - 8*i] == player_no))
			wincount++;	
		else
			break;
	}
		//Upwards: (position + 8) * i) )
	for(int i = 1; i < 6; ++i)
	{
		if ( (position + 8*i) > 63 )//don't go outside the vertical range
			break;
		if ((board[position + 8*i] == player_no))
			wincount++;	
		else
			break;
	}
	
	//Check for diagonal down win 
	wincount = 1;
		//Downwards: (position + i + 8*i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position + i + 8*i) > 63 )//don't go outside the board
			break;
		if ((board[position + i + 8*i] == player_no))
			wincount++;	
		else
			break;
	}
		//Upwards: (position - i - 8*i))
	for(int i = 1; i < 6; ++i)
	{
		if ( (position - i - 8*i) < 0 )//don't go outside the board
			break;
		if ((board[position - i - 8*i] == player_no))
			wincount++;	
		else
			break;
	}
	
	//Check for diagonal up win
	wincount = 1;
	
		//Upwards: (position + i - 8*i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position + i - 8*i) < 0 )//don't go outside the board
			break;
		if ((board[position + i - 8*i] == player_no))
			wincount++;	
		else
			break;
	}
		//Downwards: (position - i + 8*i)
	for(int i = 1; i < 6; ++i)
	{
		if ( (position - i + 8*i) > 63 )//don't go outside the board
			break;
		if ((board[position - i + 8*i] == player_no))
			wincount++;	
		else
			break;
	}
	
	cout << "wincount # " << wincount << endl;
	
	if (wincount == 5)
		cout << "Player # " << player_no << " wins! " << endl;
	
	
	/* ----------------------
	** Update available list
	** ----------------------
	***/
	//If a spot to the left or right is available, add it (make sure we are not on edge)
	if ( (position+1)%8 != 0 && board[position + 1] == 0)
		avail_positions[posindex] = position + 1;
	else if ( (position-1)%8 != 7	&& board[position - 1] == 0)
		avail_positions[posindex] = position - 1;
	else
		avail_positions[posindex] = -1;
	
	/* ----------------------
	** Switch to next player
	** ----------------------
	***/
	if (player_no == 1)
		player_no = 2;
	else
		player_no = 1;
			
}