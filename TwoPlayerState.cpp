#include "PlayerNameInput.h"
#include "SettingsState.h"
#include "TwoPlayerState.h"

#include "Button.h"
#include <iostream>
#include <memory>
using namespace std;
int cntInput = 0;
const sf::Vector2f PLAYER_BUTTON_SIZE = { 250.f, 50.f };


const sf::Vector2f INPUT_BOX_SIZE = { 450.0f, 60.0f };

TwoPlayerState::TwoPlayerState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),

    textUser1(font, "Player 1's name", 48),
    textUser2(font, "Player 2's name", 48),


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
    if (!buttonBackTexture.loadFromFile("Assets/image/"+ngonngu[g_language]+"/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.8f));

    gameMode = 2;
    menuInputs.push_back(&user1);
    menuInputs.push_back(&user2);
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
                           window.getSize().y * 0.6f });

    nextState = GameState::TwoPlayer;
    std::cout << "Da vao trang New Game (Player Select)!" << std::endl;
    twoPlayerBackgroundTexture = std::make_unique<sf::Texture>();


    if (!twoPlayerBackgroundTexture->loadFromFile("Assets/Image/"+ngonngu[g_language]+"/typeName2-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    twoPlayerBackgroundSprite = std::make_unique<sf::Sprite>(*(twoPlayerBackgroundTexture));


    sf::Vector2f TwoPlayerBackgroundScale(
        static_cast<float>(window.getSize().x) / twoPlayerBackgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / twoPlayerBackgroundTexture->getSize().y
    );
    twoPlayerBackgroundSprite->setScale(TwoPlayerBackgroundScale);
    float startX = window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f + 100.0f;
    float startY = window.getSize().y * 0.3f;
    float spacing = 120.0f;


}

GameState TwoPlayerState::getNextState() {
    return nextState;
}
void TwoPlayerState::updateActiveInput() {
    if (menuInputs.empty()) return;

    PlayerNameInput* input = menuInputs[selectedButtonIndex];


    user1.setActive(false);
    user2.setActive(false);


    if (input == &user1) user1.setActive(true);
    else if (input == &user2) user2.setActive(true);
}


void TwoPlayerState::handleEvent(const sf::Event& event) {


    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
    {

        if (!menuInputs.empty()) {
            menuInputs[selectedButtonIndex]->type(textEvent->unicode);
        }
    }


    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {

        if (key->scancode == sf::Keyboard::Scancode::Up) {
            if (menuInputs.empty()) return;
            selectedButtonIndex = (selectedButtonIndex - 1 + menuInputs.size()) % menuInputs.size();
            updateActiveInput();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Down) {
            if (menuInputs.empty()) return;
            selectedButtonIndex = (selectedButtonIndex + 1) % menuInputs.size();
            updateActiveInput();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {
            if (menuInputs.empty()) return;


            PlayerNameInput* currentInput = menuInputs[selectedButtonIndex];
            std::string confirmedName = currentInput->getName();


            playerNames[++cntInput] = confirmedName;
            std::cout << "Da luu ten: " << confirmedName << '\n';



            menuInputs.erase(menuInputs.begin() + selectedButtonIndex);

            if (cntInput == 2) {

                cntInput = 0;
                nextState = GameState::Playing;

            }
            else {

                if (!menuInputs.empty()) selectedButtonIndex = selectedButtonIndex % menuInputs.size();
                updateActiveInput();
            }
        }
    }


    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);

            if (buttonBack->isMouseOver(mousePos)) {
                std::cout << "Quay lai Main Menu!" << std::endl;
                nextState = GameState::NewGame;
            }

            else {
                bool inputClicked = false;

                for (int i = 0; i < menuInputs.size(); ++i) {
                    if (menuInputs[i]->checkClick(mousePos)) {
                        selectedButtonIndex = i;
                        updateActiveInput();
                        inputClicked = true;
                        break;
                    }
                }


                if (!inputClicked) {
                    user1.setActive(false);
                    user2.setActive(false);
                }
            }
        }
    }
}


void TwoPlayerState::update(sf::Vector2f mousePos) {

    buttonBack->update(mousePos);


}

void TwoPlayerState::render(sf::RenderTarget& target) {


    target.draw(*(twoPlayerBackgroundSprite));


    target.draw(user1);
    target.draw(user2);
    target.draw(textUser1);
    target.draw(textUser2);

    buttonBack->render(target);
}