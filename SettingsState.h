#pragma once
#include "State.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>

class SettingsState : public State {
private:
    sf::RenderWindow& window;
    sf::Font& font;

    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;

    Button buttonBack;
    Button buttonMusic;

    bool musicOn;
    GameState nextState;

public:
    SettingsState(sf::RenderWindow& window, sf::Font& font, bool musicOn = true);

    void handleEvent(const sf::Event& event) override;
    void update(sf::Vector2f mousePos) override;
    void render(sf::RenderTarget& target) override;

    GameState getNextState() override;

    bool getMusicSetting() const;
};
