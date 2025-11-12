#include "PlayerNameInput.h"
#include "ThreePlayerState.h"
#include "Button.h"
#include <iostream>
#include <memory>
using namespace std;

const sf::Vector2f PLAYER_BUTTON_SIZE = { 250.f, 50.f };
const sf::Vector2f INPUT_BOX_SIZE = { 450.0f, 60.0f };
int cntInputs = 0;
ThreePlayerState::ThreePlayerState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),
    textUser1(font, "Player 1's name", 48),
    textUser2(font, "Player 2's name", 48),
    textUser3(font, "Player 3's name", 48),

    buttonBack("Back", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x / 2.0f, window.getSize().y * 0.92f }),
    user1(

        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,

        window.getSize().y * 0.45f },
        INPUT_BOX_SIZE,
        font
    ),


    user2(

        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,
        window.getSize().y * 0.6f },
        INPUT_BOX_SIZE,
        font
    ),

    user3(

        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,
        window.getSize().y * 0.75f },
        INPUT_BOX_SIZE,
        font
    )

{
    gameMode = 3;
    buttonInputs.push_back(&user1);
    buttonInputs.push_back(&user2);
    buttonInputs.push_back(&user3);
    selectedButtonIndex = 0;
    user1.setActive(true);

    sf::FloatRect textBounds = this->textUser1.getLocalBounds();

    textBounds = this->textUser1.getLocalBounds();
    this->textUser1.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser1.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.4f });


    textBounds = this->textUser2.getLocalBounds();
    this->textUser2.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser2.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.55f });

    textBounds = this->textUser3.getLocalBounds();
    this->textUser3.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser3.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.7f });

    this->nextState = GameState::ThreePlayer;
    std::cout << "Da vao trang New Game (Player Select)!" << std::endl;
    this->threePlayerBackgroundTexture = std::make_unique<sf::Texture>();


    if (!this->threePlayerBackgroundTexture->loadFromFile("Assets/Image/vn/typeName3-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    this->threePlayerBackgroundSprite = std::make_unique<sf::Sprite>(*(this->threePlayerBackgroundTexture));


    sf::Vector2f threePlayerBackgroundScale(
        static_cast<float>(this->window.getSize().x) / this->threePlayerBackgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->threePlayerBackgroundTexture->getSize().y
    );
    this->threePlayerBackgroundSprite->setScale(threePlayerBackgroundScale);
    float startX = window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f + 100.0f;
    float startY = window.getSize().y * 0.3f;
    float spacing = 120.0f;


}

GameState ThreePlayerState::getNextState() {
    return this->nextState;
}


void ThreePlayerState::handleEvent(const sf::Event& event) {


    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
    {
        if (!buttonInputs.empty()) {
            buttonInputs[selectedButtonIndex]->type(textEvent->unicode);
        }
    }

    // 2. XỬ LÝ ĐIỀU KHIỂN
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {

        if (key->scancode == sf::Keyboard::Scancode::Up) {
            if (buttonInputs.empty()) return;
            selectedButtonIndex = (selectedButtonIndex - 1 + buttonInputs.size()) % buttonInputs.size();
            updateActiveInput();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Down) {
            if (buttonInputs.empty()) return;
            selectedButtonIndex = (selectedButtonIndex + 1) % buttonInputs.size();
            updateActiveInput();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {
            if (buttonInputs.empty()) return;


            PlayerNameInput* currentInput = buttonInputs[selectedButtonIndex];
            std::string confirmedName = currentInput->getName();
            playerNames[++cntInputs] = confirmedName;
            std::cout << "Da luu ten: " << confirmedName << '\n';



            buttonInputs.erase(buttonInputs.begin() + selectedButtonIndex);

            if (cntInputs == 3) {
                cntInputs %= 3;
                this->nextState = GameState::Playing;

            }
            else {

                if (!buttonInputs.empty()) selectedButtonIndex = selectedButtonIndex % buttonInputs.size();
                updateActiveInput();
            }
        }

    }


    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {

        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords(mouseEvent->position);


            if (this->buttonBack.isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                this->nextState = GameState::NewGame;
            }
            if (user1.checkClick(mousePos)) {
                user1.setActive(true);
                user2.setActive(false);
                user3.setActive(false);
            }
            else if (user2.checkClick(mousePos)) {
                user1.setActive(false);
                user3.setActive(false);
                user2.setActive(true);
            }
            else if (user3.checkClick(mousePos)) {
                user1.setActive(false);
                user2.setActive(false);
                user3.setActive(true);
            }
            else if (!this->buttonBack.isMouseOver(mousePos)) {
                user1.setActive(false);
                user2.setActive(false);
                user3.setActive(false);
            }
        }
    }
}

void ThreePlayerState::updateActiveInput() {
    if (buttonInputs.empty()) return; // Tránh crash nếu vector rỗng

    PlayerNameInput* input = buttonInputs[selectedButtonIndex];

    // Tắt hết
    user1.setActive(false);
    user2.setActive(false);
    user3.setActive(false);

    // Bật cái được chọn
    if (input == &this->user1) user1.setActive(true);
    else if (input == &this->user2) user2.setActive(true);
    else if (input == &this->user3) user3.setActive(true);
}

void ThreePlayerState::update(sf::Vector2f mousePos) {

    this->buttonBack.update(mousePos);


}

void ThreePlayerState::render(sf::RenderTarget& target) {


    target.draw(*(this->threePlayerBackgroundSprite));


    target.draw(user1);
    target.draw(user2);
    target.draw(user3);
    target.draw(textUser1);
    target.draw(textUser2);
    target.draw(textUser3);

    this->buttonBack.render(target);


}