#include "Button.h"

Button::Button(sf::Texture& texture, sf::Vector2f position)


    //: buttonText(font, text, 24)
    : buttonSprite(texture)
{
    isSelected = false;
 
    //this->buttonSprite.setSize(sizeShape);
    //this->buttonSprite.setFillColor(sf::Color(255, 255, 255)); 
    //this->buttonSprite.setOutlineColor(sf::Color::White);
    //this->buttonSprite.setOutlineThickness(1.f);

    this->buttonSprite.setTexture(texture);
    this->buttonSprite.setScale({ m_normalScale, m_normalScale });

    //this->buttonText.setFillColor(sf::Color::Black);


   
    this->updateOrigin();
    //this->buttonSprite.setPosition(position);
    //this->buttonText.setPosition(position);
    this->buttonSprite.setPosition(position);
}

void Button::updateOrigin() {
    // chinh tam cua vat the ngay chinh giua o hinh chu nhat moi tao
    //sf::Vector2f shapeSize = this->buttonSprite.getSize();
    //this->buttonSprite.setOrigin({ shapeSize.x / 2.0f, shapeSize.y / 2.0f });

    
    //sf::FloatRect textBounds = this->buttonText.getLocalBounds();
    //this->buttonText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.0f,
    //    textBounds.position.y + textBounds.size.y / 2.0f });
    sf::FloatRect spriteBounds = this->buttonSprite.getLocalBounds();
    this->buttonSprite.setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f, 
        spriteBounds.position.y + spriteBounds.size.y / 2.0f });
}

bool Button::isMouseOver(sf::Vector2f mousePos) const {
    return this->buttonSprite.getGlobalBounds().contains(mousePos);
}

void Button::update(sf::Vector2f mousePos) {
    float targetScale = m_normalScale;

    if (this->isMouseOver(mousePos) || this->isSelected) {
        //this->buttonSprite.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(1000))); 
        targetScale = m_hoverScale;
    }
    else {
        //this->buttonSprite.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(400)));
        targetScale = m_normalScale;
    }
    
    //if (isSelected)
    //{
    //    buttonSprite.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(1000)));
    //}
    
    this->buttonSprite.setScale({ targetScale, targetScale });
    
}
void Button::setSelected(bool selected)
{
    isSelected = selected;
}
void Button::render(sf::RenderTarget& target) const {
    target.draw(this->buttonSprite);
    //target.draw(this->buttonText);
}

void Button::setTexture(sf::Texture& newTexture)
{
    this->buttonSprite.setTexture(newTexture);
    this->updateOrigin();
}

sf::Vector2f Button::getPosition() const {
    return this->buttonSprite.getPosition();
}