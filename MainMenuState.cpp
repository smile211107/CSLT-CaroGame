#include "MainMenuState.h"
#include "GameState.h"
#include "Button.h"
#include "NewGameState.h" 
#include "State.h"
#include <iostream>

// 1. XÓA các hằng số hard-coded (CENTER_X, START_Y)
const sf::Vector2f BUTTON_SIZE = { 400.0F, 60.f };
const float GAP = 90.0f;

MainMenuState::MainMenuState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),


    // 2. TÍNH TOÁN VỊ TRÍ ĐỘNG (DÙNG window.getSize())
    buttonNewGame("New Game", font, BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 0) }),
    buttonLoadGame("Load Game", font, BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 1) }),
    buttonTutorials("Tutorials", font, BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 2) }),
    buttonAboutUs("About Us", font, BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 3) }),
    buttonSettings("Settings", font, BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 4) }),
    buttonExit("Exit", font, BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.5f + (GAP * 5) })


{
    this->menuButtons.push_back(&this->buttonNewGame);
    this->menuButtons.push_back(&this->buttonLoadGame);
    this->menuButtons.push_back(&this->buttonTutorials);
    this->menuButtons.push_back(&this->buttonAboutUs);
    this->menuButtons.push_back(&this->buttonSettings);
    this->menuButtons.push_back(&this->buttonExit);
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

            Button* currentButton = menuButtons[selectedButtonIndex];

          
            if (currentButton == &this->buttonNewGame) {
                this->nextState = GameState::NewGame;
            }
            else if (currentButton == &this->buttonExit) {
                this->nextState = GameState::Exiting;
            }
            else if (currentButton == &this->buttonAboutUs) {
                this->nextState = GameState::AboutUs;
            }
            else if (currentButton == &this->buttonTutorials) {
                this->nextState = GameState::Tutorials;
            }
            else if (currentButton == &this->buttonLoadGame) {
                this->nextState = GameState::LoadGame;
            }

        }


        if (prevIndex != this->selectedButtonIndex) {
            this->menuButtons[prevIndex]->setSelected(false);
            this->menuButtons[this->selectedButtonIndex]->setSelected(true);
        }
    }
}

void MainMenuState::update(sf::Vector2f mousePos) {
    this->buttonNewGame.update(mousePos);
    this->buttonLoadGame.update(mousePos);
    this->buttonTutorials.update(mousePos);
    this->buttonAboutUs.update(mousePos);
    this->buttonSettings.update(mousePos);
    this->buttonExit.update(mousePos);
}

void MainMenuState::render(sf::RenderTarget& target) {

    target.draw(*(this->menuBackgroundSprite));

    this->buttonNewGame.render(target);
    this->buttonLoadGame.render(target);
    this->buttonTutorials.render(target);
    this->buttonAboutUs.render(target);
    this->buttonSettings.render(target);
    this->buttonExit.render(target);
}