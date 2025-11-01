#include "menu.hpp"
#include "gameplay.hpp"
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Game Caro", sf::Style::Default);
    // while (window.isOpen()) {
        runMenu(window);
        game(window);
    // }
    return 0;
}