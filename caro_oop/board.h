#pragma once
#ifndef BOARD_H
#define BOARD_H

class Board {
public:
	int score;
	

};
extern unsigned char (mainGameBoard[13][13]);
int checkWin(int y, int x, int checkNum);

#endif
