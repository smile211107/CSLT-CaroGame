#include "AboutState.h"
#include "SettingsState.h"
#include "Button.h"
#include <iostream>
using namespace std;
const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };

AboutState::AboutState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font)

{
    if (!buttonBackTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.92f));

    nextState = GameState::AboutUs;
    cout << "Da vao trang AboutUs!" << std::endl;
    backgroundTexture = std::make_unique<sf::Texture>();


    if (!this->backgroundTexture->loadFromFile("Assets/image/" + ngonngu[g_language] + "/about-background.png")) {
        cout << "khong the mo Aboutbackground" << '\n';
    }

    backgroundSprite = std::make_unique<sf::Sprite>(*(backgroundTexture));


    sf::Vector2f backgroundScale(
        static_cast<float>(window.getSize().x) / backgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture->getSize().y
    );
    backgroundSprite->setScale(backgroundScale);
    buttonBack->setSelected(true);
}

GameState AboutState::getNextState() {
    return nextState;
}

void AboutState::handleEvent(const sf::Event& event) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

            if (buttonBack->isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                nextState = GameState::MainMenu;
            }
        }
    }
    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->scancode == sf::Keyboard::Scancode::Enter) {
            nextState = GameState::MainMenu;
        }
    }
}



void AboutState::update(sf::Vector2f mousePos) {
    buttonBack->update(mousePos);
}

void AboutState::render(sf::RenderTarget& target) {
    target.draw(*(backgroundSprite));
    buttonBack->render(target);
}