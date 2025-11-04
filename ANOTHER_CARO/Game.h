#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "State.h"
#include <memory> // Dùng cho con trỏ thông minh unique_ptr

class Game {
public:
    Game();
    void run(); // Vòng lặp game chính

private:
    void processEvents();
    void update();
    void render();

    // Hàm chuyển trang
    void changeState(GameState newState);

    sf::RenderWindow window;
    sf::Font font;

    GameState currentStateEnum;
    std::unique_ptr<State> currentState; 
};