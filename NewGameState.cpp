#include "NewGameState.h"
#include <iostream>
#include <memory>
const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };

NewGameState::NewGameState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font)

  
{
    if (!buttonTwoPlayerTexture.loadFromFile("Assets/image/vn/2players-button.png")) {
        std::cout << "khong the mo 2playersbutton" << '\n';
    }
    buttonTwoPlayer = std::make_unique<Button>(buttonTwoPlayerTexture,
        sf::Vector2f(window.getSize().x * 0.35f, window.getSize().y * 0.7f));

    if (!buttonThreePlayerTexture.loadFromFile("Assets/image/vn/3players-button.png")) {
        std::cout << "khong the mo 3players" << '\n';
    }
    buttonThreePlayer = std::make_unique<Button>(buttonThreePlayerTexture,
        sf::Vector2f(window.getSize().x * 0.65f, window.getSize().y * 0.7f));

    if (!buttonBackTexture.loadFromFile("Assets/image/vn/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.8f));

    this->menuButtons.push_back(move(buttonTwoPlayer));
    this->menuButtons.push_back(move(buttonThreePlayer));
    this->menuButtons.push_back(move(buttonBack));
    this->selectedButtonIndex = 0;
    this->menuButtons[this->selectedButtonIndex]->setSelected(true);

    this->nextState = GameState::NewGame;
    this->backgroundTexture = std::make_unique<sf::Texture>();


    if (!this->backgroundTexture->loadFromFile("assets/image/vn/selectMode-background.png")) {
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
        
            /*auto& currentButton = this->menuButtons[this->selectedButtonIndex];

            if (currentButton == buttonTwoPlayer) {
                this->nextState = GameState::TwoPlayer;
            }
            else if (currentButton == buttonThreePlayer) {
                this->nextState = GameState::ThreePlayer;
            }
            else if (currentButton == buttonBack) {
                this->nextState = GameState::MainMenu;
            }*/
            if (selectedButtonIndex == 0) {
                this->nextState = GameState::TwoPlayer;
            }
            else if (selectedButtonIndex == 1) {
                this->nextState = GameState::ThreePlayer;
            }
            else if (selectedButtonIndex == 2) {
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

            if (this->buttonTwoPlayer->isMouseOver(mousePos)) {
                this->nextState = GameState::TwoPlayer;
                std::cout << "Bat dau game 2 nguoi!" << std::endl;
            }
            if (this->buttonThreePlayer->isMouseOver(mousePos)) {
                std::cout << "Bat dau game 3 nguoi!" << std::endl;
            }
            if (this->buttonBack->isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                this->nextState = GameState::MainMenu;
            }
        }
    }
}

void NewGameState::update(sf::Vector2f mousePos) {
    /*this->buttonTwoPlayer->update(mousePos);
    this->buttonThreePlayer->update(mousePos);
    this->buttonBack->update(mousePos);*/
    for (auto& button : menuButtons) {
        if (button != nullptr) button->update(mousePos);
    }
}

void NewGameState::render(sf::RenderTarget& target) {
    target.draw(*(this->backgroundSprite));
    /*this->buttonTwoPlayer->render(target);
    this->buttonThreePlayer->render(target);
    this->buttonBack->render(target);*/
    for (auto& button : menuButtons) {
        if (button != nullptr) button->render(target);
    }
}