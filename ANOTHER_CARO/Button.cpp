#include "Button.h"

// SỬA LỖI: Đây là CONSTRUCTOR, không phải hàm setup
Button::Button(const std::string& text, sf::Font& font,
    sf::Vector2f sizeShape, sf::Vector2f position)

    // SỬA LỖI QUAN TRỌNG: Khởi tạo buttonText (sf::Text) ở đây
    : buttonText(font, text, 24)
{
    // --- Cài đặt Shape ---
    this->buttonShape.setSize(sizeShape);
    this->buttonShape.setFillColor(sf::Color(255, 255, 255)); // Nền trắng mờ
    this->buttonShape.setOutlineColor(sf::Color::White);
    this->buttonShape.setOutlineThickness(1.f);

    // --- Cài đặt Text ---
    // (Không cần setFont, setString, setSize nữa, đã làm ở trên)
    this->buttonText.setFillColor(sf::Color::Black);
    

    // --- Cài đặt Vị trí & Căn giữa ---
    this->updateOrigin();
    this->buttonShape.setPosition(position);
    this->buttonText.setPosition(position);
}

void Button::updateOrigin() {
    // 1. Căn giữa Shape
    sf::Vector2f shapeSize = this->buttonShape.getSize();
    this->buttonShape.setOrigin({ shapeSize.x / 2.0f, shapeSize.y / 2.0f });

    // 2. Căn giữa Text
    sf::FloatRect textBounds = this->buttonText.getLocalBounds();
    this->buttonText.setOrigin({ textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f });
}

bool Button::isMouseOver(sf::Vector2f mousePos) const {
    return this->buttonShape.getGlobalBounds().contains(mousePos);
}

void Button::update(sf::Vector2f mousePos) {
    if (this->isMouseOver(mousePos)) {
        this->buttonShape.setFillColor(sf::Color(255, 255, 255, 1000)); // Sáng hơn
    }
    else {
        this->buttonShape.setFillColor(sf::Color(255, 255, 255, 400)); // Mờ lại
    }
}

void Button::render(sf::RenderTarget& target) const {
    target.draw(this->buttonShape);
    target.draw(this->buttonText);
}

sf::Vector2f Button::getPosition() const {
    return this->buttonShape.getPosition();
}