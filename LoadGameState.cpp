#include "LoadGameState.h"
#include "Button.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem> 
#include <fstream>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;
const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };


LoadGameState::LoadGameState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font)



{
    if (!buttonBackTexture.loadFromFile("Assets/image/vn/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.95f));

    this->nextState = GameState::LoadGame;
    cout << "Da vao trang load game!" << std::endl;
    this->backgroundTexture = std::make_unique<sf::Texture>();


    if (!this->backgroundTexture->loadFromFile("Assets/image/vn/loadGame-background.png")) {
        cout << "khong the mo loadgame background" << '\n';
    }

    this->backgroundSprite = std::make_unique<sf::Sprite>(*(this->backgroundTexture));


    sf::Vector2f backgroundScale(
        static_cast<float>(this->window.getSize().x) / this->backgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->backgroundTexture->getSize().y
    );
    this->backgroundSprite->setScale(backgroundScale);

   
}

GameState LoadGameState::getNextState() {
    return this->nextState;
}

void LoadGameState::handleEvent(const sf::Event& event) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

            if (this->buttonBack->isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                this->nextState = GameState::MainMenu;
            }
        }
    }
}

void LoadGameState::update(sf::Vector2f mousePos) {
    this->buttonBack->update(mousePos);
}

void LoadGameState::render(sf::RenderTarget& target) {
    target.draw(*(this->backgroundSprite));
    this->buttonBack->render(target);
}