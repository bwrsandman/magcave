#include "gameinfo.h"

int main(int argc, char * argv[])
{
	GameInfo test;
	
	
	for(int i = 0; i < 16; ++i)
	{
		cout << test.avail_positions[i] << endl;
	}
	
	test.move(0,1);
	test.move(0,2);
	test.move(0,3);
	test.move(0,4);
	test.move(0,5);
	test.move(7,5);
	test.move(7,2);
	
	for(int i = 0; i < 64; ++i)
	{
		cout << test.board[i];
		if (i%8 == 7)
			cout <<endl;
	}
}
