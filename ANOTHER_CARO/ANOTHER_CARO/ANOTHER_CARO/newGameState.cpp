#include "NewGameState.h"
#include <iostream>

const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };

NewGameState::NewGameState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),

    // 2. TÍNH TOÁN VỊ TRÍ ĐỘNG
    buttonTwoPlayer("Two Players", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.4f }),
    buttonThreePlayer("Three Players", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.5f }),
    buttonBack("Back", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.7f })
{
    this->nextState = GameState::NewGame;
    std::cout << "Da vao trang New Game (Player Select)!" << std::endl;
    this->backgroundTexture = std::make_unique<sf::Texture>();

    // 2. Tải file (dùng -> thay vì .)
    if (!this->backgroundTexture->loadFromFile("Assets/Image/background.png")) {
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