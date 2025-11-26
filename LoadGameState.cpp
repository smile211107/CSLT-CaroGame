#include "LoadGameState.h"
#include "SettingsState.h"
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
    if (!buttonBackTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.95f));

    nextState = GameState::LoadGame;
    cout << "Da vao trang load game!" << std::endl;
    backgroundTexture = std::make_unique<sf::Texture>();


    if (!backgroundTexture->loadFromFile("Assets/image/"+ngonngu[g_language]+"/loadGame-background.png")) {
        cout << "khong the mo loadgame background" << '\n';
    }

    backgroundSprite = std::make_unique<sf::Sprite>(*(backgroundTexture));


    sf::Vector2f backgroundScale(
        static_cast<float>(window.getSize().x) / backgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture->getSize().y
    );
    backgroundSprite->setScale(backgroundScale);
    buttonBack->setSelected(true);

   
}

GameState LoadGameState::getNextState() {
    return nextState;
}

void LoadGameState::handleEvent(const sf::Event& event) {
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

void LoadGameState::update(sf::Vector2f mousePos) {
    buttonBack->update(mousePos);
}

void LoadGameState::render(sf::RenderTarget& target) {
    target.draw(*(backgroundSprite));
    buttonBack->render(target);
}