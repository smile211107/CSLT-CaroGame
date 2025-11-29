#include "PlayerNameInput.h"
#include "SettingsState.h"
#include "ThreePlayerState.h"
#include "Button.h"
#include "Game.h"
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
    if (!buttonBackTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.92f));

    gameMode = 3;
    buttonInputs.push_back({ &user1,1 });
    buttonInputs.push_back({ &user2,2 });
    buttonInputs.push_back({ &user3,3 });
    selectedButtonIndex = 0;
    user1.setActive(true);

    sf::FloatRect textBounds = textUser1.getLocalBounds();

    textBounds = textUser1.getLocalBounds();
    textUser1.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser1.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.4f });


    textBounds = textUser2.getLocalBounds();
    textUser2.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser2.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.55f });

    textBounds = textUser3.getLocalBounds();
    textUser3.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    textUser3.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.7f });

    nextState = GameState::ThreePlayer;

    threePlayerBackgroundTexture = std::make_unique<sf::Texture>();


    if (!threePlayerBackgroundTexture->loadFromFile("Assets/Image/" + ngonngu[g_language] + "/typeName3-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    threePlayerBackgroundSprite = std::make_unique<sf::Sprite>(*(threePlayerBackgroundTexture));


    sf::Vector2f threePlayerBackgroundScale(
        static_cast<float>(window.getSize().x) / threePlayerBackgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / threePlayerBackgroundTexture->getSize().y
    );
    threePlayerBackgroundSprite->setScale(threePlayerBackgroundScale);
    float startX = window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f + 100.0f;
    float startY = window.getSize().y * 0.3f;
    float spacing = 120.0f;


}

GameState ThreePlayerState::getNextState() {
    return nextState;
}


void ThreePlayerState::handleEvent(const sf::Event& event) {


    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
    {
        if (!buttonInputs.empty()) {
            buttonInputs[selectedButtonIndex].first->type(textEvent->unicode);
        }
    }
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {

        if (key->scancode == sf::Keyboard::Scancode::Up) {

            selectedButtonIndex = (selectedButtonIndex + buttonInputs.size()) % (1+buttonInputs.size());
            updateActiveInput();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Down) {

            selectedButtonIndex = (selectedButtonIndex + 1) % (1+buttonInputs.size());
            updateActiveInput();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {
            if (selectedButtonIndex == buttonInputs.size()) {
                cntInputs = 0;

                buttonInputs.clear();
                buttonInputs.push_back({ &user1,1 });
                buttonInputs.push_back({ &user2,2 });
                buttonInputs.push_back({ &user3,3 });

                selectedButtonIndex = 0;
                user1.setActive(true);
                buttonBack->setSelected(false);

                nextState = GameState::NewGame;
                return;
            }
            else buttonBack->setSelected(false);

            if (selectedButtonIndex != 3) {
                PlayerNameInput* currentInput = buttonInputs[selectedButtonIndex].first;
                std::string confirmedName = currentInput->getName();
                playerNames[buttonInputs[selectedButtonIndex].second] = confirmedName; std::cout << "Da luu ten: " << confirmedName << '\n';
                ++cntInputs;
                buttonInputs.erase(buttonInputs.begin() + selectedButtonIndex);
            }
           
            if (cntInputs == 3) {
                cntInputs = 0;

                buttonInputs.clear();
               
                buttonInputs.push_back({ &user1,1 });
                buttonInputs.push_back({ &user2,2 });
                buttonInputs.push_back({ &user3,3 });


                selectedButtonIndex = 0;

                player1Score = 0;
                player2Score = 0;
                player3Score = 0;


                nextState = GameState::Playing;
                return;

            }
            else {

                if (!buttonInputs.empty()) selectedButtonIndex = selectedButtonIndex % buttonInputs.size();
                updateActiveInput();
            }
            
        }

    }


    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {

        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);


            if (buttonBack->isMouseOver(mousePos)) {

                cntInputs = 0;

                buttonInputs.clear();
                buttonInputs.push_back({ &user1,1 });
                buttonInputs.push_back({ &user2,2 });
                buttonInputs.push_back({ &user3,3 });

                selectedButtonIndex = 0;

                nextState = GameState::NewGame;
            }
            else {
                bool inputClicked = false;

                for (int i = 0; i < buttonInputs.size(); ++i) {
                    if (buttonInputs[i].first->checkClick(mousePos)) {
                        selectedButtonIndex = i;
                        updateActiveInput();
                        inputClicked = true;
                        break;
                    }
                }


                if (!inputClicked) {
                    user1.setActive(false);
                    user2.setActive(false);
                    user3.setActive(false);
                }
            }
        }
    }
}

void ThreePlayerState::updateActiveInput() {
    if (buttonInputs.empty()) return;

    if (selectedButtonIndex == buttonInputs.size()) {
        buttonBack->setSelected(true);
        user1.setActive(false);
        user2.setActive(false);
        user3.setActive(false);
        return;
    }
    else buttonBack->setSelected(false);

    PlayerNameInput* input = buttonInputs[selectedButtonIndex].first;


    user1.setActive(false);
    user2.setActive(false);
    user3.setActive(false);

    
    if (input == &user1) user1.setActive(true);
    else if (input == &user2) user2.setActive(true);
    else if (input == &user3) user3.setActive(true);
}

void ThreePlayerState::update(sf::Vector2f mousePos) {

    buttonBack->update(mousePos);


}

void ThreePlayerState::render(sf::RenderTarget& target) {


    target.draw(*(threePlayerBackgroundSprite));


    target.draw(user1);
    target.draw(user2);
    target.draw(user3);
    target.draw(textUser1);
    target.draw(textUser2);
    target.draw(textUser3);

    buttonBack->render(target);


}