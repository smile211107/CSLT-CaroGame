#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "SettingsState.h"
#include "PlayerNameInput.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class ThreePlayerState : public State {
public:

    ThreePlayerState(sf::RenderWindow& window, sf::Font& font);


    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:

    sf::RenderWindow& window;
    sf::Font& font;
    std::vector<PlayerNameInput> nameInputs;
    std::vector<pair<PlayerNameInput*,int>> buttonInputs;

    std::unique_ptr<sf::Texture>    threePlayerBackgroundTexture;
    std::unique_ptr<sf::Sprite>     threePlayerBackgroundSprite;

    int selectedButtonIndex;


    sf::Text textUser1;
    sf::Text textUser2;
    sf::Text textUser3;

    PlayerNameInput user1;
    PlayerNameInput user2;
    PlayerNameInput user3;
   
    std::unique_ptr<Button> buttonBack;
    sf::Texture buttonBackTexture;


    GameState nextState;
    void updateActiveInput();
};