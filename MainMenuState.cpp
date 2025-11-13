#include "MainMenuState.h"
#include "GameState.h"
#include "Button.h"
#include "NewGameState.h" 
#include "SettingsState.h"
#include "State.h"
#include <iostream>

// 1. XÓA các hằng số hard-coded (CENTER_X, START_Y)
const sf::Vector2f BUTTON_SIZE = { 400.0F, 60.f };
const float GAP = 90.0f;

MainMenuState::MainMenuState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font)


    // 2. TÍNH TOÁN VỊ TRÍ ĐỘNG (DÙNG window.getSize())
    /*buttonNewGame(buttonNewGameTexture, { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 0) }),
    buttonLoadGame(buttonLoadGameTexture, { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 1) }),
    buttonTutorials(buttonTutorialsTexture, { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 2) }),
    buttonAboutUs(buttonAboutUsTexture, { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 3) }),
    buttonSettings(buttonSettingsTexture, { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 4) }),
    buttonExit(buttonExitTexture, { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 5) })*/


{
    //this->buttonNewGameTexture = std::make_unique<sf::Texture>();
    if (!buttonNewGameTexture.loadFromFile("Assets/image/vn/newGame-button.png")) {
        std::cout << "khong the mo newgametexture" << '\n';
    }
    //this->buttonLoadGameTexture = std::make_unique<sf::Texture>();
    if (!buttonLoadGameTexture.loadFromFile("Assets/image/vn/loadGame-button.png")) {

    }
    //this->buttonTutorialsTexture = std::make_unique<sf::Texture>();
    if (!buttonTutorialsTexture.loadFromFile("Assets/image/vn/tutorial-button.png")) {

    }
    //this->buttonAboutUsTexture = std::make_unique<sf::Texture>();
    if (!buttonAboutUsTexture.loadFromFile("Assets/image/vn/aboutUs-button.png")) {

    }
    //this->buttonSettingsTexture = std::make_unique<sf::Texture>();
    if (!buttonSettingsTexture.loadFromFile("Assets/image/vn/settings-button.png")) {

    }
    //this->buttonExitTexture = std::make_unique<sf::Texture>();
    if (!buttonExitTexture.loadFromFile("Assets/image/vn/exit-button.png")) {

    }
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

    this->menuButtons.push_back(move(buttonNewGame));
    this->menuButtons.push_back(move(buttonLoadGame));
    this->menuButtons.push_back(move(buttonTutorials));
    this->menuButtons.push_back(move(buttonAboutUs));
    this->menuButtons.push_back(move(buttonSettings));
    this->menuButtons.push_back(move(buttonExit));
    this->selectedButtonIndex = 0;
    this->menuButtons[this->selectedButtonIndex]->setSelected(true);
    this->nextState = GameState::MainMenu;
    this->menuBackgroundTexture = std::make_unique<sf::Texture>();

    
    if (!this->menuBackgroundTexture->loadFromFile("Assets/Image/menu-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    this->menuBackgroundSprite = std::make_unique<sf::Sprite>(*(this->menuBackgroundTexture));

    sf::Vector2f backgroundScale(
        static_cast<float>(this->window.getSize().x) / this->menuBackgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->menuBackgroundTexture->getSize().y
    );
    this->menuBackgroundSprite->setScale(backgroundScale);

}

GameState MainMenuState::getNextState() {
    return this->nextState;
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {

        int prevIndex = this->selectedButtonIndex;

        if (key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) {
       
            selectedButtonIndex = (selectedButtonIndex - 1 + menuButtons.size()) % menuButtons.size();
        }
        else if (key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) {
         
            selectedButtonIndex = (selectedButtonIndex + 1) % menuButtons.size();

        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {

            //auto& currentButton = menuButtons[selectedButtonIndex];

            /*if (currentButton == buttonNewGame) {
                this->nextState = GameState::NewGame;
            }
            else if (currentButton == buttonExit) {
                this->nextState = GameState::Exiting;
            }
            else if (currentButton == buttonAboutUs) {
                this->nextState = GameState::AboutUs;
            }
            else if (currentButton == buttonTutorials) {
                this->nextState = GameState::Tutorials;
            }
            else if (currentButton == buttonLoadGame) {
                this->nextState = GameState::LoadGame;
            }
            else if (currentButton == buttonSettings) {
                this->nextState = GameState::Settings;
            }*/

            if (selectedButtonIndex == 0) {
                this->nextState = GameState::NewGame;
            }
            else if (selectedButtonIndex == 1) {
                this->nextState = GameState::LoadGame;
            }
            else if (selectedButtonIndex == 2) {
                this->nextState = GameState::Tutorials;
            }
            else if (selectedButtonIndex == 3) {
                this->nextState = GameState::AboutUs;
            }
            else if (selectedButtonIndex == 4) {
                this->nextState = GameState::Settings;
            }
            else if (selectedButtonIndex == 5) {
                this->nextState = GameState::Exiting;
            }


        }


        if (prevIndex != this->selectedButtonIndex) {
            this->menuButtons[prevIndex]->setSelected(false);
            this->menuButtons[this->selectedButtonIndex]->setSelected(true);
        }
    }
}

void MainMenuState::update(sf::Vector2f mousePos) {
    /*this->buttonNewGame->update(mousePos);
    this->buttonLoadGame->update(mousePos);
    this->buttonTutorials->update(mousePos);
    this->buttonAboutUs->update(mousePos);
    this->buttonSettings->update(mousePos);
    this->buttonExit->update(mousePos);*/
    for (auto& button : menuButtons) {
        if (button != nullptr) button->update(mousePos);
    }
}

void MainMenuState::render(sf::RenderTarget& target) {

    target.draw(*(this->menuBackgroundSprite));

    /*this->buttonNewGame->render(target);
    this->buttonLoadGame->render(target);
    this->buttonTutorials->render(target);
    this->buttonAboutUs->render(target);
    this->buttonSettings->render(target);
    this->buttonExit->render(target);*/
    for (auto& button : menuButtons) {
        if (button != nullptr) button->render(target);
    }
}