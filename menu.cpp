#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "gameplay.hpp"

struct Button {
    sf::Sprite sprite;
    std::string name;

    Button(sf::Texture& texture, const sf::Vector2f& pos, const std::string& n)
        : name(n), sprite(texture)
    {
        sprite.setTexture(texture);
        auto bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        sprite.setPosition(pos);
        sprite.setScale({1.f, 1.f});
        std::cout << "📍 Button " << name << " at " << pos.x << ", " << pos.y << std::endl;
    }

    bool isClicked(const sf::Vector2f& mousePos) const {
        return sprite.getGlobalBounds().contains(mousePos);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }
};

void runMenu(sf::RenderWindow& window) {
    // --- Background ---
    // #include <filesystem>
    // std::cout << "🧭 Working directory: " << std::filesystem::current_path() << std::endl;

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/background/menu-screen.png")) {
        std::cerr << "⚠️ Không thể tải background\n";
    }
    sf::Sprite background(bgTexture);

    // --- Tải toàn bộ texture ---
    std::vector<sf::Texture> buttonTextures(6);
    std::vector<std::string> filenames = {
        "assets/button/newGame-button-vn.png",
        "assets/button/loadGame-button-vn.png",
        "assets/button/settings-button-vn.png",
        "assets/button/tutorial-button-vn.png",
        "assets/button/aboutUs-button-vn.png",
        "assets/button/exit-button-vn.png"
    };
    std::vector<std::string> names = {
        "New Game", "Load Game", "Settings", "Tutorial", "About Us", "Exit"
    };

    for (size_t i = 0; i < filenames.size(); ++i) {
        if (!buttonTextures[i].loadFromFile(filenames[i])) {
            std::cerr << "⚠️ Không thể tải: " << filenames[i] << std::endl;
        } else {
            std::cout << "✅ Loaded: " << filenames[i] << std::endl;
        }
    }

    // --- Tạo nút ---
    std::vector<Button> buttons;
    float windowWidth = 1920.f;
    float windowHeight = 1080.f;

    float gap = 20.f;
    float buttonHeight = 87.f;  // từ ảnh của bạn
    float totalHeight = 6 * buttonHeight + 5 * gap;
    float startY = (windowHeight - totalHeight) / 2.f;

    for (size_t i = 0; i < buttonTextures.size(); ++i) {
        float posX = windowWidth / 2.f;
        float posY = startY + i * (buttonHeight + gap) + buttonHeight / 2.f;
        buttons.emplace_back(buttonTextures[i], sf::Vector2f(posX, posY), names[i]);
    }

    // --- Vòng lặp ---
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse && mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(static_cast<float>(mouse->position.x),
                                          static_cast<float>(mouse->position.y));
                    for (const auto& btn : buttons) {
                        if (btn.isClicked(mousePos)) {
                            std::cout << "👉 Clicked: " << btn.name << std::endl;
                            if (btn.name == "Exit")
                                window.close();
                            else if (btn.name == "New Game")
                            {
                                std::cout << "GAMEEE\n";
                                return;
                                game();
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        for (const auto& btn : buttons)
            btn.draw(window);
        window.display();
    }
}
