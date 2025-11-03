#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    // ham khoi tao dung de lam gi
    Button() = default;

    // ham setup button nhap vao text,font,position va size
    Button(const std::string& text, sf::Font& font,
        sf::Vector2f sizeShape, sf::Vector2f position);

    bool isMouseOver(sf::Vector2f mousePos) const;
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget& target) const;
    sf::Vector2f getPosition() const;

private:
    void updateOrigin();

    
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
};