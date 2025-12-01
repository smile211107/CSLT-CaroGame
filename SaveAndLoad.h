#pragma once
#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include "Game.h"
#include "GamePlay.h"
#include "PlayerNameInput.h"
#define PATH "saved/"
using namespace std;
namespace fs = std::filesystem;
/*
File name
Save date
Number of players
Score of each players
Number of turns
Cordinates and value of each turn
*/
void writeFile(string NAME)
{
	time_t now = time(nullptr);
	tm localTime;
	ofstream OUTPUT(PATH + NAME + ".txt");
	if (!OUTPUT)
	{
		cout << "Khong mo duoc file\n";
	}
	OUTPUT << NAME << '\n';
	if (localtime_s(&localTime, &now) == 0) {
		OUTPUT << localTime.tm_hour << ':' << localTime.tm_min << ':' << localTime.tm_sec << ' ' << localTime.tm_mday << '/' << 1 + localTime.tm_mon << '/' << 1900 + localTime.tm_year << '\n';
	}
	else {
		std::cerr << "Error converting time." << std::endl;
	}
	OUTPUT << gameMode << '\n';
	OUTPUT << playerNames[1] << '\n';
	OUTPUT << player1Score;
	OUTPUT << playerNames[2] << '\n';
	OUTPUT << player2Score;
	if (gameMode == 3)
	{
		OUTPUT << playerNames[3] << '\n';
		OUTPUT << player3Score;
	}
	OUTPUT << '\n' << track.size() << '\n';
	for (int i = 0; i < track.size(); i++) OUTPUT << track[i].first.first << ' ' << track[i].first.second << ' ' << track[i].second << '\n';
	OUTPUT.close();
}


void readFile(string NAME)
{
	ifstream INPUT(PATH + NAME + ".txt");
	if (!INPUT) {
		cout << "File khong ton tai!\n";
	}
	string fileName, date;
	int size, y, x, val;
	INPUT >> fileName;
	INPUT >> date;
	INPUT >> gameMode;
	INPUT >> playerNames[1] >> player1Score >> playerNames[2] >> player2Score;
	if (gameMode == 3) INPUT >> playerNames[3] >> player3Score;
	INPUT >> size;
	for (int i = 0; i < size; i++)
	{
		INPUT >> y >> x >> val;
		track.push_back({ {y,x},val });
	}
}


void showFiles()
{
	try {
		for (const auto& entry : fs::directory_iterator(PATH)) {
			std::cout << entry.path() << std::endl; 
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

}


#endif
