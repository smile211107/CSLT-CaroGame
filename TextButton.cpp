#include "TextButton.h"

TextButton::TextButton(const std::string& text, sf::Font& font,
    sf::Vector2f sizeShape, sf::Vector2f position)


    : buttonText(font, text, 24)
{
    isSelected = false;

    this->buttonShape.setSize(sizeShape);
    this->buttonShape.setFillColor(sf::Color(255, 255, 255));
    this->buttonShape.setOutlineColor(sf::Color::White);
    this->buttonShape.setOutlineThickness(1.f);


    this->buttonText.setFillColor(sf::Color::Black);



    this->updateOrigin();
    this->buttonShape.setPosition(position);
    this->buttonText.setPosition(position);
}

void TextButton::updateOrigin() {
    // chinh tam cua vat the ngay chinh giua o hinh chu nhat moi tao
    sf::Vector2f shapeSize = this->buttonShape.getSize();
    this->buttonShape.setOrigin({ shapeSize.x / 2.0f, shapeSize.y / 2.0f });


    sf::FloatRect textBounds = this->buttonText.getLocalBounds();
    this->buttonText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f });
}

bool TextButton::isMouseOver(sf::Vector2f mousePos) const {
    return this->buttonShape.getGlobalBounds().contains(mousePos);
}

void TextButton::update(sf::Vector2f mousePos) {
    if (this->isMouseOver(mousePos)) {
        this->buttonShape.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(1000)));
    }
    else {
        this->buttonShape.setFillColor(sf::Color(255, 0, 0, static_cast<uint8_t>(400)));
    }
    if (isMouseOver(mousePos))
    {
        buttonShape.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(1000)));
    }
    else if (isSelected)
    {
        buttonShape.setFillColor(sf::Color(255, 255, 255, static_cast<uint8_t>(1000)));
    }

    else
    {
        buttonShape.setFillColor(sf::Color(255, 0, 0, static_cast<uint8_t>(400)));
    }
}

void TextButton::setSelected(bool selected) {
    this->isSelected = selected;
    if (selected)
        this->buttonShape.setFillColor(sf::Color(255, 200, 0)); // vàng khi chọn
    else
        this->buttonShape.setFillColor(sf::Color(150, 150, 150)); // xám khi không chọn
}

void TextButton::render(sf::RenderTarget& target) const {
    target.draw(this->buttonShape);
    target.draw(this->buttonText);
}

sf::Vector2f TextButton::getPosition() const {
    return this->buttonShape.getPosition();
}
