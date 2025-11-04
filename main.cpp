#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "BaseState.h"
#include "MainMenu.h"
#include "GuideState.h"

using namespace sf;
using namespace std;

int main()
{
    VideoMode desktopMode = VideoMode::getDesktopMode();
    Vector2u screenSize = desktopMode.size;
    RenderWindow window(VideoMode(screenSize), "Example Game", sf::Style::None);




    Clock clock;
    unique_ptr<BaseState> currentState;
    currentState = make_unique<MainMenuState>();


    while (window.isOpen())
    S_LOOP:
    {
        Time dt = clock.restart();
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            currentState->handleInput(*event, window);
        }
        currentState->update(dt);

        StateType next = currentState->getNextState();
        if (next != StateType::None) {
            currentState->resetNextState();

            switch (next) {
            case StateType::MainMenu:
                currentState = std::make_unique<MainMenuState>();
                break;
            case StateType::Guide:
                currentState = std::make_unique<GuideState>();
                break;
            case StateType::Exit:
                window.close();
                break;
            }

            goto S_LOOP;
        }

        window.clear();
        currentState->draw(window);
        window.display();
    }

    
}