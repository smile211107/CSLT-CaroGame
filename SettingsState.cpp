#include "SettingsState.h"

#include <iostream>

const sf::Vector2f BUTTON_SIZE = { 400.f, 60.f };
const float GAP = 130.f;

// Định nghĩa biến toàn cục
bool g_musicOn = true;
bool g_soundOn = true;
bool g_language = true; // true = English, false = Vietnamese
std::string ngonngu[2] = { "vn", "en" };

SettingsState::SettingsState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font)

{
    if (!onMusicTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/on-music-button.png")) {
        std::cout << "khong the mo on musicbutton" << '\n';
    }
    if (!offMusicTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/off-music-button.png")) {
        std::cout << "khong the mo off musicbutton" << '\n';
    }
    buttonMusic = std::make_unique<Button>(g_musicOn ? onMusicTexture : offMusicTexture,
        sf::Vector2f(window.getSize().x / 2.f - 298, window.getSize().y * 0.5f));

    if (!onSoundTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/on-sfx-button.png")) {
        std::cout << "khong the mo on sfxbutton" << '\n';
    }
    if (!offSoundTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/off-sfx-button.png")) {
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

    if (!buttonBackTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/return-button.png")) {
        std::cout << "khong the mo returnbutton" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.f, window.getSize().y * 0.8f));

    nextState = GameState::Settings;

    // Load background
    backgroundTexture = std::make_unique<sf::Texture>();
    if (!backgroundTexture->loadFromFile("Assets/Image/" + ngonngu[g_language] + "/settings-background.png")) {
        std::cerr << "⚠️ Không thể tải background.png\n";
    }
    backgroundSprite = std::make_unique<sf::Sprite>(*backgroundTexture);

    // Scale background để vừa màn hình
    sf::Vector2f scale(
        static_cast<float>(window.getSize().x) / backgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture->getSize().y
    );
    backgroundSprite->setScale(scale);
    buttonSettings.push_back(move(buttonMusic));
    buttonSettings.push_back(move(buttonSound));
    buttonSettings.push_back(move(buttonVN));
    buttonSettings.push_back(move(buttonEN));
    buttonSettings.push_back(move(buttonBack));

    selectedIdx = 0;
    buttonSettings[selectedIdx]->setSelected(true);

}

void SettingsState::handleEvent(const sf::Event& event) {
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        int prevIndex = selectedIdx;
        if (key->scancode == sf::Keyboard::Scancode::Up) {

            selectedIdx = (selectedIdx - 1 + buttonSettings.size()) % (buttonSettings.size());

        }
        else if (key->scancode == sf::Keyboard::Scancode::Down) {

            selectedIdx = (selectedIdx + 1) % (buttonSettings.size());

        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {
            if (selectedIdx == 0) {
                g_musicOn = !g_musicOn;  // cập nhật global variable
                // buttonMusic.setLabel("Music: " + std::string(g_musicOn ? "ON" : "OFF"));
                if (g_musicOn) {
                    buttonSettings[0]->setTexture(onMusicTexture);
                }
                else {
                    buttonSettings[0]->setTexture(offMusicTexture);
                }

            }
            else if (selectedIdx == 1) {
                g_soundOn = !g_soundOn;
                buttonSettings[1]->setTexture(g_soundOn ? onSoundTexture : offSoundTexture);
            }
            else if (selectedIdx == 2) {
                g_language = false;
            }
            else if (selectedIdx == 3) {
                g_language = true;

            }
            else {
                nextState = GameState::MainMenu;

            }
        }
        if (prevIndex != selectedIdx) {
            buttonSettings[prevIndex]->setSelected(false);
            buttonSettings[selectedIdx]->setSelected(true);
        }
    }

    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(
                { mouseEvent->position.x, mouseEvent->position.y });

            // Toggle nhạc
            if (buttonSettings[0]->isMouseOver(mousePos)) {
                g_musicOn = !g_musicOn;  // cập nhật global variable
                // buttonMusic.setLabel("Music: " + std::string(g_musicOn ? "ON" : "OFF"));
                if (g_musicOn) {
                    buttonSettings[0]->setTexture(onMusicTexture);
                }
                else {
                    buttonSettings[0]->setTexture(offMusicTexture);
                }
            }

            // Quay về menu chính
             // Toggle sound effect
            if (buttonSettings[1]->isMouseOver(mousePos)) {
                g_soundOn = !g_soundOn;
                buttonSettings[1]->setTexture(g_soundOn ? onSoundTexture : offSoundTexture);
            }
            if (buttonSettings[2]->isMouseOver(mousePos)) {
                g_language = false;
            }
            if (buttonSettings[3]->isMouseOver(mousePos)) {
                g_language = true;
            }

            if (buttonSettings[4]->isMouseOver(mousePos)) {
                nextState = GameState::MainMenu;
            }
        }
    }
}

void SettingsState::update(sf::Vector2f mousePos) {

    if (g_language == true) {
        buttonSettings[2]->setTexture(offVNTexture);
        buttonSettings[3]->setTexture(onENTexture);
    }
    else {
        buttonSettings[2]->setTexture(onVNTexture);
        buttonSettings[3]->setTexture(offENTexture);
    }
    for (auto& button : buttonSettings) {
        if (button != nullptr) button->update(mousePos);
    }
}

void SettingsState::render(sf::RenderTarget& target) {
    target.draw(*backgroundSprite);

    for (auto& button : buttonSettings) {
        if (button != nullptr) button->render(target);
    }
}

GameState SettingsState::getNextState() {
    return nextState;
}

bool SettingsState::getMusicSetting() const {
    return g_musicOn; // trả về global variable
}
