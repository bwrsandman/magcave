#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "minimax.h"
#include <pthread.h>

const unsigned char WIN_BY_HORIZONTAL = 0x1;
const unsigned char WIN_BY_VERTICAL = 0x2;
const unsigned char WIN_BY_FDIAGONAL = 0x3;
const unsigned char WIN_BY_BDIAGONAL = 0x4;
const unsigned char mults[4] = {1, 8, 7, 9};

class GameInfo
{	
private:
	unsigned char getposition(unsigned char x, unsigned char y) const {return x + 8 * y;}
	signed char avail_positions[16];
	unsigned char board[64];
	unsigned char player_no:2;
public:
    GameInfo();
    ~GameInfo(void);
    const unsigned char get_board_at(unsigned char i)const {return board[i];}
	const unsigned char get_player_no() const     {return player_no;}
	bool move(unsigned char, unsigned char, bool);
	bool move(unsigned char p, bool b){return move(p % 8, p / 8, b);}
	unsigned char checkwin(unsigned char, unsigned char) const;
	bool check_stalemate(void) const;
	const unsigned char *get_board(void) const{return board;}
	const int get_best_move(bool) const;
};

class LineChecker
{
public:
	const unsigned char * const board;
	const unsigned char pos:6;					/* Both pos and mul make 1 byte together */
	const unsigned char mul:2;
	const unsigned char player:2;
	LineChecker(const unsigned char * const, const unsigned char p, const unsigned char m, const unsigned char);
};

void* checkline(void*);
unsigned char check_win(unsigned char, const unsigned char *, const unsigned char);
MinimaxNode * build_minimax_tree(const unsigned char * const, const signed char, unsigned char);

#endif
