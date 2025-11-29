#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

extern std::string playerNames[4];
const int MAX_NAME_LENGTH = 15;
extern int gameMode;
class PlayerNameInput : public sf::Drawable
{
private:

    sf::RectangleShape background;
    sf::Text text;
    std::string currentText;
    bool isActive;
    std::vector<pair<unique_ptr<Button>,int>> menuButtons;
    int selectedButtonIndex;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

    PlayerNameInput(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);



    void setActive(bool active);

    bool checkClick(const sf::Vector2f& mousePos);


    void type(uint32_t unicode);


    std::string getName() const;
};