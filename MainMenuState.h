#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h" 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>


class MainMenuState : public State {
public:
    MainMenuState(sf::RenderWindow& window, sf::Font& font);

  
    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:
   
    sf::RenderWindow& window;
    sf::Font& font;
    std::unique_ptr<sf::Texture> menuBackgroundTexture;
    std::unique_ptr<sf::Sprite> menuBackgroundSprite;
    std::vector<Button*> menuButtons;

    Button buttonNewGame;
    Button buttonLoadGame;
    Button buttonTutorials;
    Button buttonAboutUs;
    Button buttonSettings;
    Button buttonExit;
    sf::Music mainMenuMusic;
    int selectedButtonIndex;

    
    GameState nextState;
};