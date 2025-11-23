#include "Button.h"

Button::Button(sf::Texture& texture, sf::Vector2f position)


    //: buttonText(font, text, 24)
    : buttonSprite(texture)
{
    isSelected = false;
 
    //buttonSprite.setSize(sizeShape);
    //buttonSprite.setFillColor(sf::Color(255, 255, 255)); 
    //buttonSprite.setOutlineColor(sf::Color::White);
    //buttonSprite.setOutlineThickness(1.f);

    buttonSprite.setTexture(texture);
    buttonSprite.setScale({ m_normalScale, m_normalScale });

    //buttonText.setFillColor(sf::Color::Black);


   
    updateOrigin();
    //buttonSprite.setPosition(position);
    //buttonText.setPosition(position);
    buttonSprite.setPosition(position);
}

void Button::updateOrigin() {
    // chinh tam cua vat the ngay chinh giua o hinh chu nhat moi tao
    //sf::Vector2f shapeSize = buttonSprite.getSize();
    //buttonSprite.setOrigin({ shapeSize.x / 2.0f, shapeSize.y / 2.0f });

    
    //sf::FloatRect textBounds = buttonText.getLocalBounds();
    //buttonText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.0f,
    //    textBounds.position.y + textBounds.size.y / 2.0f });
    sf::FloatRect spriteBounds = buttonSprite.getLocalBounds();
    buttonSprite.setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f, 
        spriteBounds.position.y + spriteBounds.size.y / 2.0f });
}

bool Button::isMouseOver(sf::Vector2f mousePos) const {
    return buttonSprite.getGlobalBounds().contains(mousePos);
}

void Button::update(sf::Vector2f mousePos) {
    float targetScale = m_normalScale;

    if (isMouseOver(mousePos) || isSelected) {
        //buttonSprite.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(1000))); 
        targetScale = m_hoverScale;
    }
    else {
        //buttonSprite.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(400)));
        targetScale = m_normalScale;
    }
    
    //if (isSelected)
    //{
    //    buttonSprite.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(1000)));
    //}
    
    buttonSprite.setScale({ targetScale, targetScale });
    
}
void Button::setSelected(bool selected)
{
    isSelected = selected;
}
void Button::render(sf::RenderTarget& target) const {
    target.draw(buttonSprite);
    //target.draw(buttonText);
}

void Button::setTexture(sf::Texture& newTexture)
{
    buttonSprite.setTexture(newTexture);
    updateOrigin();
}

sf::Vector2f Button::getPosition() const {
    return buttonSprite.getPosition();
}