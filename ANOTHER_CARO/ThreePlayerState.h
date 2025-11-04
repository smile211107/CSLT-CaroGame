#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h" // Thêm file này
#include "PlayerNameInput.h"
#include <SFML/Graphics.hpp>
#include <memory>



// Kế thừa từ lớp "State"
class ThreePlayerState : public State {
public:
    // Constructor: "Mượn" (tham chiếu) window và font từ lớp Game
    ThreePlayerState(sf::RenderWindow& window, sf::Font& font);

    // Ghi đè (override) 4 hàm "ảo" từ lớp State
    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

private:
    // Nó không "sở hữu" 2 cái này, nó chỉ "mượn"
    sf::RenderWindow& window;
    sf::Font& font;
    std::vector<PlayerNameInput> nameInputs;

    std::unique_ptr<sf::Texture>    threePlayerBackgroundTexture;
    std::unique_ptr<sf::Sprite>     threePlayerBackgroundSprite;


    sf::Text textUser1;
    sf::Text textUser2;
    sf::Text textUser3;

    PlayerNameInput user1;
    PlayerNameInput user2;
    PlayerNameInput user3;
    Button buttonBack;
    Button continueButton;
    // Biến để lưu "trang" tiếp theo
    GameState nextState;
};