#include "AboutState.h"
#include <iostream>

const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };

AboutState::AboutState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),

    // 2. TÍNH TOÁN VỊ TRÍ ĐỘNG
    buttonBack("Back", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.92f })
{
    this->nextState = GameState::AboutUs;
    std::cout << "Da vao trang AboutUs!" << std::endl;
    this->backgroundTexture = std::make_unique<sf::Texture>();

    // 2. Tải file (dùng -> thay vì .)
    if (!this->backgroundTexture->loadFromFile("assets/image/about-background-vn.png")) {
        std::cout << "khong the mo Aboutbackground" << '\n';
    }

    this->backgroundSprite = std::make_unique<sf::Sprite>(*(this->backgroundTexture));


    sf::Vector2f backgroundScale(
        static_cast<float>(this->window.getSize().x) / this->backgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->backgroundTexture->getSize().y
    );
    this->backgroundSprite->setScale(backgroundScale);
}

GameState AboutState::getNextState() {
    return this->nextState;
}

void AboutState::handleEvent(const sf::Event& event) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

            if (this->buttonBack.isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                this->nextState = GameState::MainMenu;
            }
        }
    }
}

void AboutState::update(sf::Vector2f mousePos) {
    this->buttonBack.update(mousePos);
}

void AboutState::render(sf::RenderTarget& target) {
    target.draw(*(this->backgroundSprite));
    this->buttonBack.render(target);
}