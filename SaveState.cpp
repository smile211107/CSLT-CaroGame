#include "PlayerNameInput.h"
#include "SaveState.h"
#include "SettingsState.h"
#include "Button.h"
#include "Game.h"
#include "SaveAndLoad.h"
#include <iostream>
#include <memory>
using namespace std;
const sf::Vector2f PLAYER_BUTTON_SIZE = { 250.f, 50.f };


const sf::Vector2f INPUT_BOX_SIZE = { 450.0f, 60.0f };

SaveState::SaveState(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),

    fileName(font, "File name", 48),

    fileInput(

        { window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f,

        window.getSize().y * 0.6f },
        INPUT_BOX_SIZE,
        font
    )


{
    if (!buttonBackTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/return-button.png")) {
        std::cout << "khong the mo buttonBack" << '\n';
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y * 0.92f));

    fileInput.setActive(true);
    sf::FloatRect textBounds = this->fileName.getLocalBounds();

    textBounds = this->fileName.getLocalBounds();
    this->fileName.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f });
    fileName.setPosition({ window.getSize().x / 2.0f,
                           window.getSize().y * 0.55f });

    this->nextState = GameState::Saving;
    std::cout << "Da vao trang Save Game!" << std::endl;
    this->saveBackgroundTexture = std::make_unique<sf::Texture>();


    if (!this->saveBackgroundTexture->loadFromFile("Assets/Image/" + ngonngu[g_language] + "/save-background.png")) {
        std::cout << "khong the mo menubackground" << '\n';
    }

    this->saveBackgroundSprite = std::make_unique<sf::Sprite>(*(this->saveBackgroundTexture));


    sf::Vector2f BackgroundScale(
        static_cast<float>(window.getSize().x) / this->saveBackgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / this->saveBackgroundTexture->getSize().y
    );
    this->saveBackgroundSprite->setScale(BackgroundScale);
    float startX = window.getSize().x / 2.0f - INPUT_BOX_SIZE.x / 2.0f + 100.0f;
    float startY = window.getSize().y * 0.3f;
    float spacing = 120.0f;


}

GameState SaveState::getNextState() {
    return this->nextState;
}
void SaveState::updateActiveInput() {


    fileInput.setActive(true);


}


void SaveState::handleEvent(const sf::Event& event) {


    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
    {

        fileInput.type(textEvent->unicode);

    }


    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {


        if (key->scancode == sf::Keyboard::Scancode::Enter) {


            std::string confirmedName = fileInput.getName();


            std::cout << "Da luu ten: " << confirmedName << '\n';
            writeFile(confirmedName);
            nextState = GameState::MainMenu;


        }
    }


    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = this->window.mapPixelToCoords(mouseEvent->position);

            if (buttonBack->isMouseOver(mousePos)) {
                std::cout << "Quay lai gameplay!" << std::endl;
                previousState = GameState::Saving;
                nextState = GameState::Playing;
            }

            /*else {
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
            }*/
        }
    }
}


void SaveState::update(sf::Vector2f mousePos) {

    buttonBack->update(mousePos);


}

void SaveState::render(sf::RenderTarget& target) {


    target.draw(*(this->saveBackgroundSprite));


    target.draw(fileInput);
    target.draw(fileName);

    buttonBack->render(target);
}