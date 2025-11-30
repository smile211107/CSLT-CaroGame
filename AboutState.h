#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>


class AboutState : public State {
public:

    AboutState(sf::RenderWindow& window, sf::Font& font);

    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:
    sf::RenderWindow& window;
    sf::Font& font;

    std::unique_ptr<Button> buttonBack;
    sf::Texture buttonBackTexture;

    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;

    GameState nextState;
};