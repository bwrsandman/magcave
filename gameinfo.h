#include <iostream>
#include <utility>
#include <string>
using namespace std;

class GameInfo
{	
	int getposition(int x, int y) const {return x + 8 * y;}
public:
	int avail_positions[16];
	int board[64];
	int player_no;
    GameInfo();
    ~GameInfo(void);
	bool move(int, int);
	bool checkwin(int, int) const;
};
