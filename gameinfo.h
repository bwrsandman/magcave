#include <iostream>
#include <utility>
#include <string>
using namespace std;

class GameInfo
{	
	int getposition(int x, int y) const {return x + 8 * y;}
	char avail_positions[16];
	char board[64];
	char player_no;
public:
    GameInfo();
    ~GameInfo(void);
	const char get_board_at(int i)const {return board[i];}
	bool move(int, int, bool);
	bool checkwin(int, int) const;
	bool check_stalemate(void) const;
};
