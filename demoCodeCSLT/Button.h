#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:

    Button() = default;


    Button(const std::string& text, sf::Font& font,
        sf::Vector2f sizeShape, sf::Vector2f position);

    bool isMouseOver(sf::Vector2f mousePos) const;
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget& target) const;
    sf::Vector2f getPosition() const;
    void setSelected(bool selected);

private:
    void updateOrigin();

    bool isSelected;

    sf::RectangleShape buttonShape;
    sf::Text buttonText;
};