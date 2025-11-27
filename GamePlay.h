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
    sf::Music gameplayMusic;
    sf::Clock m_moveClock;
    sf::Time m_moveThreshold;

    GameState nextState;
    
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int currentPlayer;
    bool isGameOver;
    bool firstGame = true;
  

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
    std::unique_ptr<sf::Texture> textureOToken;
    std::unique_ptr<sf::Texture> textureXToken;
    std::unique_ptr<sf::Texture> textureVToken;
    std::unique_ptr<sf::Texture> textureCard1;
    std::unique_ptr<sf::Texture> textureCard2;
    std::unique_ptr<sf::Texture> textureCard3;
    std::unique_ptr<sf::Texture> texturePauseBox;
    std::unique_ptr<sf::Texture> textureEndBox;
    std::unique_ptr<sf::Texture> endBackgroundTexture;

    std::unique_ptr<sf::Sprite> endBackgroundSprite;
    std::unique_ptr<sf::Sprite> spriteEndEffect;
    std::unique_ptr<sf::Sprite> spriteOIcon;
    std::unique_ptr<sf::Sprite> spriteXIcon;
    std::unique_ptr<sf::Sprite> spriteVIcon;
    std::unique_ptr<sf::Sprite> spriteXToken;
    std::unique_ptr<sf::Sprite> spriteOToken;
    std::unique_ptr<sf::Sprite> spriteVToken;
    std::unique_ptr<sf::Sprite> spriteCard1;
    std::unique_ptr<sf::Sprite> spriteCard2;
    std::unique_ptr<sf::Sprite> spriteCard3;
    std::unique_ptr<sf::Sprite> spritePauseBox;
    std::unique_ptr<sf::Sprite> spriteEndBox;

    std::vector<std::unique_ptr<sf::Sprite>> pieces;
    sf::Text score1;
    sf::Text score2;
    sf::Text score3;

    // BUTTON END GAME
    std::vector<std::unique_ptr<Button>> endButtons;

    std::unique_ptr<Button> buttonNewGame;
    std::unique_ptr<Button> buttonSaveGame;
    std::unique_ptr<Button> buttonExit;
    sf::Texture buttonNewGameTexture;
    sf::Texture buttonSaveGameTexture;
    sf::Texture buttonExitTexture;
    

    //BUTTON PAUSE GAME
    std::vector<std::unique_ptr<Button>> pauseButtons;
    std::unique_ptr<Button> buttonPauseSave;
    std::unique_ptr<Button> buttonPauseResume;
    std::unique_ptr<Button> buttonPauseRestart;
    std::unique_ptr<Button> buttonPauseQuit;

    sf::Texture buttonPauseSaveTexture;
    sf::Texture buttonPauseResumeTexture;
    sf::Texture buttonPauseRestartTexture;
    sf::Texture buttonPauseQuitTexture;


    std::unique_ptr<sf::Sprite> buttonPauseSaveSprite;
    std::unique_ptr<sf::Sprite> buttonPauseReturnSprite;
    std::unique_ptr<sf::Sprite> buttonPauseRestartSprite;
    std::unique_ptr<sf::Sprite> buttonPauseQuitSprite;

    

    int selectedButtonIndex;
    float cellSize;
    sf::Music winSound;
    sf::Music playSound;

    sf::Music playSoundWrong;
};
extern int result;
extern vector<pair<pair<int, int>, int>> track;