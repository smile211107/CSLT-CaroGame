#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>


class NewGameState : public State {
public:

    NewGameState(sf::RenderWindow& window, sf::Font& font);

    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:
    sf::RenderWindow& window;
    sf::Font& font;

    std::unique_ptr<Button> buttonTwoPlayer;
    std::unique_ptr<Button> buttonThreePlayer;
    std::unique_ptr<Button> buttonBack;
    sf::Texture buttonTwoPlayerTexture;
    sf::Texture buttonThreePlayerTexture;
    sf::Texture buttonBackTexture;

    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;
    std::vector<std::unique_ptr<Button>> menuButtons;
    int selectedButtonIndex;
    GameState nextState;
};