#include "NewGameState.h"
#include "SettingsState.h"
#include <iostream>
#include <memory>
const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };

NewGameState::NewGameState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font)


{
    if (!buttonTwoPlayerTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/2players-button.png")) {
        std::cout << "khong the mo 2playersbutton" << '\n';
    }
    buttonTwoPlayer = std::make_unique<Button>(buttonTwoPlayerTexture,
        sf::Vector2f(window.getSize().x * 0.35f, window.getSize().y * 0.7f));

    if (!buttonThreePlayerTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/3players-button.png")) {
        std::cout << "khong the mo 3players" << '\n';
    }
    buttonThreePlayer = std::make_unique<Button>(buttonThreePlayerTexture,
        sf::Vector2f(window.getSize().x * 0.65f, window.getSize().y * 0.7f));

    if (!buttonBackTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.8f));

    menuButtons.push_back(move(buttonTwoPlayer));
    menuButtons.push_back(move(buttonThreePlayer));
    menuButtons.push_back(move(buttonBack));
    selectedButtonIndex = 0;
    menuButtons[selectedButtonIndex]->setSelected(true);

    nextState = GameState::NewGame;
    backgroundTexture = std::make_unique<sf::Texture>();


    if (!backgroundTexture->loadFromFile("assets/image/" + ngonngu[g_language] + "/selectMode-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    backgroundSprite = std::make_unique<sf::Sprite>(*(backgroundTexture));


    sf::Vector2f backgroundScale(
        static_cast<float>(window.getSize().x) / backgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture->getSize().y
    );
    backgroundSprite->setScale(backgroundScale);
}

GameState NewGameState::getNextState() {
    return nextState;
}

void NewGameState::handleEvent(const sf::Event& event) {
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {

        int prevIndex = selectedButtonIndex;

        if (key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) {

            selectedButtonIndex = (selectedButtonIndex - 1 + menuButtons.size()) % menuButtons.size();
        }
        else if (key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) {

            selectedButtonIndex = (selectedButtonIndex + 1) % menuButtons.size();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {

            /*auto& currentButton = menuButtons[selectedButtonIndex];

            if (currentButton == buttonTwoPlayer) {
                nextState = GameState::TwoPlayer;
            }
            else if (currentButton == buttonThreePlayer) {
                nextState = GameState::ThreePlayer;
            }
            else if (currentButton == buttonBack) {
                nextState = GameState::MainMenu;
            }*/
            if (selectedButtonIndex == 0) {
                nextState = GameState::TwoPlayer;
            }
            else if (selectedButtonIndex == 1) {
                nextState = GameState::ThreePlayer;
            }
            else if (selectedButtonIndex == 2) {
                nextState = GameState::MainMenu;
            }
        }

        if (prevIndex != selectedButtonIndex) {
            menuButtons[prevIndex]->setSelected(false);
            menuButtons[selectedButtonIndex]->setSelected(true);
        }
    }
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

            if (menuButtons[0]->isMouseOver(mousePos)) {
                nextState = GameState::TwoPlayer;
                std::cout << "Bat dau game 2 nguoi!" << std::endl;
            }
            if (menuButtons[1]->isMouseOver(mousePos)) {
                nextState = GameState::ThreePlayer;
                std::cout << "Bat dau game 3 nguoi!" << std::endl;
            }
            if (menuButtons[2]->isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                nextState = GameState::MainMenu;
            }
        }
    }
}

void NewGameState::update(sf::Vector2f mousePos) {
    /*buttonTwoPlayer->update(mousePos);
    buttonThreePlayer->update(mousePos);
    buttonBack->update(mousePos);*/

    for (auto& button : menuButtons) {
        if (button != nullptr) button->update(mousePos);
    }
}

void NewGameState::render(sf::RenderTarget& target) {
    target.draw(*(backgroundSprite));
    /*buttonTwoPlayer->render(target);
    buttonThreePlayer->render(target);
    buttonBack->render(target);*/
    for (auto& button : menuButtons) {
        if (button != nullptr) button->render(target);
    }
}