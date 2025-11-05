#include "Game.h"
#include "MainMenuState.h"
#include "NewGameState.h" 
#include "GamePlay.h"
#include "TwoPlayerState.h"
#include "AboutState.h"
#include "ThreePlayerState.h"
#include "TutorialState.h"
#include<sfml/Graphics.hpp>
#include<sfml/Audio.hpp>
#include<sfml/Network.hpp>
#include<sfml/Window.hpp>
#include<sfml/System.hpp>
#include <iostream>
#include <memory>

int gameMode = 0;
Game::Game()

    : window(sf::VideoMode::getDesktopMode(), "Caro Game OOP", sf::State::Fullscreen)
 
{

    this->window.setFramerateLimit(120);

 
    if (!this->font.openFromFile("Assets/Font/Silkscreen.ttf")) {
        std::cout << "Error: Khong tim thay font silkscreen.ttf" << std::endl;
       
    }

    this->currentStateEnum = GameState::MainMenu;
  
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

    case GameState::ThreePlayer:
        this->currentState = std::make_unique<ThreePlayerState>(this->window, this->font);

        break;
    case GameState::AboutUs:
        this->currentState = std::make_unique<AboutState>(this->window, this->font);

        break;


    case GameState::Tutorials:
        this->currentState = std::make_unique<TutorialState>(this->window, this->font);

        break;
    }

}


void Game::processEvents() {
    while (const auto event = this->window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->window.close();
        }

        // giao event cho trang hien tai xu li
        this->currentState->handleEvent(*event);
    }
}



void Game::update() {
    sf::Vector2f mousePos = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));

    this->currentState->update(mousePos);
}

void Game::render() {
    this->window.clear();

    this->currentState->render(this->window);

    this->window.display();
}