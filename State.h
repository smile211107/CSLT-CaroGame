#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h" 

class State {
public:
    virtual ~State() = default;

    
    virtual GameState getNextState() = 0;

    
    virtual void handleEvent(const sf::Event& event) = 0;

    
    virtual void update(sf::Vector2f mousePos) = 0;

    
    virtual void render(sf::RenderTarget& target) = 0;
};