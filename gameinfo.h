#include <iostream>
#include <utility>
#include <string>
using namespace std;

class GameInfo
{	
public:
	int avail_positions[16];
	int board[64];
	int player_no;
    GameInfo();
    ~GameInfo(void);
	void move(int, int);
};