#include "PlayerNameInput.h"
#include "SettingsState.h"
#include <iostream>
#include <memory>
std::string playerNames[4];
PlayerNameInput::PlayerNameInput(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    :text(font, "", 24),
    selectedButtonIndex(1)
{
    background.setPosition(position);
    background.setSize(size);
    background.setFillColor(sf::Color(139, 69, 19, 180));
    background.setOutlineThickness(0.0f);

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);

    text.setPosition({ position.x + 10, position.y + (size.y / 2.0f) - 20.0f });

    isActive = false;
    currentText = "";
    text.setString(currentText);
    
}


void PlayerNameInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    target.draw(text, states);
}


void PlayerNameInput::setActive(bool active)
{
    isActive = active;

    background.setOutlineThickness(active ? 3.0f : 0.0f);
    background.setOutlineColor(sf::Color::Yellow);


    if (isActive) {
        text.setString(currentText + "|");
    }
    else {
        text.setString(currentText);
    }
}

bool PlayerNameInput::checkClick(const sf::Vector2f& mousePos)
{
    return background.getGlobalBounds().contains(mousePos);
}


void PlayerNameInput::type(uint32_t unicode)
{
    if (!isActive) return;

    if (unicode == 8) // Backspace
    {
        if (!currentText.empty())
            currentText.pop_back();
    }

    else if (unicode < 128) // in ky tu thong thuong
    {
        if (currentText.length() < MAX_NAME_LENGTH)
        {
            currentText += static_cast<char>(unicode);
        }
    }

    // luon update text, them | neu dang active
    text.setString(currentText + (isActive ? "|" : ""));
}

std::string PlayerNameInput::getName() const
{
    return currentText;
}