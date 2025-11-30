#include "GameState.h"
#include "Game.h"
#include "LoadGameState.h"
#include "GamePlay.h"
#include "Button.h"
#include "PlayerNameInput.h"
#include "SettingsState.h"
#include <iostream>
#include <vector>
// #include <conio.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
int turn = 0;
int result = 0;
bool isPause = false, endGame = false;
const int margin = 30, playerSize = 50;
const sf::Vector2f BUTTON_SIZE = { 400.0F, 60.f };
const float GAP = 120.0f;
float length = 0;
vector<pair<pair<int, int>, int>> track;
sf::RectangleShape line(sf::Vector2f(length, 5.f));
pair<int, int> pointOne = { 1,1 };
sf::Vector2f startPoint({ 0,0 });
int player1Score = 0;
int player2Score = 0;
int player3Score = 0;

uint8_t mainGameBoard[13][13] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
};
//Ham tra ve toa do thuc trong window
sf::Vector2f cord(int y, int x)
{
    float cx = static_cast<float>(x) * 80 - 10;
    float cy = static_cast<float>(y) * 80 - 10;
    sf::Vector2f cordinate({ cx,cy });
    return cordinate;
}
int checkRow(int y, int x)
{
    int res = 1, start = 1, end = 12;
    if (x > 4) start = x - 4;
    if (x < 9) end = x + 4;
    pointOne.first = y;
    pointOne.second = start;
    for (int i = start; i <= end; i++)
    {
        if (mainGameBoard[y][i] == mainGameBoard[y][i - 1] && mainGameBoard[y][i] == mainGameBoard[y][x] && mainGameBoard[y][i] > 0) res++;
        else
        {
            res = 1;
            pointOne.second = i;
        }
        if (res > 4)
        {
            line.setSize(sf::Vector2f(350, 10));
            line.setOrigin({ 0,5 });
            return mainGameBoard[y][x];
        }
    }
    return 0;
}

int checkCol(int y, int x)
{
    int res = 1, start = 1, end = 12;
    if (y > 4) start = y - 4;
    if (y < 9) end = y + 4;
    pointOne.second = x;
    pointOne.first = start;
    for (int i = start; i <= end; i++)
    {
        if (mainGameBoard[i][x] == mainGameBoard[i - 1][x] && mainGameBoard[i][x] == mainGameBoard[y][x] && mainGameBoard[i][x] > 0) res++;
        else
        {
            res = 1;
            pointOne.first = i;
        }
        if (res > 4)
        {
            line.setSize(sf::Vector2f(10, 350));
            line.setOrigin({ 5,0 });
            return mainGameBoard[y][x];
        }
    }
    return 0;
}

int checkDia2(int y, int x)
{
    int i = y, j = x, res = 1;
    if (y + x < 12)
    {
        i = 2;
        j = y + x - 2;
    }
    else
    {
        i = x + y - 11;
        j = 11;
    }
    pointOne.first = i - 1;
    pointOne.second = j + 1;
    while (i <= 12 && j >= 1)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j + 1] && mainGameBoard[i][j] == mainGameBoard[y][x] && mainGameBoard[i][j] > 0) res++;
        else
        {
            res = 1;
            pointOne.first = i;
            pointOne.second = j;
        }
        if (res > 4)
        {
            line.setSize(sf::Vector2f(495, 10));
            line.setOrigin({ 0,5 });
            line.rotate(sf::degrees(135));
            return mainGameBoard[i][j];
        }
        i++; j--;
    }
    return 0;
}

int checkDia1(int y, int x)
{
    int i = y, j = x, res = 1;
    if (y > x)
    {
        i = y - x + 2;
        j = 2;
    }
    else
    {
        i = 2;
        j = x - y + 2;
    }
    pointOne.first = i - 1;
    pointOne.second = j - 1;
    while (i <= 12 && j <= 12)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j - 1] && mainGameBoard[i][j] == mainGameBoard[y][x] && mainGameBoard[i][j] > 0) res++;
        else
        {
            res = 1;
            pointOne.first = i;
            pointOne.second = j;
        }
        if (res > 4)
        {
            line.setSize(sf::Vector2f(495, 10));
            line.setOrigin({ 0,5 });
            line.rotate(sf::degrees(45));
            return mainGameBoard[i][j];
        }
        i++; j++;
    }
    return 0;
}

int checkWin(int y, int x, int checkNum)
{
    if (checkNum == checkRow(y, x) || checkNum == checkCol(y, x) || checkNum == checkDia1(y, x) || checkNum == checkDia2(y, x))
    {

        return checkNum;
    }
    return 0;
}

Gameplay::Gameplay(sf::RenderWindow& window, sf::Font& font)
    : window(window),
    font(font),
    score1(font, playerNames[1] + "\nScore: " + to_string(player1Score) + "     Turn: " + to_string(cntTurn1), 48),
    score2(font, playerNames[2] + "\nScore: " + to_string(player2Score) + "     Turn: " + to_string(cntTurn2), 48),
    score3(font, playerNames[3] + "\nScore: " + to_string(player3Score) + "     Turn: " + to_string(cntTurn3), 48)


{
    if (!buttonPauseSaveTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/save-button.png")) {
        std::cout << "khong the mo buttonPauseSaveTexture" << '\n';
    }
    if (!buttonPauseResumeTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/resume-button.png")) {
        std::cout << "khong the mo buttonPauseSaveTexture" << '\n';
    }
    if (!buttonPauseQuitTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/quit-button.png")) {
        std::cout << "khong the mo buttonPauseSaveTexture" << '\n';
    }
    if (!buttonPauseRestartTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/restart-button.png")) {
        std::cout << "khong the mo buttonPauseSaveTexture" << '\n';
    }
    if (!buttonNewGameTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/nextRound-button.png")) {
        std::cout << "khong the mo nextRoundtexture" << '\n';
    }
    if (!buttonSaveGameTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/save-button.png")) {
        std::cout << "khong the mo savegametexture" << '\n';
    }
    if (!buttonExitTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/quit-button.png")) {
        std::cout << "khong the mo quittexture" << '\n';
    }
    //BUTTON PAUSE GAME
    buttonPauseSave = std::make_unique<Button>(buttonPauseSaveTexture,
        sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.35f + (GAP * 0) + 30));
    buttonPauseResume = std::make_unique<Button>(buttonPauseResumeTexture,
        sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.35f + (GAP * 1) + 30));
    buttonPauseRestart = std::make_unique<Button>(buttonPauseRestartTexture,
        sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.35f + (GAP * 2) + 30));
    buttonPauseQuit = std::make_unique<Button>(buttonPauseQuitTexture,
        sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.35f + (GAP * 3) + 30));

    pauseButtons.push_back(move(buttonPauseSave));
    pauseButtons.push_back(move(buttonPauseResume));
    pauseButtons.push_back(move(buttonPauseRestart));
    pauseButtons.push_back(move(buttonPauseQuit));
    pauseButtons[selectedButtonIndex]->setSelected(true);


    buttonNewGame = std::make_unique<Button>(buttonNewGameTexture,
        sf::Vector2f(window.getSize().x * 0.75f, window.getSize().y * 0.5f + (GAP * 1) + 60));
    buttonSaveGame = std::make_unique<Button>(buttonSaveGameTexture,
        sf::Vector2f(window.getSize().x * 0.75f, window.getSize().y * 0.5f + (GAP * 2) + 60));
    buttonExit = std::make_unique<Button>(buttonExitTexture,
        sf::Vector2f(window.getSize().x * 0.75f, window.getSize().y * 0.5f + (GAP * 3) + 60));

    endButtons.push_back(move(buttonNewGame));
    endButtons.push_back(move(buttonSaveGame));
    endButtons.push_back(move(buttonExit));



    selectedButtonIndex = 0;
    endButtons[selectedButtonIndex]->setSelected(true);
    nextState = GameState::Playing;
    textureCard1 = std::make_unique<sf::Texture>();
    textureCard2 = std::make_unique<sf::Texture>();
    textureCard3 = std::make_unique<sf::Texture>();
    textureOToken = std::make_unique<sf::Texture>();
    textureXToken = std::make_unique<sf::Texture>();
    textureVToken = std::make_unique<sf::Texture>();
    endBackgroundTexture = std::make_unique<sf::Texture>();

    if (!endBackgroundTexture->loadFromFile("Assets/image/endBox.png")) {
        std::cout << "khong the mo end box" << '\n';
    }
    if (!winSound.openFromFile("assets/audio/sound-win.mp3")) {

        std::cout << "khong tai duoc am thanh";
    }
    if (!playSoundWrong.openFromFile("assets/audio/playSound.ogg")) {

        std::cout << "khong tai duoc am thanh";
    }
    if (!playSound.openFromFile("assets/audio/playSoundWrong.ogg")) {

        std::cout << "khong tai duoc am thanh";
    }
    endBackgroundSprite = std::make_unique<sf::Sprite>(*(endBackgroundTexture));
    if (!textureCard1->loadFromFile("Assets/image/player1-card.png")) {
        std::cout << "khong tai duoc card 1";
    }
    if (!textureCard2->loadFromFile("Assets/image/player2-card.png")) {
        std::cout << "khong tai duoc card 2";
    }
    if (!textureCard3->loadFromFile("Assets/image/player3-card.png")) {
        std::cout << "khong tai duoc card 3";
    }
    if (!textureXToken->loadFromFile("Assets/image/player1-token.png")) {
        std::cout << "khong tai duoc card 1";
    }
    if (!textureOToken->loadFromFile("Assets/image/player2-token.png")) {
        std::cout << "khong tai duoc card 2";
    }
    if (!textureVToken->loadFromFile("Assets/image/player3-token.png")) {
        std::cout << "khong tai duoc card 3";
    }
    if (!gameplayMusic.openFromFile("assets/audio/gameplayAudio.mp3")) {

        std::cout << "khong tai duoc am thanh";
    }
    endBackgroundSprite->setPosition({ window.getSize().x * 0.5f + 100, window.getSize().y * 0.6f });
    spriteCard1 = std::make_unique<sf::Sprite>(*(textureCard1));
    spriteCard2 = std::make_unique<sf::Sprite>(*(textureCard2));
    spriteCard3 = std::make_unique<sf::Sprite>(*(textureCard3));
    spriteXToken = std::make_unique<sf::Sprite>(*(textureXToken));
    spriteOToken = std::make_unique<sf::Sprite>(*(textureOToken));
    spriteVToken = std::make_unique<sf::Sprite>(*(textureVToken));


    sf::FloatRect spriteBounds = spriteCard1->getLocalBounds();

    spriteCard1->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });
    spriteCard2->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });
    spriteCard3->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });


    spriteCard1->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.1f });

    spriteCard2->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.3f });
    spriteCard3->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.5f });
    spriteXToken->setPosition({ window.getSize().x * 0.75f + 350.0f,
                                     window.getSize().y * 0.1f });

    spriteOToken->setPosition({ window.getSize().x * 0.75f + 350.0f,
                                     window.getSize().y * 0.3f });
    spriteVToken->setPosition({ window.getSize().x * 0.75f + 350.0f,
                                     window.getSize().y * 0.5f });
    score1.setPosition({ window.getSize().x * 0.65f,
                                     window.getSize().y * 0.03f });
    score2.setPosition({ window.getSize().x * 0.65f,
                                    window.getSize().y * 0.23f });
    score3.setPosition({ window.getSize().x * 0.65f,
                                  window.getSize().y * 0.43f });


    gameplayMusic.setLooping(true);
    gameplayMusic.setVolume(g_musicOn * 30);
    gameplayMusic.play();

    gameplayBackgroundTexture = std::make_unique<sf::Texture>();
    if (!gameplayBackgroundTexture->loadFromFile("Assets/Image/inGame-background.png")) {
        std::cout << "khong the mo background gameplay" << '\n';

    }
    gameplayBackgroundSprite = std::make_unique<sf::Sprite>(*(gameplayBackgroundTexture));

    sf::Vector2f backgroundScale(
        static_cast<float>(window.getSize().x) / gameplayBackgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / gameplayBackgroundTexture->getSize().y
    );
    gameplayBackgroundSprite->setScale(backgroundScale);

    cellSize = 80;



    textureTwoDraw = std::make_unique<sf::Texture>();
    textureThreeDraw = std::make_unique<sf::Texture>();
    textureXIcon = std::make_unique<sf::Texture>();
    textureOIcon = std::make_unique<sf::Texture>();
    textureVIcon = std::make_unique<sf::Texture>();
    textureXWin = std::make_unique<sf::Texture>();
    textureOWin = std::make_unique<sf::Texture>();
    textureVWin = std::make_unique<sf::Texture>();
    texturePauseBox = std::make_unique<sf::Texture>();
    if (!texturePauseBox->loadFromFile("Assets/image/" + ngonngu[g_language] + "/pause-box.png")) {
        std::cout << "khong tai duoc pause box" << '\n';

    };
    if (!textureOIcon->loadFromFile("Assets/image/o-icon.png")) {
        std::cout << "khong tai duoc icon o" << '\n';

    };
    if (!textureXIcon->loadFromFile("Assets/image/x-icon.png")) {
        std::cout << "khong tai duoc icon x" << '\n';

    };
    if (!textureVIcon->loadFromFile("Assets/image/v-icon.png")) {
        std::cout << "khong tai duoc icon x" << '\n';

    };
    if (!textureOWin->loadFromFile("Assets/image/" + ngonngu[g_language] + "/o-win.png")) {
        std::cout << "khong tai duoc win o" << '\n';

    };
    if (!textureXWin->loadFromFile("Assets/image/" + ngonngu[g_language] + "/x-win.png")) {
        std::cout << "khong tai duoc win x" << '\n';

    };
    if (!textureVWin->loadFromFile("Assets/image/" + ngonngu[g_language] + "/v-win.png")) {
        std::cout << "khong tai duoc win v" << '\n';

    };
    if (!textureTwoDraw->loadFromFile("Assets/image/" + ngonngu[g_language] + "/draw-2player.png")) {
        std::cout << "khong tai duoc draw2" << '\n';

    };
    if (!textureThreeDraw->loadFromFile("Assets/image/" + ngonngu[g_language] + "/draw-3player.png")) {
        std::cout << "khong tai duoc draw3" << '\n';

    };
    spriteEndEffect = std::make_unique<sf::Sprite>(*(textureXWin));

    cursorShape.setSize(sf::Vector2f(cellSize - 10, CURSOR_THICKNESS));
    line.setSize(sf::Vector2f(0, 0));
    cursorShape.setFillColor(sf::Color::Blue);
    line.setFillColor(sf::Color::Red);
    spritePauseBox = std::make_unique<sf::Sprite>(*(texturePauseBox));
    spriteBounds = spritePauseBox->getLocalBounds();

    spritePauseBox->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });
    spritePauseBox->setPosition({ window.getSize().x / 2.0f,
                                    window.getSize().y / 2.0f });
    if (previousState == GameState::NewGame) firstGame = true;
    else firstGame = false;
    if ((previousState == GameState::LoadGame || previousState == GameState::Saving) && track.size() > 0)
    {
        //cout << track.size() << '\n';
        for (int i = 0; i < track.size(); i++)
        {
            std::unique_ptr<sf::Sprite> newPiece;
            if (track[i].second == 1) {
                newPiece = std::make_unique<sf::Sprite>(*textureXIcon);
                cntTurn1++;
            }
            else if (track[i].second == 2) {
                newPiece = std::make_unique<sf::Sprite>(*textureOIcon);
                cntTurn2++;
            }
            else {
                newPiece = std::make_unique<sf::Sprite>(*textureVIcon);
                cntTurn3++;
            }


            newPiece->setPosition({ margin + 20 + (track[i].first.second - 1) * cellSize,margin + 20 + (track[i].first.first - 1) * cellSize - CURSOR_THICKNESS });
            pieces.push_back(std::move(newPiece));
            mainGameBoard[track[i].first.first][track[i].first.second] = track[i].second;
        }
        score1.setString(playerNames[1] + "\nScore: " + to_string(player1Score) + "     Turn: " + to_string(cntTurn1));
        score2.setString(playerNames[2] + "\nScore: " + to_string(player2Score) + "     Turn: " + to_string(cntTurn2));
        score3.setString(playerNames[3] + "\nScore: " + to_string(player3Score) + "     Turn: " + to_string(cntTurn3));
    }

    line.setSize({ 0,0 });
    newGame();
    return;
}


void Gameplay::updateCursorShapePosition() {
    cursorShape.setPosition({ margin + (cursorX - 1) * cellSize + 10,margin + cursorY * cellSize - CURSOR_THICKNESS });
    line.setPosition({ startPoint });

}


void Gameplay::newGame() {

    if (previousState == GameState::NewGame)
    {
        track.clear();
        pieces.clear();
    }
    else
    {
        std::cout << selectedFile << "\n";
    }
    line.setRotation(sf::degrees(0));
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            mainGameBoard[i][j] = 0;
        }
    }
    currentPlayer = ((player1Score + player2Score + ((gameMode - 2) * player3Score)) % gameMode) + 1;
    //if (currentPlayer > gameMode) currentPlayer -= gameMode;
    isGameOver = 0;
    endGame = false;
    isPause = false;
    if (firstGame)
    {
        player1Score = 0;
        player2Score = 0;
        player3Score = 0;
    }
    result = 0;

    cursorY = BOARD_HEIGHT / 2;
    cursorX = BOARD_WIDTH / 2;
    updateCursorShapePosition();
}
GameState Gameplay::getNextState() {
    return nextState;
}

void Gameplay::handleEvent(const sf::Event& event) {
    cout << currentPlayer << '\n';
    if ((previousState == GameState::Saving || previousState == GameState::LoadGame) && track.size() > 0)
    {
        for (int i = 0; i < track.size(); i++) mainGameBoard[track[i].first.first][track[i].first.second] = track[i].second;
    }
    if (previousState == GameState::Saving)
    {

        previousState == GameState::Playing;
    }
    if (event.is<sf::Event::Closed>()) window.close();
    if (track.size() > 0) currentPlayer = (track[track.size() - 1].second % gameMode) + 1;
    if (currentPlayer < 1) currentPlayer = ((player1Score + player2Score + ((gameMode - 2) * player3Score)) % gameMode) + 1;
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (endGame) {
            if (mouseEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

                if (endButtons[0]->isMouseOver(mousePos)) {
                    nextState = GameState::Playing;
                    endGame = 0;


                }
                if (endButtons[1]->isMouseOver(mousePos)) {
                    nextState = GameState::Saving;

                }
                if (endButtons[2]->isMouseOver(mousePos)) {

                    nextState = GameState::MainMenu;

                }


            }

        }
        if (isPause) {

            if (mouseEvent->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords({ mouseEvent->position.x, mouseEvent->position.y });

                if (pauseButtons[0]->isMouseOver(mousePos)) {
                    nextState = GameState::Saving;
                    return;

                }
                if (pauseButtons[1]->isMouseOver(mousePos)) {
                    isPause = 0;
                    return;

                }
                if (pauseButtons[2]->isMouseOver(mousePos)) {

                    nextState = GameState::MainMenu;
                    return;
                }
                if (pauseButtons[3]->isMouseOver(mousePos)) {

                    nextState = GameState::Exiting;
                    return;
                }
                if (pauseButtons[4]->isMouseOver(mousePos)) {

                    g_musicOn = !g_musicOn;
                    pauseButtons[4]->setTexture(g_musicOn ? onMusicTexture : offMusicTexture);
                    gameplayMusic.setVolume(g_musicOn * 30);
                    return;
                }
                if (pauseButtons[5]->isMouseOver(mousePos)) {

                    g_soundOn = !g_soundOn;
                    pauseButtons[5]->setTexture(g_soundOn ? onSoundTexture : offSoundTexture);
                    return;
                }




            }
        }


    }
    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (endGame)
        {

            int prevIndex = selectedButtonIndex;

            if (key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) {

                selectedButtonIndex = (selectedButtonIndex - 1 + static_cast<int>(endButtons.size())) % static_cast<int>(endButtons.size());
            }
            else if (key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) {

                selectedButtonIndex = (selectedButtonIndex + 1) % static_cast<int>(endButtons.size());
            }
            else if (key->scancode == sf::Keyboard::Scancode::Enter) {
                result = 0;
                requestMenuMusic = true;

                if (selectedButtonIndex == 0) {
                    firstGame = false;
                    line.setSize({ 0,0 });  
                    newGame();
                    nextState = GameState::Playing;
                  
                    
                }
                else if (selectedButtonIndex == 1) {
                    nextState = GameState::Saving;
                }
                else if (selectedButtonIndex == 2) {
                    nextState = GameState::MainMenu;
                }
                track.clear();
                pieces.clear();

            }


            if (prevIndex != selectedButtonIndex) {
                endButtons[prevIndex]->setSelected(false);
                endButtons[selectedButtonIndex]->setSelected(true);
            }
        }
        if (isPause)
        {
            int prevIndex = selectedButtonIndex;

            if (key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) {

                selectedButtonIndex = (selectedButtonIndex - 1 + static_cast<int>(pauseButtons.size())) % static_cast<int>(pauseButtons.size());
            }
            else if (key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) {

                selectedButtonIndex = (selectedButtonIndex + 1) % static_cast<int>(pauseButtons.size());
            }
            else if (key->scancode == sf::Keyboard::Scancode::Enter) {
                result = 0;
                requestMenuMusic = true;
                // 1 save
                // 2 continue game
                // 3 restart
                // 4 quit
                // 5 music
                // 6 sfx
                if (selectedButtonIndex == 0) {
                    nextState = GameState::Saving;
                }
                else if (selectedButtonIndex == 1) {
                    isPause = 0;

                }
                else if (selectedButtonIndex == 2) {
                    firstGame = false;
                    line.setSize({ 0,0 });
                    newGame();
                    nextState = GameState::Playing;
                }
                else if (selectedButtonIndex == 3) {
                    nextState = GameState::MainMenu;
                }
                else if (selectedButtonIndex == 4) {
                    g_musicOn = !g_musicOn;
                    pauseButtons[4]->setTexture(g_musicOn ? onMusicTexture : offMusicTexture);
                    gameplayMusic.setVolume(g_musicOn * 30);
                }
                else if (selectedButtonIndex == 5) {
                    g_soundOn = !g_soundOn;
                    pauseButtons[5]->setTexture(g_soundOn ? onSoundTexture : offSoundTexture);
                }

            }


            if (prevIndex != selectedButtonIndex) {
                pauseButtons[prevIndex]->setSelected(false);
                pauseButtons[selectedButtonIndex]->setSelected(true);
            }
        }

        if (result > 0 && key->scancode == sf::Keyboard::Scancode::Space)
        {
            if (!endGame) {
                selectedButtonIndex = 0;

                for (auto& btn : endButtons) btn->setSelected(false);
                endButtons[0]->setSelected(true);
            }
            endGame = true;

        }
        if (isPause && key->scancode == sf::Keyboard::Scancode::Enter)
        {
            if (selectedButtonIndex != 4 && selectedButtonIndex != 5) {
                isPause = false;
            }

        }
        if (!isPause && key->scancode == sf::Keyboard::Scancode::Escape)
        {
            isPause = true;
            selectedButtonIndex = 0;
            for (auto& btn : pauseButtons) btn->setSelected(false);
            pauseButtons[0]->setSelected(true);
        }

        if (result == 0 && !isPause)
        {

            if (key->scancode == sf::Keyboard::Scancode::Escape)
            {
                requestMenuMusic = true;
                nextState = GameState::MainMenu;
            }
            if (key->scancode == sf::Keyboard::Scancode::W)
            {

                cursorY--;
                if (cursorY == 0) cursorY = 12;
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::S)
            {

                cursorY++;
                if (cursorY == 13) cursorY = 1;
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::A)
            {

                cursorX--;
                if (cursorX == 0) cursorX = 12;

                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::D)
            {

                cursorX++;
                if (cursorX == 13) cursorX = 1;

                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::Space)

            {
                playSound.setVolume(static_cast<float>(g_soundOn) * 75);
                playSound.play();

                int y = cursorY;
                int x = cursorX;
               



                if (mainGameBoard[y][x] == 0)
                {
                    if (currentPlayer == 1)
                    {
                        ++cntTurn1;
                        score1.setString(playerNames[1] + "\nScore: " + to_string(player1Score) + "     Turn: " + to_string(cntTurn1));
                        

                    }

                    else if (currentPlayer == 2)
                    {

                        ++cntTurn2;
                        score2.setString(playerNames[2] + "\nScore: " + to_string(player2Score) + "     Turn: " + to_string(cntTurn2));

                    }
                    else if (currentPlayer == 3) {

                        ++cntTurn3;
                        score3.setString(playerNames[3] + "\nScore: " + to_string(player3Score) + "     Turn: " + to_string(cntTurn3));

                    }
                    track.push_back({ {y,x},currentPlayer });
                    //currentPlayer = turn % gameMode;
                    ++turn;
                    mainGameBoard[y][x] = currentPlayer;


                    std::unique_ptr<sf::Sprite> newPiece;
                    if (currentPlayer == 1) {
                        newPiece = std::make_unique<sf::Sprite>(*textureXIcon);

                    }
                    else if (currentPlayer == 2) {
                        newPiece = std::make_unique<sf::Sprite>(*textureOIcon);
                    }
                    else if (currentPlayer == 3) {
                        newPiece = std::make_unique<sf::Sprite>(*textureVIcon);
                    }


                    newPiece->setPosition({ margin + 20 + (x - 1) * cellSize,margin + 20 + (y - 1) * cellSize - CURSOR_THICKNESS });
                    pieces.push_back(std::move(newPiece));


                    if (checkWin(y, x, currentPlayer) > 0)
                    {
                        startPoint = cord(pointOne.first, pointOne.second);

                        line.setPosition(startPoint);

                        // Calculate the angle of rotation

                        /*float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
                        line.setRotation(angle);*/
                        //window.draw(line);
                        winSound.setVolume(static_cast<float>(g_soundOn) * 75);
                        winSound.play();
                        if (currentPlayer == 1)
                        {
                            player1Score++;
                            score1.setString(playerNames[1] + "\nScore: " + to_string(player1Score) + "     Turn: " + to_string(cntTurn1));
                            result = 1;

                        }

                        else if (currentPlayer == 2)
                        {
                            player2Score++;

                            score2.setString(playerNames[2] + "\nScore: " + to_string(player2Score) + "     Turn: " + to_string(cntTurn2));
                            result = 2;
                        }
                        else if (currentPlayer == 3)
                        {
                            player3Score++;

                            score3.setString(playerNames[3] + "\nScore: " + to_string(player3Score) + "     Turn: " + to_string(cntTurn3));
                            result = 3;
                        }
                        cntTurn1 = 0;
                        cntTurn2 = 0;
                        cntTurn3 = 0;

                    }
                    else if (pieces.size() >= 144)
                    {
                        winSound.play();
                        if (gameMode == 2) result = 4;
                        else result = 5;
                    }

                    currentPlayer++;
                    if (currentPlayer > gameMode) currentPlayer = 1;
                    std::cout << "------------------------\n";
                    for (int i = 1; i < 13; i++)
                    {
                        for (int j = 1; j < 13; j++) std::cout << static_cast<int>(mainGameBoard[i][j]) << ' ';
                        std::cout << '\n';
                    }

                    std::cout << currentPlayer << ' ' << gameMode << ' ' << track.size() << '\n';
                    std::cout << player1Score << ' ' << player2Score << ' ' << player3Score << '\n';
                    std::cout << "------------------------\n";
                }
                else {
                    playSoundWrong.setVolume(static_cast<float>(g_soundOn) * 75);
                    playSoundWrong.play();
                }


            }



        }
    }


}

void Gameplay::update(sf::Vector2f mousePos) {
    updateCursorShapePosition();
    if (endGame)
    {

        for (auto& button : endButtons) {
            if (button != nullptr) button->update(mousePos);
        }
    }
    if (isPause) {
        for (auto& button : pauseButtons) {
            if (button != nullptr) button->update(mousePos);
        }

    }
}
void Gameplay::render(sf::RenderTarget& target) {

    target.draw(*(gameplayBackgroundSprite));

    target.draw(*(spriteCard1));
    target.draw(*(spriteCard2));
    if (gameMode == 3)  target.draw(*(spriteCard3));
    target.draw(score1);
    target.draw(score2);
    if (gameMode == 3) target.draw(score3);


    for (const auto& piece : pieces)
    {
        target.draw(*(piece));
    }


    if (!isGameOver)
    {
        target.draw(cursorShape);
        target.draw(line);
        if (currentPlayer == 1) {
            target.draw(*spriteXToken);

        }
        else if (currentPlayer == 2) {
            target.draw(*spriteOToken);
        }
        else {
            target.draw(*spriteVToken);
        }
    }
    if (endGame)
    {

        target.draw(*endBackgroundSprite);
        /*buttonNewGame->render(target);
        buttonSaveGame->render(target);
        buttonExit->render(target);*/
        for (auto& button : endButtons) {
            if (button != nullptr) button->render(target);
        }
    }

    if (result > 0 && !endGame)
    {
        target.draw(line);
        switch (result)
        {
        case 1:
            spriteEndEffect = std::make_unique<sf::Sprite>(*(textureXWin));
            break;
        case 2:
            spriteEndEffect = std::make_unique<sf::Sprite>(*(textureOWin));
            break;
        case 3:
            spriteEndEffect = std::make_unique<sf::Sprite>(*(textureVWin));
            break;
        case 4:
            spriteEndEffect = std::make_unique<sf::Sprite>(*(textureTwoDraw));
            break;
        case 5:
            spriteEndEffect = std::make_unique<sf::Sprite>(*(textureThreeDraw));
            break;
        default:
            spriteEndEffect = std::make_unique<sf::Sprite>(*(textureXWin));
            break;
        }
        sf::FloatRect spriteBounds = spriteEndEffect->getLocalBounds();

        spriteEndEffect->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                       spriteBounds.position.y + spriteBounds.size.y / 2.0f });
        spriteEndEffect->setPosition({ window.getSize().x / 2.0f,
                                         window.getSize().y / 2.0f });
        target.draw(*spriteEndEffect);

    }
    if (isPause)
    {
        target.draw(*spritePauseBox);
        for (auto& button : pauseButtons) {
            if (button != nullptr) button->render(target);
        }
    }
}