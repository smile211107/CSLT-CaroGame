#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	int x, y, turn = 1, playerNum, playerResult;
	Player();
	void setPlayerNum(int num) {
		playerNum = num;
	}
};

#endif