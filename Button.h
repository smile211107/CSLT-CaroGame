#pragma once

#include <SFML/Graphics.hpp>
//#include <string>

class Button {
public:

    Button() = delete;


    //Button(const std::string& text, sf::Font& font,
    //    sf::Vector2f sizeShape, sf::Vector2f position);
    Button(sf::Texture& texture, sf::Vector2f position);

    bool isMouseOver(sf::Vector2f mousePos) const;
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget& target) const;
    sf::Vector2f getPosition() const;
    void setSelected(bool selected);
    //void setLabel(const std::string& newText) {
    //    buttonText.setString(newText);
    //}

    void setTexture(sf::Texture& newTexture);

private:
    void updateOrigin();

    bool isSelected;

    sf::Sprite buttonSprite;
    //sf::Text buttonText;

    const float m_normalScale = 1.0f;
    const float m_hoverScale = 1.2f;
};