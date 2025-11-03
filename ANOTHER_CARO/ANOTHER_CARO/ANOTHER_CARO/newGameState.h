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
    std::vector<Button*> menuButtons; // Danh sách các con trỏ tới tất cả các nút
    int selectedButtonIndex;
   
    Button buttonTwoPlayer;
    Button buttonThreePlayer;
    Button buttonBack;

    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;

    GameState nextState;
};