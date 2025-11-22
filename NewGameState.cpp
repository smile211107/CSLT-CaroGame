#include "NewGameState.h"
#include "SettingsState.h"
#include <iostream>
#include <memory>
const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };

NewGameState::NewGameState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),

    buttonTwoPlayer("Two Players", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x * 0.35f, window.getSize().y * 0.7f }),
    buttonThreePlayer("Three Players", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x * 0.65f, window.getSize().y * 0.7f }),
    buttonBack("Back", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.8f })
{
    this->menuButtons.push_back(&this->buttonTwoPlayer);
    this->menuButtons.push_back(&this->buttonThreePlayer);
    this->menuButtons.push_back(&this->buttonBack);
    this->selectedButtonIndex = 0;
    this->menuButtons[this->selectedButtonIndex]->setSelected(true);

    this->nextState = GameState::NewGame;
    this->backgroundTexture = std::make_unique<sf::Texture>();


    if (!this->backgroundTexture->loadFromFile("assets/image/"+ngonngu[g_language]+"/selectMode-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    this->backgroundSprite = std::make_unique<sf::Sprite>(*(this->backgroundTexture));


    sf::Vector2f backgroundScale(
        static_cast<float>(this->window.getSize().x) / this->backgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->backgroundTexture->getSize().y
    );
    this->backgroundSprite->setScale(backgroundScale);
}

GameState NewGameState::getNextState() {
    return this->nextState;
}

void NewGameState::handleEvent(const sf::Event& event) {
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {

        int prevIndex = this->selectedButtonIndex;

        if (key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) {
           
            this->selectedButtonIndex = (this->selectedButtonIndex - 1 + this->menuButtons.size()) % this->menuButtons.size();
        }
        else if (key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) {
        
            this->selectedButtonIndex = (this->selectedButtonIndex + 1) % this->menuButtons.size();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {
        
            Button* currentButton = this->menuButtons[this->selectedButtonIndex];

            if (currentButton == &this->buttonTwoPlayer) {
                this->nextState = GameState::TwoPlayer;
            }
            else if (currentButton == &this->buttonThreePlayer) {
                this->nextState = GameState::ThreePlayer;
            }
            else if (currentButton == &this->buttonBack) {
                this->nextState = GameState::MainMenu;
            }

        }

        if (prevIndex != this->selectedButtonIndex) {
            this->menuButtons[prevIndex]->setSelected(false);
            this->menuButtons[this->selectedButtonIndex]->setSelected(true);
        }
    }
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

            if (this->buttonTwoPlayer.isMouseOver(mousePos)) {
                this->nextState = GameState::TwoPlayer;
                std::cout << "Bat dau game 2 nguoi!" << std::endl;
            }
            if (this->buttonThreePlayer.isMouseOver(mousePos)) {
                std::cout << "Bat dau game 3 nguoi!" << std::endl;
            }
            if (this->buttonBack.isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                this->nextState = GameState::MainMenu;
            }
        }
    }
}

void NewGameState::update(sf::Vector2f mousePos) {
    this->buttonTwoPlayer.update(mousePos);
    this->buttonThreePlayer.update(mousePos);
    this->buttonBack.update(mousePos);
}

void NewGameState::render(sf::RenderTarget& target) {
    target.draw(*(this->backgroundSprite));
    this->buttonTwoPlayer.render(target);
    this->buttonThreePlayer.render(target);
    this->buttonBack.render(target);
}