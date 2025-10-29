#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
using namespace sf;

class createWindow {
public:
	RenderWindow& window;
	createWindow();
	unsigned int width, height;
};

#endif
