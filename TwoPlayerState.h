#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h" 
#include "PlayerNameInput.h"
#include <SFML/Graphics.hpp>
#include <memory>




class TwoPlayerState : public State {
public:

    TwoPlayerState(sf::RenderWindow& window, sf::Font& font);


    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:

    sf::RenderWindow& window;
    sf::Font& font;
    std::vector<PlayerNameInput> nameInputs;

    std::vector<PlayerNameInput*> menuInputs;
    int selectedButtonIndex;
    std::unique_ptr<sf::Texture>    twoPlayerBackgroundTexture;
    std::unique_ptr<sf::Sprite>     twoPlayerBackgroundSprite;


    sf::Text textUser1;
    sf::Text textUser2;


    PlayerNameInput user1;

    PlayerNameInput user2;
    std::unique_ptr<Button> buttonBack;
    sf::Texture buttonBackTexture;

    void updateActiveInput();
    GameState nextState;
};