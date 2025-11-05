
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
const int margin = 30, playerSize = 50;
vector<pair<int, int>> track;
unsigned char mainGameBoard[13][13] = {
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
    if (!textureCard1->loadFromFile("Assets/Image/player1-card.png")) {
        cout << "khong tai duoc card 1";
    }
    if (!textureCard2->loadFromFile("Assets/Image/player2-card.png")) {
        cout << "khong tai duoc card 2";
    }
    if (!textureCard3->loadFromFile("Assets/Image/player3-card.png")) {
        cout << "khong tai duoc card 3";
    }
    if (!backgroundMusic.openFromFile("assets/mainaudio.mp3")) {

        cout << "khong tai duoc am thanh";
    }
   
    this->spriteCard1 = std::make_unique<sf::Sprite>(*(this->textureCard1));
    this->spriteCard2 = std::make_unique<sf::Sprite>(*(this->textureCard2));
    this->spriteCard3 = std::make_unique<sf::Sprite>(*(this->textureCard3));

    sf::FloatRect spriteBounds = this->spriteCard1->getLocalBounds();

    this->spriteCard1->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });
    spriteBounds = this->spriteCard2->getLocalBounds();
    this->spriteCard2->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });

   spriteBounds = this->spriteCard3->getLocalBounds();
    this->spriteCard3->setOrigin({ spriteBounds.position.x + spriteBounds.size.x / 2.0f,
                                     spriteBounds.position.y + spriteBounds.size.y / 2.0f });


    this->spriteCard1->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.1f });

    this->spriteCard2->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.3f });
    this->spriteCard3->setPosition({ window.getSize().x * 0.75f,
                                     window.getSize().y * 0.5f });
    score1.setPosition({ window.getSize().x * 0.65f,
                                     window.getSize().y * 0.1f });
    score2.setPosition({ window.getSize().x * 0.65f,
                                    window.getSize().y * 0.3f });
    score3.setPosition({ window.getSize().x * 0.65f,
                                  window.getSize().y * 0.5f });
   
    backgroundMusic.setLooping(true);
    backgroundMusic.setVolume(50);
    backgroundMusic.play();

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


    


    this->textureXIcon = std::make_unique<sf::Texture>();
    this->textureOIcon = std::make_unique<sf::Texture>();
    this->textureVIcon = std::make_unique<sf::Texture>();
    if (!this->textureOIcon->loadFromFile("Assets/gameplay/o-icon.png")) {
        cout << "khong tai duoc icon o" << '\n';

    };
    if (!this->textureXIcon->loadFromFile("Assets/gameplay/x-icon.png")) {
        cout << "khong tai duoc icon x" << '\n';

    };
    if (!this->textureVIcon->loadFromFile("Assets/gameplay/v-icon.png")) {
        cout << "khong tai duoc icon x" << '\n';

    };


    cursorShape.setSize(sf::Vector2f(cellSize - 10, CURSOR_THICKNESS));
    cursorShape.setFillColor(sf::Color::Blue);

    newGame();
}


void Gameplay::updateCursorShapePosition() {
    cursorShape.setPosition({ margin + cursorX * cellSize + 10,margin + cursorY * cellSize - CURSOR_THICKNESS });

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
    currentPlayer = 0;
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

        if (!isGameOver)
        {

            if (key->scancode == sf::Keyboard::Scancode::Escape) window.close();
            if (key->scancode == sf::Keyboard::Scancode::W)
            {

                --cursorY;
                cursorY = (cursorY == 0) ? 12 : cursorY;
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::S)
            {

                ++cursorY;
                cursorY = (cursorY == 13) ? 1 : (cursorY);
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::A)
            {

                --cursorX;
                cursorX = (cursorX == -1) ? 11 : (cursorX);
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::D)
            {

                ++cursorX;
                cursorX = (cursorX == 12) ? 0 : cursorX;
                updateCursorShapePosition();

            }
            else if (key->scancode == sf::Keyboard::Scancode::Enter ||
                key->scancode == sf::Keyboard::Scancode::Space)
            {
                
                int y = cursorY;
                int x = cursorX;


                if (mainGameBoard[y][x] == 0)
                {
                    currentPlayer = turn % gameMode;
                    ++turn;
                    mainGameBoard[y][x] = currentPlayer;


                    std::unique_ptr<sf::Sprite> newPiece;
                    if (currentPlayer == 0) {
                        newPiece = std::make_unique<sf::Sprite>(*textureXIcon);

                    }
                    else if (currentPlayer == 1) {
                        newPiece = std::make_unique<sf::Sprite>(*textureOIcon);

                    }
                    else {
                        newPiece = std::make_unique<sf::Sprite>(*textureVIcon);
                    }
                

                    newPiece->setPosition({ margin + 20 + x * cellSize,margin + 20 + (y - 1) * cellSize - CURSOR_THICKNESS });
                    pieces.push_back(std::move(newPiece));

                   
                    if (checkWin(y, x, currentPlayer) > 0)
                    {
                        isGameOver = true;


                        if (currentPlayer == 0)
                        {
                            player1Score++;
                            score1.setString(playerName[1] + ": " + to_string(player1Score));

                        }
                            
                        else if(currentPlayer == 1)
                        {
                            player2Score++;
                            score2.setString(playerName[2] + ": " + to_string(player2Score));
                        }
                        else {
                            player3Score++;
                            score3.setString(playerName[3] + ": " + to_string(player3Score));
                        }
              
                        newGame();
                    }
                    
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
    }

}