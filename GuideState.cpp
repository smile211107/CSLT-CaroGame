#include "GuideState.h"
#include <iostream>
using namespace sf;

GuideState::GuideState() :
    guideBackground(guidebgTexture),
    okButton(okButtonTexture)
{
    guidebgTexture.loadFromFile("assets\\about-background-vn.png");
    okButtonTexture.loadFromFile("assets\\button\\return-button-vn.png");

    guideBackground.setTexture(guidebgTexture);
    okButton.setTexture(okButtonTexture);
    guideBackground.setPosition({ 0, 0 });

    int tmpx = guidebgTexture.getSize().x, tmpy = guidebgTexture.getSize().y;
    Vector2i pos = { 0, 0 }, size = { tmpx, tmpy };
    guideBackground.setTextureRect(Rect<int>::Rect(pos, size));
    tmpx = okButtonTexture.getSize().x;  tmpy = okButtonTexture.getSize().y; size = { tmpx, tmpy };
    okButton.setTextureRect(Rect<int>::Rect(pos, size));


    unsigned int windowWidth = 1920; 
    unsigned int windowHeight = 1080; 
    float windowCenterX = windowWidth / 2.0f;

    float scaleX = static_cast<float>(windowWidth) / guidebgTexture.getSize().x;
    float scaleY = static_cast<float>(windowHeight) / guidebgTexture.getSize().y;
    guideBackground.setScale({ scaleX, scaleY });


    okButton.setOrigin({ okButton.getLocalBounds().size.x / 2.0f, 0.f});
    okButton.setPosition({ windowCenterX, 895.f });
}

GuideState::~GuideState() {
    std::cout << "Huy GuideState\n";
}

void GuideState::handleInput(const Event& event, RenderWindow& window) {
    if (event.is <Event::MouseButtonPressed>()) {
        if (event.getIf <Event::MouseButtonPressed>()->button == Mouse::Button::Left) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            if (okButton.getGlobalBounds().contains(mousePos)) {
                std::cout << "Da nhan nut OK (quay ve Menu)\n";
                m_nextState = StateType::MainMenu;
            }
        }
    }
}

void GuideState::update(Time dt, RenderWindow& window) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    if (okButton.getGlobalBounds().contains(mousePos)) {
        okButton.setScale({ m_buttonScaleHover, m_buttonScaleHover });
    }
    else {
        okButton.setScale({ m_buttonScaleNormal, m_buttonScaleNormal });
    }
}

void GuideState::draw(RenderWindow& window) {
    window.draw(guideBackground);
    window.draw(okButton);
}