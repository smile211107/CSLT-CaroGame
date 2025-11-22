#pragma once
#include "State.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <cstring>

// Biến toàn cục cho trạng thái nhạc
extern bool g_musicOn;
extern bool g_soundOn;
extern bool g_language;

extern std::string ngonngu[2];

class SettingsState : public State {
private:
    sf::RenderWindow& window;
    sf::Font& font;

    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;

    Button buttonBack;
    Button buttonMusic;
    Button buttonSound;
    Button buttonVN;
    Button buttonEN;


    GameState nextState;

public:
    // Constructor không cần truyền musicOn nữa
    SettingsState(sf::RenderWindow& window, sf::Font& font);

    void handleEvent(const sf::Event& event) override;
    void update(sf::Vector2f mousePos) override;
    void render(sf::RenderTarget& target) override;

    GameState getNextState() override;

    bool getMusicSetting() const;
    // bool getSoundSetting() const;
};
