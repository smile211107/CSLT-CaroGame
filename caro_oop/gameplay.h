#pragma once
#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "player.h"
#include "board.h"
#include <iostream>
#include <conio.h>
using namespace std;
using namespace sf;

class Game {
public:
	Game();
	void gamePlay();
private:
	RenderWindow window;
};

#endif