#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h" 
#include "GamePlay.h" 
#include "PlayerNameInput.h"
#include <SFML/Graphics.hpp>
#include <memory>




class SaveState : public State {
public:

    SaveState(sf::RenderWindow& window, sf::Font& font);


    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:

    sf::RenderWindow& window;
    sf::Font& font;

    std::unique_ptr<sf::Texture>    saveBackgroundTexture;
    std::unique_ptr<sf::Sprite>     saveBackgroundSprite;


    sf::Text fileName;


    PlayerNameInput fileInput;

    std::unique_ptr<Button> buttonBack;
    sf::Texture buttonBackTexture;

    void updateActiveInput();
    GameState nextState;
};