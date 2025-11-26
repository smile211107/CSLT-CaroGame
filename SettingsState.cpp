#include "SettingsState.h"
#include <iostream>

const sf::Vector2f BUTTON_SIZE = { 400.f, 60.f };
const float GAP = 130.f;

// Định nghĩa biến toàn cục
bool g_musicOn = true;
bool g_soundOn = true;
bool g_language = true; // true = English, false = Vietnamese
std::string ngonngu[2] = { "vn", "en"};

SettingsState::SettingsState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
      font(font)
     
{
    if (!onMusicTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/on-music-button.png")) {
        std::cout << "khong the mo on musicbutton" << '\n';
    }
    if (!offMusicTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/off-music-button.png")) {
        std::cout << "khong the mo off musicbutton" << '\n';
    }
    buttonMusic = std::make_unique<Button>(g_musicOn ? onMusicTexture : offMusicTexture,
        sf::Vector2f(window.getSize().x / 2.f - 298, window.getSize().y * 0.5f));

    if (!onSoundTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/on-sfx-button.png")) {
        std::cout << "khong the mo on sfxbutton" << '\n';
    }
    if (!offSoundTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/off-sfx-button.png")) {
        std::cout << "khong the mo off sfxbutton" << '\n';
    }
    buttonSound = std::make_unique<Button>(g_soundOn ? onSoundTexture : offSoundTexture,
        sf::Vector2f(window.getSize().x / 2.f - 298, window.getSize().y * 0.5f + GAP));

    if (!onVNTexture.loadFromFile("Assets/image/vn/vn-lang.png")) {
        std::cout << "khong the mo on vnlang" << '\n';
    }
    if (!offVNTexture.loadFromFile("Assets/image/en/vn-lang.png")) {
        std::cout << "khong the mo off vnlang" << '\n';
    }
    buttonVN = std::make_unique<Button>(g_language ? offVNTexture : onVNTexture,
        sf::Vector2f(window.getSize().x / 2.f + 298, window.getSize().y * 0.5f));

    if (!onENTexture.loadFromFile("Assets/image/en/en-lang.png")) {
        std::cout << "khong the mo on enlang" << '\n';
    }
    if (!offENTexture.loadFromFile("Assets/image/vn/en-lang.png")) {
        std::cout << "khong the mo off enlang" << '\n';
    }
    buttonEN = std::make_unique<Button>(g_language ? onENTexture : offENTexture,
        sf::Vector2f(window.getSize().x / 2.f + 298, window.getSize().y * 0.5f + GAP));

    if (!buttonBackTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/return-button.png")) {
        std::cout << "khong the mo returnbutton" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.f, window.getSize().y * 0.8f));

    nextState = GameState::Settings;

    // Load background
    backgroundTexture = std::make_unique<sf::Texture>();
    if (!backgroundTexture->loadFromFile("Assets/Image/"+ngonngu[g_language]+"/settings-background.png")) {
        std::cerr << "⚠️ Không thể tải background.png\n";
    }
    backgroundSprite = std::make_unique<sf::Sprite>(*backgroundTexture);

    // Scale background để vừa màn hình
    sf::Vector2f scale(
        static_cast<float>(window.getSize().x) / backgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture->getSize().y
    );
    backgroundSprite->setScale(scale);
}

void SettingsState::handleEvent(const sf::Event& event) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(
                { mouseEvent->position.x, mouseEvent->position.y });

            // Toggle nhạc
            if (buttonMusic->isMouseOver(mousePos)) {
                g_musicOn = !g_musicOn;  // cập nhật global variable
               // buttonMusic.setLabel("Music: " + std::string(g_musicOn ? "ON" : "OFF"));
                if (g_musicOn) {
                    buttonMusic->setTexture(onMusicTexture);
                }
                else {
                    buttonMusic->setTexture(offMusicTexture);
                }
            }

            // Quay về menu chính
             // Toggle sound effect
            if (buttonSound->isMouseOver(mousePos)) {
                g_soundOn = !g_soundOn;
                buttonSound->setTexture(g_soundOn ? onSoundTexture : offSoundTexture);
            }
            if (buttonVN->isMouseOver(mousePos)) {
                g_language = false;
            }
            if (buttonEN->isMouseOver(mousePos)) {
                g_language = true;
            }

            if (buttonBack->isMouseOver(mousePos)) {
                nextState = GameState::MainMenu;
            }
        }
    }
}

void SettingsState::update(sf::Vector2f mousePos) {
    buttonBack->update(mousePos);
    buttonMusic->update(mousePos);
    buttonSound->update(mousePos);
    buttonVN->update(mousePos);
    buttonEN->update(mousePos);
    if (g_language == true) {
        buttonVN->setTexture(offVNTexture);
        buttonEN->setTexture(onENTexture);
    }
    else {
        buttonVN->setTexture(onVNTexture);
        buttonEN->setTexture(offENTexture);
    }
}

void SettingsState::render(sf::RenderTarget& target) {
    target.draw(*backgroundSprite);
    buttonMusic->render(target);
    buttonBack->render(target);
    buttonSound->render(target);
    buttonVN->render(target);
    buttonEN->render(target);
}

GameState SettingsState::getNextState() {
    return nextState;
}

bool SettingsState::getMusicSetting() const {
    return g_musicOn; // trả về global variable
}
