#include "SettingsState.h"
#include <iostream>

const sf::Vector2f BUTTON_SIZE = { 400.f, 60.f };

// Định nghĩa biến toàn cục
bool g_musicOn = true;
bool g_soundOn = true;
bool g_language = true; // true = English, false = Vietnamese
std::string ngonngu[2] = {"vn", "en"};

SettingsState::SettingsState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
      font(font),
      buttonBack("Back", font, BUTTON_SIZE,
                 { window.getSize().x / 2.f, window.getSize().y * 0.8f }),
      buttonMusic("Music: " + std::string(g_musicOn ? "ON" : "OFF"),
                  font, BUTTON_SIZE,
                  { window.getSize().x / 2.f, window.getSize().y * 0.5f }),
      buttonSound("Sound: " + std::string(g_soundOn ? "ON" : "OFF"),
                  font, BUTTON_SIZE,
                  { window.getSize().x / 2.f, window.getSize().y * 0.65f }), 
      buttonLanguage("Language: " + std::string(g_language ? "EN" : "VN"),
               font, BUTTON_SIZE,
               { window.getSize().x / 2.f, window.getSize().y * 0.35f })

{

    this->nextState = GameState::Settings;

    // Load background
    this->backgroundTexture = std::make_unique<sf::Texture>();
    if (!this->backgroundTexture->loadFromFile("Assets/Image/"+ngonngu[g_language]+"/settings-background.png")) {
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
        if (mouseEvent->button == sf::Mouse::Button::Left){
            sf::Vector2f mousePos = this->window.mapPixelToCoords(
                { mouseEvent->position.x, mouseEvent->position.y });

            // Toggle nhạc
            if (this->buttonMusic.isMouseOver(mousePos)) {
                g_musicOn = !g_musicOn;
                this->buttonMusic.setLabel("Music: " + std::string(g_musicOn ? "ON" : "OFF"));
            }

            // Toggle sound effect
            if (this->buttonSound.isMouseOver(mousePos)) {
                g_soundOn = !g_soundOn;
                this->buttonSound.setLabel("Sound: " + std::string(g_soundOn ? "ON" : "OFF"));
            }
            if (this->buttonLanguage.isMouseOver(mousePos)) {
                g_language = !g_language;
                this->buttonLanguage.setLabel("Language: " + std::string(g_language ? "EN" : "VN"));
            }

            // Back
            if (this->buttonBack.isMouseOver(mousePos)) {
                this->nextState = GameState::MainMenu;
            }
        }
    }
}


void SettingsState::update(sf::Vector2f mousePos) {
    this->buttonBack.update(mousePos);
    this->buttonMusic.update(mousePos);
    this->buttonSound.update(mousePos);
    this->buttonLanguage.update(mousePos);
}

void SettingsState::render(sf::RenderTarget& target) {
    target.draw(*this->backgroundSprite);
    this->buttonMusic.render(target);
    this->buttonBack.render(target);
    this->buttonSound.render(target);
    this->buttonLanguage.render(target);
}

GameState SettingsState::getNextState() {
    return this->nextState;
}

bool SettingsState::getMusicSetting() const {
    return g_musicOn; // trả về global variable
}
// bool SettingsState::getSoundSetting() const {
//     return g_soundOn;
// }

