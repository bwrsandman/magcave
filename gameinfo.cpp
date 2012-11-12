#include "gameinfo.h"

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
	
	//Check that the position is available
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
		//... take care of it in some way we've decided
	
	//Take the position
	board[position] = player_no;
	
	//Check if it is a winning spot
	//...
	
	//Update available list
	//If a spot to the left or right is available, add it
	if (board[position + 1] == 0)
		avail_positions[posindex] = position + 1;
	else if (board[position - 1] == 0)
		avail_positions[posindex] = position + -1;
	else
		avail_positions[posindex] = -1;
	
	//Switch to new player
	if (player_no == 1)
		player_no = 2;
	else
		player_no = 1;
			
}