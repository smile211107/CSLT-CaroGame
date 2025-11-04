#include "MainMenuState.h"
#include "GameState.h"
#include "Button.h"
#include "NewGameState.h" 
#include "State.h"
#include <iostream>
#include <SFML/Graphics.hpp>
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
    this->nextState = GameState::MainMenu;
    this->menuBackgroundTexture = std::make_unique<sf::Texture>();
    
    // 2. Tải file (dùng -> thay vì .)
    if (!this->menuBackgroundTexture->loadFromFile("Assets/Image/menuBackground.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }
    // 3. Tạo đối tượng Sprite mới VÀ TRUYỀN Texture vào
    //    Dùng dấu * để lấy đối tượng Texture từ con trỏ
    this->menuBackgroundSprite = std::make_unique<sf::Sprite>(*(this->menuBackgroundTexture));

    // 4. Scale (dùng ->)
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
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {

     
        if (mouseEvent->button == sf::Mouse::Button::Left) {

            

            sf::Vector2f mousePos = this->window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });
             
            if (this->buttonNewGame.isMouseOver(mousePos)) {
                std::cout << "Yeu cau chuyen sang New Game!" << std::endl;
                this->nextState = GameState::NewGame;
            }
            if (this->buttonLoadGame.isMouseOver(mousePos)) {
                std::cout << "Chua lam trang Load Game!" << std::endl;
            }
            if (this->buttonTutorials.isMouseOver(mousePos)) {
                std::cout << "Yeu cau chuyen sang Tutorials" << std::endl;
                this->nextState = GameState::Tutorials;
            }
            if (this->buttonAboutUs.isMouseOver(mousePos)) {
                std::cout << "Yeu cau chuyen sang About Us" << std::endl;
                this->nextState = GameState::AboutUs;
            }
            if (this->buttonSettings.isMouseOver(mousePos)) {
                std::cout << "Chua lam trang Settings" << std::endl;
            }
            if (this->buttonExit.isMouseOver(mousePos)) {
                this->nextState = GameState::Exiting;
            }
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