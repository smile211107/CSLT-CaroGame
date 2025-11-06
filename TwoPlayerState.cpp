#include "PlayerNameInput.h"
#include "TwoPlayerState.h"

#include "GamePlay.h"
#include "Game.h"
#include "Button.h"
#include <iostream>
#include <memory>
using namespace std;

const sf::Vector2f PLAYER_BUTTON_SIZE = { 250.f, 50.f };


const sf::Vector2f INPUT_BOX_SIZE = { 450.0f, 60.0f };

TwoPlayerState::TwoPlayerState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),
   
    textUser1(font, "Player 1's name", 48),
    textUser2(font, "Player 2's name", 48),

    buttonBack("Back", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x * 0.6f, window.getSize().y * 0.8f }),
    continueButton("Continue", font, PLAYER_BUTTON_SIZE,
        { window.getSize().x * 0.4f, window.getSize().y * 0.8f }),

    user1(

        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,

        window.getSize().y * 0.45f },
        INPUT_BOX_SIZE,
        font
    ),


    user2(

        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,
        window.getSize().y * 0.65f },
        INPUT_BOX_SIZE,
        font
    )
{
    gameMode = 2;
    sf::FloatRect textBounds = this->textUser1.getLocalBounds();
    /*textBounds = this->textUser1.getLocalBounds();
    this->textUser1.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser1.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.4f });*/

                           //cout << textBounds.position.x << " " << window.getSize().x << endl;



    textBounds = this->textUser1.getLocalBounds();
    this->textUser1.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser1.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.4f });


    textBounds = this->textUser2.getLocalBounds();
    this->textUser2.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser2.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.6f });

    this->nextState = GameState::TwoPlayer;
    std::cout << "Da vao trang New Game (Player Select)!" << std::endl;
    this->twoPlayerBackgroundTexture = std::make_unique<sf::Texture>();


    if (!this->twoPlayerBackgroundTexture->loadFromFile("Assets/Image/typeName2-background-vn.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    this->twoPlayerBackgroundSprite = std::make_unique<sf::Sprite>(*(this->twoPlayerBackgroundTexture));


    sf::Vector2f TwoPlayerBackgroundScale(
        static_cast<float>(this->window.getSize().x) / this->twoPlayerBackgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->twoPlayerBackgroundTexture->getSize().y
    );
    this->twoPlayerBackgroundSprite->setScale(TwoPlayerBackgroundScale);
    float startX = window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f + 100.0f;
    float startY = window.getSize().y * 0.3f;
    float spacing = 120.0f;


}

GameState TwoPlayerState::getNextState() {
    return this->nextState;
}


void TwoPlayerState::handleEvent(const sf::Event& event) {


    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
    {

        user1.type(textEvent->unicode);
        user2.type(textEvent->unicode);
    }


    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {

        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords(mouseEvent->position);


            if (this->buttonBack.isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                this->nextState = GameState::NewGame;
            }

            if (this->continueButton.isMouseOver(mousePos)) {
                std::cout << "qua man hinh gameplay" << '\n';

                this->nextState = GameState::Playing;
               ;
                
            }

            if (user1.checkClick(mousePos)) {
                user1.setActive(true);
                user2.setActive(false);
            }
            else if (user2.checkClick(mousePos)) {
                user1.setActive(false);
                user2.setActive(true);
            }
            else if (!this->buttonBack.isMouseOver(mousePos)) {

                user1.setActive(false);
                user2.setActive(false);
            }
        }
    }
}

void TwoPlayerState::update(sf::Vector2f mousePos) {

    this->buttonBack.update(mousePos);
    this->continueButton.update(mousePos);

}

void TwoPlayerState::render(sf::RenderTarget& target) {


    target.draw(*(this->twoPlayerBackgroundSprite));


    target.draw(user1);
    target.draw(user2);
    target.draw(textUser1);
    target.draw(textUser2);

    this->buttonBack.render(target);
    this->continueButton.render(target);

}