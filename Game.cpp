#include "Game.h"
#include "MainMenuState.h"
#include "NewGameState.h" 
#include "LoadGameState.h" 
#include "GamePlay.h"
#include "TwoPlayerState.h"
#include "AboutState.h"
#include "ThreePlayerState.h"
#include "TutorialState.h"
#include "SettingsState.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
// #include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include "SettingsState.h"


#include<SFML/System.hpp>
#include <iostream>
#include <memory>
bool requestMenuMusic = false;
int gameMode = 0;
Game::Game()
    : window(sf::VideoMode({1920 ,1080}), "Caro Game OOP", sf::State::Fullscreen)
    // : window(sf::VideoMode::getDesktopMode(), "Caro Game OOP", sf::State::Default)
    // : window(sf::VideoMode::getDesktopMode(), "Caro Game OOP", sf::State::Fullscreen)
 
{

    this->window.setFramerateLimit(120);

 
    if (!this->font.openFromFile("Assets/Font/Baloo.ttf")) {
        std::cout << "Error: Khong tim thay font Baloo.ttf" << std::endl;
       
    }
    if (!mainMenuMusic.openFromFile("assets/audio/mainMenuAudio.mp3")) {

        cout << "khong tai duoc am thanh";
    }
    this->currentStateEnum = GameState::MainMenu;
  
    this->currentState = std::make_unique<MainMenuState>(this->window, this->font);
    mainMenuMusic.setLooping(true);
    mainMenuMusic.setVolume(g_musicOn*50);
    mainMenuMusic.play();
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
        static GameState prevState = GameState::MainMenu;

        if (prevState == GameState::Settings && this->currentStateEnum != GameState::Settings) {
            // vừa thoát SettingsState
            mainMenuMusic.setVolume(g_musicOn*50);

        }

        prevState = this->currentStateEnum;

    }
}

void Game::changeState(GameState newState) {
    this->currentStateEnum = newState;

    switch (this->currentStateEnum) {

    case GameState::MainMenu:
        this->currentState = std::make_unique<MainMenuState>(this->window, this->font);
        // Bật nhạc menu nếu g_musicOn = true và nhạc chưa phát
        mainMenuMusic.setVolume(g_musicOn*50);
        break;

    case GameState::NewGame:
        this->currentState = std::make_unique<NewGameState>(this->window, this->font);
        if (g_musicOn)
            mainMenuMusic.setVolume(g_musicOn*50);
        break;

    case GameState::Exiting:
        this->window.close();
        break;

    case GameState::Settings:
        this->currentState = std::make_unique<SettingsState>(this->window, this->font);
        break;

    case GameState::TwoPlayer:
        this->currentState = std::make_unique<TwoPlayerState>(this->window, this->font);

        break;

    case GameState::Playing:
        mainMenuMusic.stop();
        this->currentState = std::make_unique<Gameplay>(this->window, this->font);
        break;

    case GameState::ThreePlayer:
        this->currentState = std::make_unique<ThreePlayerState>(this->window, this->font);
        break;

    case GameState::AboutUs:
        this->currentState = std::make_unique<AboutState>(this->window, this->font);
        break;

    case GameState::LoadGame:
        this->currentState = std::make_unique<LoadGameState>(this->window, this->font);
        mainMenuMusic.setVolume(g_musicOn*50);
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