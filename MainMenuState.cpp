#include "MainMenuState.h"
#include "GameState.h"
#include "GamePlay.h"
#include "Button.h"
#include "NewGameState.h" 
#include "SettingsState.h"
#include "State.h"
#include <iostream>

const sf::Vector2f BUTTON_SIZE = { 400.0F, 60.f };
const float GAP = 90.0f;

MainMenuState::MainMenuState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font)


  

{
    //buttonNewGameTexture = std::make_unique<sf::Texture>();
    if (!buttonNewGameTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/newGame-button.png")) {
        std::cout << "khong the mo newgametexture" << '\n';
    }
    //buttonLoadGameTexture = std::make_unique<sf::Texture>();
    if (!buttonLoadGameTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/loadGame-button.png")) {

    }
    //buttonTutorialsTexture = std::make_unique<sf::Texture>();
    if (!buttonTutorialsTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/tutorial-button.png")) {

    }
    //buttonAboutUsTexture = std::make_unique<sf::Texture>();
    if (!buttonAboutUsTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/aboutUs-button.png")) {

    }
    //buttonSettingsTexture = std::make_unique<sf::Texture>();
    if (!buttonSettingsTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/settings-button.png")) {

    }
    //buttonExitTexture = std::make_unique<sf::Texture>();
    if (!buttonExitTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/exit-button.png")) {

    }
    track.clear();
    buttonNewGame = std::make_unique<Button>(buttonNewGameTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 0)));
    buttonLoadGame = std::make_unique<Button>(buttonLoadGameTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 1)));
    buttonTutorials = std::make_unique<Button>(buttonTutorialsTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 2)));
    buttonAboutUs = std::make_unique<Button>(buttonAboutUsTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 3)));
    buttonSettings = std::make_unique<Button>(buttonSettingsTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 4)));
    buttonExit = std::make_unique<Button>(buttonExitTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 5)));
    menuButtons.push_back(move(buttonNewGame));
    menuButtons.push_back(move(buttonLoadGame));
    menuButtons.push_back(move(buttonTutorials));
    menuButtons.push_back(move(buttonAboutUs));
    menuButtons.push_back(move(buttonSettings));
    menuButtons.push_back(move(buttonExit));
    selectedButtonIndex = 0;
    menuButtons[selectedButtonIndex]->setSelected(true);
    nextState = GameState::MainMenu;
    menuBackgroundTexture = std::make_unique<sf::Texture>();

    
    if (!menuBackgroundTexture->loadFromFile("Assets/Image/menu-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    menuBackgroundSprite = std::make_unique<sf::Sprite>(*(menuBackgroundTexture));

    sf::Vector2f backgroundScale(
        static_cast<float>(window.getSize().x) / menuBackgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / menuBackgroundTexture->getSize().y
    );
    menuBackgroundSprite->setScale(backgroundScale);

}

GameState MainMenuState::getNextState() {
    return nextState;
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

            if (menuButtons[0]->isMouseOver(mousePos)) {
                nextState = GameState::NewGame;

            }
            if (menuButtons[1]->isMouseOver(mousePos)) {
                nextState = GameState::LoadGame;

            }
            if (menuButtons[2]->isMouseOver(mousePos)) {

                nextState = GameState::Tutorials;
            }
            if (menuButtons[3]->isMouseOver(mousePos)) {

                nextState = GameState::AboutUs;
            }
            if (menuButtons[4]->isMouseOver(mousePos)) {

                nextState = GameState::Settings;
            }
            if (menuButtons[5]->isMouseOver(mousePos)) {

                nextState = GameState::Exiting;
            }
        }
    }
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {

        int prevIndex = selectedButtonIndex;

        if (key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) {
       
            selectedButtonIndex = (selectedButtonIndex - 1 + static_cast<int>(menuButtons.size())) % static_cast<int>(menuButtons.size());
        }
        else if (key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) {
         
            selectedButtonIndex = (selectedButtonIndex + 1) % static_cast<int>(menuButtons.size());

        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {

            

            if (selectedButtonIndex == 0) {
                nextState = GameState::NewGame;
            }
            else if (selectedButtonIndex == 1) {
                nextState = GameState::LoadGame;
            }
            else if (selectedButtonIndex == 2) {
                nextState = GameState::Tutorials;
            }
            else if (selectedButtonIndex == 3) {
                nextState = GameState::AboutUs;
            }
            else if (selectedButtonIndex == 4) {
                nextState = GameState::Settings;
            }
            else if (selectedButtonIndex == 5) {
                nextState = GameState::Exiting;
            }


        }


        if (prevIndex != selectedButtonIndex) {
            menuButtons[prevIndex]->setSelected(false);
            menuButtons[selectedButtonIndex]->setSelected(true);
        }
    }
}

void MainMenuState::update(sf::Vector2f mousePos) {
   
    for (auto& button : menuButtons) {
        if (button != nullptr) button->update(mousePos);
    }
}

void MainMenuState::render(sf::RenderTarget& target) {

    target.draw(*(menuBackgroundSprite));

   
    for (auto& button : menuButtons) {
        if (button != nullptr) button->render(target);
    }
}
