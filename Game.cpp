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
#include "SaveState.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
// #include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include "SettingsState.h"


#include<SFML/System.hpp>
#include <iostream>
#include <memory>
bool requestMenuMusic = false;

int gameMode = 2;
GameState previousState = GameState::MainMenu;
Game::Game()
    : window(sf::VideoMode({1920 ,1080}), "Caro Game OOP", sf::State::Fullscreen)
    // : window(sf::VideoMode::getDesktopMode(), "Caro Game OOP", sf::State::Default)
    // : window(sf::VideoMode::getDesktopMode(), "Caro Game OOP", sf::State::Fullscreen)
 
{

    window.setFramerateLimit(120);

 
    if (!font.openFromFile("Assets/Font/Baloo.ttf")) {
        std::cout << "Error: Khong tim thay font Baloo.ttf" << std::endl;
       
    }
    if (!mainMenuMusic.openFromFile("assets/audio/mainMenuAudio.mp3")) {

        cout << "khong tai duoc am thanh";
    }
    currentStateEnum = GameState::MainMenu;
  
    currentState = std::make_unique<MainMenuState>(window, font);
    mainMenuMusic.setLooping(true);
    mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
    mainMenuMusic.play();
}

void Game::run() {

    while (window.isOpen()) {
        processEvents();
        update();
        render();


        GameState next = currentState->getNextState();

        if (next != currentStateEnum) {
            changeState(next);
        }
        static GameState prevState = GameState::MainMenu;

        if (prevState == GameState::Settings && currentStateEnum != GameState::Settings) {
            // vừa thoát SettingsState
            /*if (g_musicOn)
                mainMenuMusic.play();
            else
                mainMenuMusic.stop();*/
            mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        }

        prevState = currentStateEnum;

    }
}

void Game::changeState(GameState newState) {
    currentStateEnum = newState;

    switch (currentStateEnum) {

    case GameState::MainMenu:
        currentState = std::make_unique<MainMenuState>(window, font);
        // Bật nhạc menu nếu g_musicOn = true và nhạc chưa phát
        
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        break;

    case GameState::NewGame:
        currentState = std::make_unique<NewGameState>(window, font);
      
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        break;

    case GameState::Exiting:
        window.close();
        break;

    case GameState::Settings:
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        currentState = std::make_unique<SettingsState>(window, font);
        break;

    case GameState::TwoPlayer:
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        currentState = std::make_unique<TwoPlayerState>(window, font);

        break;

    case GameState::Playing:
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 0);
        currentState = std::make_unique<Gameplay>(window, font);
        break;

    case GameState::ThreePlayer:
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        currentState = std::make_unique<ThreePlayerState>(window, font);
        break;

    case GameState::AboutUs:
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        currentState = std::make_unique<AboutState>(window, font);
        break;

    case GameState::LoadGame:
        currentState = std::make_unique<LoadState>(window, font);
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        break;

    case GameState::Tutorials:
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        currentState = std::make_unique<TutorialState>(window, font);
        break;
    case GameState::Saving:
        mainMenuMusic.setVolume(static_cast<float>(g_musicOn) * 50);
        currentState = std::make_unique<SaveState>(window, font);
        break;
    }
}



void Game::processEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        // giao event cho trang hien tai xu li
        currentState->handleEvent(*event);
    }
}



void Game::update() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    currentState->update(mousePos);
}

void Game::render() {
    window.clear();

    currentState->render(window);

    window.display();
}