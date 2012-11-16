const char WIN_BY_HORIZONTAL = 0x1;
const char WIN_BY_VERTICAL = 0x2;
const char WIN_BY_FDIAGONAL = 0x3;
const char WIN_BY_BDIAGONAL = 0x4;

class GameInfo
{	
private:
	int getposition(int x, int y) const {return x + 8 * y;}
	char avail_positions[16];
	char board[64];
	unsigned char player_no;
	bool checkline(int, int) const;
public:
    GameInfo();
    ~GameInfo(void);
	const char get_board_at(int i)const {return board[i];}
	bool move(int, int, bool);
	char checkwin(int, int) const;
	bool check_stalemate(void) const;
};
