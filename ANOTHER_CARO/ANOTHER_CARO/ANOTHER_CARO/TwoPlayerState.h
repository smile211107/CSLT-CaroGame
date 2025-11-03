#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h" // Thêm file này
#include "PlayerNameInput.h"
#include <SFML/Graphics.hpp>
#include <memory>



// Kế thừa từ lớp "State"
class TwoPlayerState : public State {
public:
    // Constructor: "Mượn" (tham chiếu) window và font từ lớp Game
    TwoPlayerState(sf::RenderWindow& window, sf::Font& font);

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

    std::vector<Button*> menuButtons; // Danh sách các con trỏ tới tất cả các nút
    int selectedButtonIndex;

    std::unique_ptr<sf::Texture>    twoPlayerBackgroundTexture;
    std::unique_ptr<sf::Sprite>     twoPlayerBackgroundSprite;

    
    sf::Text textUser1;
    sf::Text textUser2;
    
    PlayerNameInput user1;
    PlayerNameInput user2;
    Button buttonBack;
    Button continueButton;
    // Biến để lưu "trang" tiếp theo
    GameState nextState;
};