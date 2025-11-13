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
    sf::Texture buttonNewGameTexture;
    sf::Texture buttonLoadGameTexture;
    sf::Texture buttonTutorialsTexture;
    sf::Texture buttonAboutUsTexture;
    sf::Texture buttonSettingsTexture;
    sf::Texture buttonExitTexture;

    std::unique_ptr<sf::Sprite> menuBackgroundSprite;
    std::vector<std::unique_ptr<Button>> menuButtons;

    std::unique_ptr<Button> buttonNewGame;
    std::unique_ptr<Button> buttonLoadGame;
    std::unique_ptr<Button> buttonTutorials;
    std::unique_ptr<Button> buttonAboutUs;
    std::unique_ptr<Button> buttonSettings;
    std::unique_ptr<Button> buttonExit;
    sf::Music mainMenuMusic;
    int selectedButtonIndex;

    
    GameState nextState;
};