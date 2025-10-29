#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <conio.h>
using namespace sf;

class Game {
public:
	RenderWindow gameWindow;
Game();
};
#endif;