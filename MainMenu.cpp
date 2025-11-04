#include "MainMenu.h"
#include <iostream>
using namespace sf;

MainMenuState::MainMenuState() :
    backgroundSprite(backgroundTexture),
    newGameButton(newGameButtonTexture),
    loadGameButton(loadGameButtonTexture),
    tutorialButton(tutorialButtonTexture),
    settingsButton(settingsButtonTexture),
    aboutUsButton(aboutButtonTexture),
    quitButton(quitButtonTexture)
{
    //Load anh
    backgroundTexture.loadFromFile("assets\\menu-background.png");
    newGameButtonTexture.loadFromFile("assets\\button\\newGame-button-vn.png");
    loadGameButtonTexture.loadFromFile("assets\\button\\loadGame-button-vn.png");
    tutorialButtonTexture.loadFromFile("assets\\button\\tutorial-button-vn.png");
    settingsButtonTexture.loadFromFile("assets\\button\\settings-button-vn.png");
    aboutButtonTexture.loadFromFile("assets\\button\\aboutUs-button-vn.png");
    quitButtonTexture.loadFromFile("assets\\button\\exit-button-vn.png");

    //Tai anh vao Sprite
    backgroundSprite.setTexture(backgroundTexture);
    newGameButton.setTexture(newGameButtonTexture);
    loadGameButton.setTexture(loadGameButtonTexture);
    settingsButton.setTexture(settingsButtonTexture);
    tutorialButton.setTexture(tutorialButtonTexture);
    aboutUsButton.setTexture(aboutButtonTexture);
    quitButton.setTexture(quitButtonTexture);


    //setTextureRect cho tung Sprite
    int tmpx = newGameButtonTexture.getSize().x, tmpy = newGameButtonTexture.getSize().y;
    Vector2i pos = {0, 0}, size = {tmpx, tmpy};
    newGameButton.setTextureRect(Rect<int>::Rect(pos, size));
    tmpx = backgroundTexture.getSize().x;  tmpy = backgroundTexture.getSize().y; size = { tmpx, tmpy };
    backgroundSprite.setTextureRect(Rect<int>::Rect(pos, size));
    tmpx = loadGameButtonTexture.getSize().x;  tmpy = loadGameButtonTexture.getSize().y; size = { tmpx, tmpy };
    loadGameButton.setTextureRect(Rect<int>::Rect(pos, size));
    tmpx = settingsButtonTexture.getSize().x;  tmpy = settingsButtonTexture.getSize().y; size = { tmpx, tmpy };
    settingsButton.setTextureRect(Rect<int>::Rect(pos, size));
    tmpx = tutorialButtonTexture.getSize().x;  tmpy = tutorialButtonTexture.getSize().y; size = { tmpx, tmpy };
    tutorialButton.setTextureRect(Rect<int>::Rect(pos, size));
    tmpx = aboutButtonTexture.getSize().x;  tmpy = aboutButtonTexture.getSize().y; size = { tmpx, tmpy };
    aboutUsButton.setTextureRect(Rect<int>::Rect(pos, size));
    tmpx = quitButtonTexture.getSize().x;  tmpy = quitButtonTexture.getSize().y; size = { tmpx, tmpy };
    quitButton.setTextureRect(Rect<int>::Rect(pos, size));
    

    setupLayout(1920, 1080);
 
}

MainMenuState::~MainMenuState() {
    std::cout << "Huy menu state\n";
}

void MainMenuState::setupLayout(unsigned int windowWidth, unsigned int windowHeight) {
    float windowCenterX = windowWidth / 2.0f;
    float buttonSpacing = 20.f, buttonsTopMargin = 433.f;

    float scaleX = static_cast<float>(windowWidth) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(windowHeight) / backgroundTexture.getSize().y;
    backgroundSprite.setScale({ scaleX, scaleY });


    newGameButton.setOrigin({ newGameButton.getLocalBounds().size.x / 2.0f, 0.f });
    loadGameButton.setOrigin({ loadGameButton.getLocalBounds().size.x / 2.0f, 0.f });
    quitButton.setOrigin({ quitButton.getLocalBounds().size.x / 2.0f, 0.f });
    settingsButton.setOrigin({ settingsButton.getLocalBounds().size.x / 2.0f, 0.f });
    tutorialButton.setOrigin({ tutorialButton.getLocalBounds().size.x / 2.0f, 0.f });
    aboutUsButton.setOrigin({ aboutUsButton.getLocalBounds().size.x / 2.0f, 0.f });

    newGameButton.setPosition({ windowCenterX, buttonsTopMargin });
    loadGameButton.setPosition({
        windowCenterX,
        newGameButton.getPosition().y + newGameButton.getLocalBounds().size.y + buttonSpacing
        });
    tutorialButton.setPosition({
        windowCenterX,
        loadGameButton.getPosition().y + loadGameButton.getLocalBounds().size.y + buttonSpacing
        });
    settingsButton.setPosition({
        windowCenterX,
        tutorialButton.getPosition().y + tutorialButton.getLocalBounds().size.y + buttonSpacing
        });
    aboutUsButton.setPosition({
        windowCenterX,
        settingsButton.getPosition().y + settingsButton.getLocalBounds().size.y + buttonSpacing
        });
    quitButton.setPosition({
        windowCenterX,
        aboutUsButton.getPosition().y + aboutUsButton.getLocalBounds().size.y + buttonSpacing
        });


}

void MainMenuState::handleInput(const Event& event, RenderWindow& window) {
    if (event.is <Event::MouseButtonPressed>()) {
        if (event.getIf <Event::MouseButtonPressed>()->button == Mouse::Button::Left) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            if (newGameButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "Da nhan nut New Game\n";
            }
            else if (loadGameButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "Da nhan nut Load Game\n";
            }
            else if (settingsButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "Da nhan nut Settings\n";
            }
            else if (tutorialButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "Da nhan nut Tutorial\n";
            }
            else if (aboutUsButton.getGlobalBounds().contains(mousePos)) {
                m_nextState = StateType::Guide;
            }
            else if (quitButton.getGlobalBounds().contains(mousePos)) {
                window.close();
            }
        }
    }
}

void MainMenuState::update(Time dt, RenderWindow& window) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    if (newGameButton.getGlobalBounds().contains(mousePos)) {
        newGameButton.setScale({ m_buttonScaleHover, m_buttonScaleHover });
    }
    else {
        newGameButton.setScale({ m_buttonScaleNormal, m_buttonScaleNormal });
    }
    if (loadGameButton.getGlobalBounds().contains(mousePos)) {
        loadGameButton.setScale({ m_buttonScaleHover, m_buttonScaleHover });
    }
    else {
        loadGameButton.setScale({ m_buttonScaleNormal, m_buttonScaleNormal });
    }

    if (settingsButton.getGlobalBounds().contains(mousePos)) {
        settingsButton.setScale({ m_buttonScaleHover, m_buttonScaleHover });
    }
    else {
        settingsButton.setScale({ m_buttonScaleNormal, m_buttonScaleNormal });
    }

    if (tutorialButton.getGlobalBounds().contains(mousePos)) {
        tutorialButton.setScale({ m_buttonScaleHover, m_buttonScaleHover });
    }
    else {
        tutorialButton.setScale({ m_buttonScaleNormal, m_buttonScaleNormal });
    }

    if (aboutUsButton.getGlobalBounds().contains(mousePos)) {
        aboutUsButton.setScale({ m_buttonScaleHover, m_buttonScaleHover });
    }
    else {
        aboutUsButton.setScale({ m_buttonScaleNormal, m_buttonScaleNormal });
    }

    if (quitButton.getGlobalBounds().contains(mousePos)) {
        quitButton.setScale({ m_buttonScaleHover, m_buttonScaleHover });
    }
    else {
        quitButton.setScale({ m_buttonScaleNormal, m_buttonScaleNormal });
    }
}

void MainMenuState::draw(RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(newGameButton);
    window.draw(loadGameButton);
    window.draw(settingsButton);
    window.draw(tutorialButton);
    window.draw(aboutUsButton);
    window.draw(quitButton);
}