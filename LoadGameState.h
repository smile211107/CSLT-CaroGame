#pragma once
#include "State.h"
#include "Button.h"
#include "TextButton.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
extern std::string selectedFile;
struct SaveFileInfo {
    std::string filename; 
    std::string gameName;
    std::string date;      
    int mode = 2;               
    std::string score;      
    long long timestamp = 1;    
};

class LoadState : public State {
public:
    LoadState(sf::RenderWindow& window, sf::Font& font);

    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

    std::string getSelectedFile() const;

private:
    sf::RenderWindow& window;
    sf::Font& font;
    GameState nextState;
    TextButton fileNo1, fileNo2, fileNo3, fileNo4, fileNo5;
    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;
    int selection;
    std::unique_ptr<Button> buttonBack;
    sf::Texture buttonBackTexture;

    std::vector<SaveFileInfo> saveFiles;

    std::vector<std::unique_ptr<Button>> slotButtons;

    std::vector<sf::Text> slotTexts;


    void loadSavedFilesFromDisk();
    void setupUISlots();
};
