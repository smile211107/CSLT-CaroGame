#pragma once
#include "State.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
using namespace std;


// Biến toàn cục cho trạng thái nhạc
extern bool g_musicOn;
extern bool g_soundOn;
extern bool g_language;

extern std::string ngonngu[2];

class SettingsState : public State {
private:
    sf::RenderWindow& window;
    sf::Font& font;

    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;

    std::unique_ptr<Button> buttonMusic;
    std::unique_ptr<Button> buttonSound;
    std::unique_ptr<Button> buttonVN;
    std::unique_ptr<Button> buttonEN;
    std::unique_ptr<Button> buttonBack;
    sf::Texture onMusicTexture;
    sf::Texture offMusicTexture;
    sf::Texture onSoundTexture;
    sf::Texture offSoundTexture;
    sf::Texture offENTexture;
    sf::Texture offVNTexture;
    sf::Texture onENTexture;
    sf::Texture onVNTexture;
    sf::Texture buttonBackTexture;

    GameState nextState;
    vector<std::unique_ptr<Button>> buttonSettings;


public:
    // Constructor không cần truyền musicOn nữa
    SettingsState(sf::RenderWindow& window, sf::Font& font);

    void handleEvent(const sf::Event& event) override;
    void update(sf::Vector2f mousePos) override;
    void render(sf::RenderTarget& target) override;

    GameState getNextState() override;
    int selectedIdx = 0;
    bool getMusicSetting() const;
};
