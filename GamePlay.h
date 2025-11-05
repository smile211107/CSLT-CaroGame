#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h" 
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include<SFML/Audio.hpp>
using namespace std;

const int BOARD_WIDTH = 13;
const int BOARD_HEIGHT = 13;

const float CURSOR_THICKNESS = 4.0f;

class Gameplay : public State {
public:
    Gameplay(sf::RenderWindow& window, sf::Font& font);

    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;
   
    void newGame();
    void updateCursorShapePosition();
    
private:

    sf::RenderWindow& window;
    sf::Font& font;
    std::unique_ptr<sf::Texture> gameplayBackgroundTexture;
    std::unique_ptr<sf::Sprite> gameplayBackgroundSprite;
    sf::Music backgroundMusic;
    sf::Clock m_moveClock;
    sf::Time m_moveThreshold;

    GameState nextState;
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int currentPlayer;
    bool isGameOver;
    int player1Score;
    int player2Score;
    int player3Score;
  
    int cursorX;
    int cursorY;
    sf::RectangleShape cursorShape;


    std::unique_ptr<sf::Texture> textureTwoDraw;
    std::unique_ptr<sf::Texture> textureThreeDraw;
    std::unique_ptr<sf::Texture> textureOIcon;
    std::unique_ptr<sf::Texture> textureXIcon;
    std::unique_ptr<sf::Texture> textureVIcon;
    std::unique_ptr<sf::Texture> textureOWin;
    std::unique_ptr<sf::Texture> textureXWin;
    std::unique_ptr<sf::Texture> textureVWin;
    std::unique_ptr<sf::Texture> textureCard1;
    std::unique_ptr<sf::Texture> textureCard2;
    std::unique_ptr<sf::Texture> textureCard3;


    std::unique_ptr<sf::Sprite> spriteEndEffect;
    std::unique_ptr<sf::Sprite> spriteOIcon;
    std::unique_ptr<sf::Sprite> spriteXIcon;
    std::unique_ptr<sf::Sprite> spriteVIcon;
    std::unique_ptr<sf::Sprite> spriteCard1;
    std::unique_ptr<sf::Sprite> spriteCard2;
    std::unique_ptr<sf::Sprite> spriteCard3;

    std::vector<std::unique_ptr<sf::Sprite>> pieces;
    sf::Text score1;
    sf::Text score2;
    sf::Text score3;

    float cellSize;
};
extern int result;