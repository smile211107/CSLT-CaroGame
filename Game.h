#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "GamePlay.h"
#include "State.h"

#include <memory> // dung de khai bao con tro  unique_ptr
extern int gameMode;
extern bool requestMenuMusic;
class Game {
public:
    Game();
    void run(); // chay vong lap game chinh

private:
    void processEvents();
    void update();
    void render();


    // func dung de chuyen sang trang thai game khac
    void changeState(GameState newState);

    sf::RenderWindow window;
    sf::Font font;
    sf::Music mainMenuMusic;
    GameState currentStateEnum;
    std::unique_ptr<State> currentState;
};