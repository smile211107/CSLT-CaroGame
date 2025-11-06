
#include "GameState.h"
#include "Game.h"
#include "Gameplay.h"

#include "PlayerNameInput.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <memory>
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
int turn = 0;
int result = 0;
bool isPause = false;
const int margin = 30, playerSize = 50;

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

int checkRow(int y, int x)
{
    int res = 1, start = 1, end = 12;
    if (x > 4) start = x - 4;
    if (x < 9) end = x + 4;
    for (int i = start; i <= end; i++)
    {
        if (mainGameBoard[y][i] == mainGameBoard[y][i - 1] && mainGameBoard[y][i] == mainGameBoard[y][x] && mainGameBoard[y][i] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[y][x];
    }
    return 0;
}

int checkCol(int y, int x)
{
    int res = 1, start = 1, end = 12;
    if (y > 4) start = y - 4;
    if (y < 9) end = y + 4;
    for (int i = start; i <= end; i++)
    {
        if (mainGameBoard[i][x] == mainGameBoard[i - 1][x] && mainGameBoard[i][x] == mainGameBoard[y][x] && mainGameBoard[i][x] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[y][x];
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
    while (i <= 12 && j >= 1)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j + 1] && mainGameBoard[i][j] == mainGameBoard[y][x] && mainGameBoard[i][j] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[i][j];
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
    while (i <= 12 && j <= 12)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j - 1] && mainGameBoard[i][j] == mainGameBoard[y][x] && mainGameBoard[i][j] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[i][j];
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
    score1(font,playerName[1] + ": " + to_string(player1Score), 48),
    score2(font, playerName[2] + ": " + to_string(player2Score),48),
    score3(font, playerName[3] + ": " + to_string(player3Score), 48)
   
{
    
    this->nextState = GameState::Playing;
    this->textureCard1 = std::make_unique<sf::Texture>();
    this->textureCard2 = std::make_unique<sf::Texture>();
    this->textureCard3 = std::make_unique<sf::Texture>();
    this->textureOToken = std::make_unique<sf::Texture>();
    this->textureXToken = std::make_unique<sf::Texture>();
    this->textureVToken = std::make_unique<sf::Texture>();
    if (!textureCard1->loadFromFile("Assets/gameplay/player1-card.png")) {
        cout << "khong tai duoc card 1";
    }
    if (!textureCard2->loadFromFile("Assets/gameplay/player2-card.png")) {
        cout << "khong tai duoc card 2";
    }
    if (!textureCard3->loadFromFile("Assets/gameplay/player3-card.png")) {
        cout << "khong tai duoc card 3";
    }
    if (!textureXToken->loadFromFile("Assets/gameplay/player1-token.png")) {
        cout << "khong tai duoc card 1";
    }
    if (!textureOToken->loadFromFile("Assets/gameplay/player2-token.png")) {
        cout << "khong tai duoc card 2";
    }
    if (!textureVToken->loadFromFile("Assets/gameplay/player3-token.png")) {
        cout << "khong tai duoc card 3";
    }
    if (!gameplayMusic.openFromFile("assets/audio/gameplayAudio.mp3")) {

        cout << "khong tai duoc am thanh";
    }
   
    this->spriteCard1 = std::make_unique<sf::Sprite>(*(this->textureCard1));
    this->spriteCard2 = std::make_unique<sf::Sprite>(*(this->textureCard2));
    this->spriteCard3 = std::make_unique<sf::Sprite>(*(this->textureCard3));
    this->spriteXToken = std::make_unique<sf::Sprite>(*(this->textureXToken));
    this->spriteOToken = std::make_unique<sf::Sprite>(*(this->textureOToken));
    this->spriteVToken = std::make_unique<sf::Sprite>(*(this->textureVToken));


    sf::FloatRect spriteBounds = this->spriteCard1->getLocalBounds();

    this->spriteCard1->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });
    this->spriteCard2->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });
    this->spriteCard3->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });


    this->spriteCard1->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.1f });

    this->spriteCard2->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.3f });
    this->spriteCard3->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.5f });
    this->spriteXToken->setPosition({ window.getSize().x * 0.75f + 350.0f,
                                     window.getSize().y * 0.1f });

    this->spriteOToken->setPosition({ window.getSize().x * 0.75f + 350.0f,
                                     window.getSize().y * 0.3f });
    this->spriteVToken->setPosition({ window.getSize().x * 0.75f + 350.0f,
                                     window.getSize().y * 0.5f });
    score1.setPosition({ window.getSize().x * 0.65f,
                                     window.getSize().y * 0.1f });
    score2.setPosition({ window.getSize().x * 0.65f,
                                    window.getSize().y * 0.3f });
    score3.setPosition({ window.getSize().x * 0.65f,
                                  window.getSize().y * 0.5f });
   
    
    gameplayMusic.setLooping(true);
    gameplayMusic.setVolume(30);
    gameplayMusic.play();

    gameplayBackgroundTexture = std::make_unique<sf::Texture>();
    if (!this->gameplayBackgroundTexture->loadFromFile("Assets/Image/inGame-background.png")) {
        std::cout << "khong the mo background gameplay" << '\n';

    }
    this->gameplayBackgroundSprite = std::make_unique<sf::Sprite>(*(this->gameplayBackgroundTexture));

    sf::Vector2f backgroundScale(
        static_cast<float>(this->window.getSize().x) / this->gameplayBackgroundTexture->getSize().x,
        static_cast<float>(this->window.getSize().y) / this->gameplayBackgroundTexture->getSize().y
    );
    gameplayBackgroundSprite->setScale(backgroundScale);

    cellSize = 80;


    
    this->textureTwoDraw = std::make_unique<sf::Texture>();
    this->textureThreeDraw = std::make_unique<sf::Texture>();
    this->textureXIcon = std::make_unique<sf::Texture>();
    this->textureOIcon = std::make_unique<sf::Texture>();
    this->textureVIcon = std::make_unique<sf::Texture>();
    this->textureXWin = std::make_unique<sf::Texture>();
    this->textureOWin = std::make_unique<sf::Texture>();
    this->textureVWin = std::make_unique<sf::Texture>();
    this->texturePauseBox = std::make_unique<sf::Texture>();
    if (!this->texturePauseBox->loadFromFile("Assets/gameplay/pause-box-vn.png")) {
        cout << "khong tai duoc pause box" << '\n';

    };
    if (!this->textureOIcon->loadFromFile("Assets/gameplay/o-icon.png")) {
        cout << "khong tai duoc icon o" << '\n';

    };
    if (!this->textureXIcon->loadFromFile("Assets/gameplay/x-icon.png")) {
        cout << "khong tai duoc icon x" << '\n';

    };
    if (!this->textureVIcon->loadFromFile("Assets/gameplay/v-icon.png")) {
        cout << "khong tai duoc icon x" << '\n';

    };
    if (!this->textureOWin->loadFromFile("Assets/gameplay/o-win-vn.png")) {
        cout << "khong tai duoc win o" << '\n';

    };
    if (!this->textureXWin->loadFromFile("Assets/gameplay/x-win-vn.png")) {
        cout << "khong tai duoc win x" << '\n';

    };
    if (!this->textureVWin->loadFromFile("Assets/gameplay/v-win-vn.png")) {
        cout << "khong tai duoc win v" << '\n';

    };
    if (!this->textureTwoDraw->loadFromFile("Assets/gameplay/draw-2player-vn.png")) {
        cout << "khong tai duoc draw2" << '\n';

    };
    if (!this->textureThreeDraw->loadFromFile("Assets/gameplay/draw-3player-vn.png")) {
        cout << "khong tai duoc draw3" << '\n';

    };
    this->spriteEndEffect = std::make_unique<sf::Sprite>(*(this->textureXWin));

    cursorShape.setSize(sf::Vector2f(cellSize - 10, CURSOR_THICKNESS));
    cursorShape.setFillColor(sf::Color::Blue);
    this->spritePauseBox = std::make_unique<sf::Sprite>(*(this->texturePauseBox));
    spriteBounds = this->spritePauseBox->getLocalBounds();

    this->spritePauseBox->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });
    this->spritePauseBox->setPosition({ window.getSize().x / 2.0f,
                                    window.getSize().y / 2.0f });

    newGame();
}


void Gameplay::updateCursorShapePosition() {
    cursorShape.setPosition({ margin + (cursorX - 1) * cellSize + 10,margin + cursorY * cellSize - CURSOR_THICKNESS });

}


void Gameplay::newGame() {
    pieces.clear();
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            mainGameBoard[i][j] = 0;
        }
    }
    currentPlayer = 1;
    isGameOver = 0;

    cursorY = BOARD_HEIGHT / 2;
    cursorX = BOARD_WIDTH / 2;
    updateCursorShapePosition();
}
GameState Gameplay::getNextState() {
    return this->nextState;
}

void Gameplay::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) window.close();

    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (result > 0 && key->scancode == sf::Keyboard::Scancode::Space)
        {
            result = 0;
            newGame();
        }
        if (isPause && key->scancode == sf::Keyboard::Scancode::Space)
        {
            isPause = false;
        }
        if (!isPause && key->scancode == sf::Keyboard::Scancode::P)
        {
            isPause = true;
        }
        if (result == 0 && !isPause )
        {
            
            if (key->scancode == sf::Keyboard::Scancode::Escape)
            {
                requestMenuMusic = true;
                this->nextState = GameState::MainMenu;
            }
            if (key->scancode == sf::Keyboard::Scancode::W)
            {

                cursorY--;
                if (cursorY == 0) cursorY = 12;
                //cursorY = (cursorY == 0) ? 12 : cursorY;
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::S)
            {

                cursorY++;
                if (cursorY == 13) cursorY = 1;
                //cursorY = (cursorY == 13) ? 1 : (cursorY);
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::A)
            {

                cursorX--;
                if (cursorX == 0) cursorX = 12;
                //cursorX = (cursorX == -1) ? 11 : (cursorX);
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::D)
            {

                cursorX++;
                if (cursorX == 13) cursorX = 1;
                //cursorX = (cursorX == 12) ? 0 : cursorX;
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::Enter)
                //|| key->scancode == sf::Keyboard::Scancode::Space)
            {
                
                int y = cursorY;
                int x = cursorX;


                if (mainGameBoard[y][x] == 0)
                {
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
                    else {
                        newPiece = std::make_unique<sf::Sprite>(*textureVIcon);
                    }
                

                    newPiece->setPosition({ margin + 20 + (x - 1) * cellSize,margin + 20 + (y - 1) * cellSize - CURSOR_THICKNESS });
                    pieces.push_back(std::move(newPiece));

                    
                    if (checkWin(y, x, currentPlayer) > 0)
                    {


                        if (currentPlayer == 1)
                        {
                            player1Score++;                          
                            score1.setString(playerName[1] + ": " + to_string(player1Score));
                            result = 1;

                        }
                            
                        else if(currentPlayer == 2)
                        {
                            player2Score++;
                            score2.setString(playerName[2] + ": " + to_string(player2Score));
                            result = 2;
                        }
                        else {
                            player3Score++;
                            score3.setString(playerName[3] + ": " + to_string(player3Score));
                            result = 3;
                        }
                    }
                    else if (pieces.size() >= 144)
                    {
                        if (gameMode == 2) result = 4;
                        result = 5;
                        
                    }
                    
                    currentPlayer++;
                    if (currentPlayer > gameMode) currentPlayer = 1;
                    
                }


            }



        }
    }


}

void Gameplay::update(sf::Vector2f mousePos) {
    updateCursorShapePosition();
}
void Gameplay::render(sf::RenderTarget& target) {

    target.draw(*(this->gameplayBackgroundSprite));
    
    target.draw(*(this->spriteCard1));
    target.draw(*(this->spriteCard2));
    if(gameMode == 3)  target.draw(*(this->spriteCard3));
    target.draw(score1);
    target.draw(score2);
    if(gameMode == 3) target.draw(score3);


    for (const auto& piece : pieces)
    {
        target.draw(*(piece));
    }


    if (!isGameOver)
    {
        target.draw(cursorShape);
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
    if (result > 0)
    {
        switch (result)
        {
        case 1:
            this->spriteEndEffect = std::make_unique<sf::Sprite>(*(this->textureXWin));
            break;
        case 2:
            this->spriteEndEffect = std::make_unique<sf::Sprite>(*(this->textureOWin));
            break;
        case 3:
            this->spriteEndEffect = std::make_unique<sf::Sprite>(*(this->textureVWin));
            break;
        case 4:
            this->spriteEndEffect = std::make_unique<sf::Sprite>(*(this->textureTwoDraw));
            break;
        case 5:
            this->spriteEndEffect = std::make_unique<sf::Sprite>(*(this->textureThreeDraw));
            break;
        default:
            this->spriteEndEffect = std::make_unique<sf::Sprite>(*(this->textureXWin));
            break;
        }
        sf::FloatRect spriteBounds = this->spriteEndEffect->getLocalBounds();

        this->spriteEndEffect->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                       spriteBounds.position.y + spriteBounds.size.y / 2.0f });
        this->spriteEndEffect->setPosition({ window.getSize().x / 2.0f,
                                         window.getSize().y / 2.0f });
        target.draw(*spriteEndEffect);
    }
    if (isPause)
    {
        target.draw(*spritePauseBox);
    }
}