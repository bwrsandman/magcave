#ifndef GAMEINFO_H
#define GAMEINFO_H

const char WIN_BY_HORIZONTAL = 0x1;
const char WIN_BY_VERTICAL = 0x2;
const char WIN_BY_FDIAGONAL = 0x3;
const char WIN_BY_BDIAGONAL = 0x4;

class GameInfo
{	
private:
	unsigned char getposition(unsigned char x, unsigned char y) const {return x + 8 * y;}
	signed char avail_positions[16];
	unsigned char board[64];
	unsigned char player_no;
public:
    GameInfo();
    ~GameInfo(void);
    const unsigned char get_board_at(unsigned char i)const {return board[i];}
	const unsigned char get_player_no() const     {return player_no;}
	bool move(unsigned char, unsigned char, bool);
	unsigned char checkwin(unsigned char, unsigned char) const;
	bool check_stalemate(void) const;
};

struct line_checker
{
	const GameInfo * const game;
	const unsigned char pos;
	const unsigned char mul;
};

bool* checkline(struct line_checker*);

#endif
