#include "Game.h"
#include "MainMenuState.h"
#include "NewGameState.h" 
#include "GamePlay.h"
#include "TwoPlayerState.h"
#include<sfml/Graphics.hpp>
#include<sfml/Audio.hpp>
#include<sfml/Network.hpp>
#include<sfml/Window.hpp>
#include<sfml/System.hpp>
//#include <filesystem>
#include <iostream>

// (Lấy hằng số kích thước cửa sổ từ MainMenuState.cpp)


Game::Game()
// Khởi tạo window với kích thước đã định
    : window(sf::VideoMode::getDesktopMode(), "Caro Game OOP", sf::State::Fullscreen)
{
    
    this->window.setFramerateLimit(60);

    // Tải font MỘT LẦN
    if (!this->font.openFromFile("Assets/Font/Silkscreen.ttf")) {
        std::cout << "Error: Khong tim thay font silkscreen.ttf" << std::endl;
        // Bạn nên throw exception hoặc xử lý lỗi ở đây
    }

    // Bắt đầu game ở Main Menu
    this->currentStateEnum = GameState::MainMenu;
    // Tạo đối tượng MainMenuState đầu tiên
    this->currentState = std::make_unique<MainMenuState>(this->window, this->font);
}

void Game::run() {
  
    while (this->window.isOpen()) {
        this->processEvents();
        this->update();
        this->render();

       
        GameState next = this->currentState->getNextState();

        if (next != this->currentStateEnum) {
            this->changeState(next);
        }
    }
}

// Hàm chuyển trang
void Game::changeState(GameState newState) {
    this->currentStateEnum = newState;  

    switch (this->currentStateEnum) {

    case GameState::MainMenu:
        this->currentState = std::make_unique<MainMenuState>(this->window, this->font);
        break;

    case GameState::NewGame:
        this->currentState = std::make_unique<NewGameState>(this->window, this->font);
        break;

    case GameState::Exiting:
        this->window.close();
        break;

    case GameState::TwoPlayer:
        this->currentState = std::make_unique<TwoPlayerState>(this->window, this->font);
        break;

    case GameState::Playing:
        this->currentState = std::make_unique<Gameplay>(this->window, this->font);
        break;
    }
}

void Game::processEvents() {
    while (const auto event = this->window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->window.close();
        }

        // Giao sự kiện cho trang hiện tại xử lý
        this->currentState->handleEvent(*event);
    }
}
// Trong Game::processEvents


void Game::update() {
    sf::Vector2f mousePos = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
 
    this->currentState->update(mousePos);
}

void Game::render() {
    this->window.clear();

    this->currentState->render(this->window);

    this->window.display();
}