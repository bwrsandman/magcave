#include "gameinfo.h"

int main(int argc, char * argv[])
{
	GameInfo * test = new GameInfo();
	
	//check for available positions
	/**
	for(int i = 0; i < 16; ++i)
	{
		cout << test.avail_positions[i] << endl;
	}
	**/

	//test horizontal
	/**
	test.move(0,7);
	test.move(0,0);
	test.move(1,0);
	test.move(7,5);
	test.move(2,0);
	test.move(7,3);
	test.move(3,0);
	test.move(7,4);
	test.move(4,0);
	test.move(7,7);
	test.move(5,0);
	**/
	
	//test vertical
	/**
	test.move(0,1);
	test.move(7,1);
	test.move(0,2);
	test.move(7,2);
	test.move(0,3);
	test.move(7,3);
	test.move(7,4);
	test.move(0,4);
	test.move(7,5);
	test.move(0,5);
	test.move(1,1);
	test.move(6,1);
	test.move(1,2);
	test.move(6,2);
	test.move(1,3);
	test.move(6,3);
	test.move(1,4);
	test.move(6,4);
	test.move(1,5);
	**/
	
	//test down diagonal
	/**
	test.move(0,0);
	test.move(0,1);
	test.move(0,2);
	test.move(0,3);
	test.move(0,4);
	test.move(0,5);
	test.move(1,1);
	test.move(1,2);
	test.move(1,3);
	test.move(1,4);
	test.move(2,2);
	test.move(2,3);
	test.move(2,4);	
	test.move(1,5);
	test.move(3,3);
	test.move(3,4);
	test.move(4,4);
	**/
	
	//test up diagonal (with illegal moves)
	/**
		test.move(0,7);
	test.move(7,0);
		test.move(1,6);
	test.move(7,1);
		test.move(2,5);
	test.move(7,2);
		test.move(3,4);
	test.move(7,3);
		test.move(4,3);
	**/	
	
	//show board
	for(int i = 0; i < 64; ++i)
	{
		cout << test->board[i];
		if (i%8 == 7)
			cout <<endl;
	}
}
