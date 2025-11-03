#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h" // Thêm file này
#include <SFML/Graphics.hpp>
#include <memory>

// Kế thừa từ lớp "State"
class MainMenuState : public State {
public:
    MainMenuState(sf::RenderWindow& window, sf::Font& font);

    // Ghi đè (override) 4 hàm "ảo" từ lớp State
    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:
    // Nó không "sở hữu" 2 cái này, nó chỉ "mượn"
    sf::RenderWindow& window;
    sf::Font& font;
    std::unique_ptr<sf::Texture> menuBackgroundTexture;
    std::unique_ptr<sf::Sprite> menuBackgroundSprite;
    std::vector<Button*> menuButtons;
    
    Button buttonNewGame;
    Button buttonLoadGame;
    Button buttonTutorials;
    Button buttonAboutUs;
    Button buttonSettings;
    Button buttonExit;
    int selectedButtonIndex;

    // Biến để lưu "trang" tiếp theo
    GameState nextState;
};