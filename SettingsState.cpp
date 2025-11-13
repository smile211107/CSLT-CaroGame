#include "SettingsState.h"
#include <iostream>

const sf::Vector2f BUTTON_SIZE = { 400.f, 60.f };

// Định nghĩa biến toàn cục
bool g_musicOn = true;

SettingsState::SettingsState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
      font(font)
     
{
    if (!onMusicTexture.loadFromFile("Assets/image/vn/on-music-button.png")) {
        std::cout << "khong the mo on musicbutton" << '\n';
    }
    if (!offMusicTexture.loadFromFile("Assets/image/vn/off-music-button.png")) {
        std::cout << "khong the mo off musicbutton" << '\n';
    }
    buttonMusic = std::make_unique<Button>(g_musicOn ? onMusicTexture : offMusicTexture,
        sf::Vector2f(window.getSize().x / 2.f, window.getSize().y * 0.5f));

    if (!buttonBackTexture.loadFromFile("Assets/image/vn/return-button.png")) {
        std::cout << "khong the mo returnbutton" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.f, window.getSize().y * 0.8f));

    this->nextState = GameState::Settings;

    // Load background
    this->backgroundTexture = std::make_unique<sf::Texture>();
    if (!this->backgroundTexture->loadFromFile("Assets/Image/vn/settings-background.png")) {
        std::cerr << "⚠️ Không thể tải background.png\n";
    }
    this->backgroundSprite = std::make_unique<sf::Sprite>(*this->backgroundTexture);

    // Scale background để vừa màn hình
    sf::Vector2f scale(
        static_cast<float>(window.getSize().x) / this->backgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / this->backgroundTexture->getSize().y
    );
    this->backgroundSprite->setScale(scale);
}

void SettingsState::handleEvent(const sf::Event& event) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords(
                { mouseEvent->position.x, mouseEvent->position.y });

            // Toggle nhạc
            if (this->buttonMusic->isMouseOver(mousePos)) {
                g_musicOn = !g_musicOn;  // cập nhật global variable
               // this->buttonMusic.setLabel("Music: " + std::string(g_musicOn ? "ON" : "OFF"));
                if (g_musicOn) {
                    buttonMusic->setTexture(onMusicTexture);
                }
                else {
                    buttonMusic->setTexture(offMusicTexture);
                }
            }

            // Quay về menu chính
            if (this->buttonBack->isMouseOver(mousePos)) {
                this->nextState = GameState::MainMenu;
            }
        }
    }
}

void SettingsState::update(sf::Vector2f mousePos) {
    this->buttonBack->update(mousePos);
    this->buttonMusic->update(mousePos);
}

void SettingsState::render(sf::RenderTarget& target) {
    target.draw(*this->backgroundSprite);
    this->buttonMusic->render(target);
    this->buttonBack->render(target);
}

GameState SettingsState::getNextState() {
    return this->nextState;
}

bool SettingsState::getMusicSetting() const {
    return g_musicOn; // trả về global variable
}
