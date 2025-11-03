#include "PlayerNameInput.h"
#include "TwoPlayerState.h"
#include "Button.h"
#include <iostream>

const sf::Vector2f PLAYER_BUTTON_SIZE = { 400.f, 50.f };

const sf::Vector2f INPUT_BOX_SIZE = { 450.0f, 60.0f };

TwoPlayerState::TwoPlayerState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),
    
  
    buttonBack("Back", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.7f }),
    user1(
        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,
     
        window.getSize().y * 0.3f },
        INPUT_BOX_SIZE,
        font 
    ),


    user2(
      
        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,
      
        window.getSize().y * 0.5f },
        INPUT_BOX_SIZE,
        font
    )
{
    this->nextState = GameState::TwoPlayer;
    std::cout << "Da vao trang New Game (Player Select)!" << std::endl;
    this->twoPlayerBackgroundTexture = std::make_unique<sf::Texture>();

    // 2. Tải file (dùng -> thay vì .)
    if (!this->twoPlayerBackgroundTexture->loadFromFile("Assets/Image/background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    
    //    Dùng dấu * để lấy đối tượng Texture từ con trỏ
    this->twoPlayerBackgroundSprite = std::make_unique<sf::Sprite>(*(this->twoPlayerBackgroundTexture));

    // 4. Scale (dùng ->)
    sf::Vector2f TwoPlayerBackgroundScale(
        static_cast<float>(this->window.getSize().x) / this->twoPlayerBackgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->twoPlayerBackgroundTexture->getSize().y
    );
    this->twoPlayerBackgroundSprite->setScale(TwoPlayerBackgroundScale);
    float startX = window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f + 100.0f; // Vị trí X giữa, hơi lệch phải
    float startY = window.getSize().y * 0.3f; // Vị trí Y bắt đầu
    float spacing = 120.0f;
  
}

GameState TwoPlayerState::getNextState() {
    return this->nextState;
}


void TwoPlayerState::handleEvent(const sf::Event& event) {

    // 1. XỬ LÝ SỰ KIỆN NHẬP KÝ TỰ (Bằng getIf<>)
    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
    {
        // Truyền ký tự cho cả hai ô (ô nào active sẽ tự nhận)
        user1.type(textEvent->unicode);
        user2.type(textEvent->unicode);
    }

    // 2. XỬ LÝ SỰ KIỆN CLICK CHUỘT (Bằng getIf<>)
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {

        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords(mouseEvent->position);

            // Kiểm tra nút Back
            if (this->buttonBack.isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                this->nextState = GameState::NewGame;
            }

            // Xử lý chuyển active cho ô nhập liệu
            if (user1.checkClick(mousePos)) {
                user1.setActive(true);
                user2.setActive(false);
            }
            else if (user2.checkClick(mousePos)) {
                user1.setActive(false);
                user2.setActive(true);
            }
            else if (!this->buttonBack.isMouseOver(mousePos)) {
                // Nếu click ra ngoài (và không phải nút Back)
                user1.setActive(false);
                user2.setActive(false);
            }
        }
    }
}

void TwoPlayerState::update(sf::Vector2f mousePos) {
   
    this->buttonBack.update(mousePos);
}

void TwoPlayerState::render(sf::RenderTarget& target) {

    // 1. Vẽ Background
    target.draw(*(this->twoPlayerBackgroundSprite));

    // 2. VẼ HAI Ô NHẬP LIỆU
    target.draw(user1);
    target.draw(user2);

    // 3. Vẽ nút Back
    this->buttonBack.render(target);
}