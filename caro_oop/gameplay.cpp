#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "player.h"
#include "board.h"
#include "gameplay.h"
#include <iostream>
#include <conio.h>
using namespace std;
using namespace sf;
//Board myFirstBoard;
//mainGameBoard[13][13];
const int margin = 30, playerSize = 50;
vector<pair<int, int>> track;


Texture sky, menu, board, xo;
Player mainPlayer;

// Thay doi toa do trong 2d array thanh toa do trong window
//Vector2f cord(float y, float x)
//{
//    y = margin + 20 + ((y-1) * playerSize);
//    x = margin + 20 + ((x-1) * playerSize);
//    
//}

// Tai texture
void loadTextures()
{
    sky.loadFromFile("assets/background/weebSky.jpg");
    //menu.loadFromFile("assets/background/weebSky.jpg");
    board.loadFromFile("assets/gameplay/board.png");
    xo.loadFromFile("assets/gameplay/xo.png");
}

// Tao sprite
Sprite background(sky), gameBoard(board), playerSymbol(xo), cursor(xo), winEffect(xo);


// Gan vi tri ban dau
void setSpritePosition()
{
    background.setPosition({ 0,0 });
    gameBoard.setPosition({ margin,margin });
    float cord_y = static_cast<float>(margin + 20 + (mainPlayer.y - 1) * 80);
    float cord_x = static_cast<float>(margin + 20 + (mainPlayer.x - 1) * 80);
    playerSymbol.setPosition({ cord_x, cord_y });
    cursor.setPosition({ cord_x,cord_y });
    winEffect.setPosition({ 1100,700 });
    //playerSymbol.setPosition({ margin + 20 + (mainPlayer.x - 1) * playerSize, margin + 20 + (mainPlayer.y - 1) });
}

// Cat sprite trong spritesheet
void setSpriteRect()
{
    background.setTextureRect(IntRect({ 0,0 }, { 466,161 }));
    gameBoard.setTextureRect(IntRect({ 0,0 }, { 970,970 }));
    playerSymbol.setTextureRect(IntRect({ 0,0 }, { playerSize,playerSize }));
    cursor.setTextureRect(IntRect({ 150,0 }, { playerSize,playerSize }));
    winEffect.setTextureRect(IntRect({ 0,50 }, { 150,50 }));
}

// Can ti le sprite
void setSpriteScale(RenderWindow& window)
{
    Vector2u winSize = window.getSize();
    Vector2u txtSize = sky.getSize();
    Vector2f scale(static_cast<float>(winSize.x) / txtSize.x, static_cast<float>(winSize.y) / txtSize.y);
    background.setScale({ scale.x , scale.y });
    winEffect.setScale({ 5,5 });
}

// Dat vi tri playerSymbol
void setSymbolPosition(int y, int x, Sprite& symbol)
{
    float cord_y = static_cast<float>(margin + 20 + (y - 1) * 80);
    float cord_x = static_cast<float>(margin + 20 + (x - 1) * 80);
    symbol.setPosition({ cord_x, cord_y });
}

// Ve lai man hien tai
void reDraw(RenderWindow& window)
{
    for (pair<int, int> tracker : track)
    {
        playerSymbol.setTextureRect(IntRect({ (((mainGameBoard[tracker.first][tracker.second] - 1))) * playerSize,0 }, { playerSize,playerSize }));
        setSymbolPosition(tracker.first, tracker.second, playerSymbol);
        window.draw(playerSymbol);
    }
}

// Ve nen game
void renderBg(RenderWindow& window)
{
    window.draw(background);
    //Vector2u size = board.getSize();
}


// Ve man choi
void renderGame(RenderWindow& window)
{
    window.draw(gameBoard);
    reDraw(window);
    window.draw(cursor);
}

Game::Game() 
    :window(VideoMode::getDesktopMode(), "vttaan's work", State::Fullscreen)
{


}
   

void Game::gamePlay()
{
   /* VideoMode desktop = VideoMode::getDesktopMode();
    RenderWindow window(desktop, "vttaan's work",State::Fullscreen);*/
    loadTextures();
    setSpritePosition();
    setSpriteRect();
    setSpriteScale(window);

    // Chinh so luong nguoi choi
    mainPlayer.setPlayerNum(3);

    // Mo window
    while (window.isOpen())
    {
        while (optional event = window.pollEvent())
        {
            /*Vector2f position(static_cast<float>(20 + (pp.y * 80) + margin), static_cast<float>(20 + (pp.x * 80) + margin));
            mouse.setPosition(position);*/
            if (event->is<Event::Closed>()) window.close();
            else if (auto* key = event->getIf<Event::KeyPressed>())
            {
                if (key->scancode == Keyboard::Scancode::Escape) window.close();
                else if (key->scancode == Keyboard::Scancode::W) mainPlayer.y = max(mainPlayer.y - 1, 1);
                else if (key->scancode == Keyboard::Scancode::S) mainPlayer.y = min(mainPlayer.y + 1, 12);
                else if (key->scancode == Keyboard::Scancode::A) mainPlayer.x = max(mainPlayer.x - 1, 1);
                else if (key->scancode == Keyboard::Scancode::D) mainPlayer.x = min(mainPlayer.x + 1, 12);
                //else if (key->scancode == Keyboard::Scancode::L) exportFile();
                else if (key->scancode == Keyboard::Scancode::Enter && mainGameBoard[mainPlayer.y][mainPlayer.x] == 0)
                {
                    // Dat gia tri cho o hien tai
                    mainGameBoard[mainPlayer.y][mainPlayer.x] = ((mainPlayer.turn - 1) % mainPlayer.playerNum) + 1;

                    // Luu o hien tai vao track
                    track.push_back({ mainPlayer.y,mainPlayer.x });

                    // check win
                    mainPlayer.playerResult = checkWin(mainPlayer.y, mainPlayer.x, mainGameBoard[mainPlayer.y][mainPlayer.x]);
                    if (track.size() == 144 && mainPlayer.playerResult == 0) mainPlayer.playerResult = 4;

                    if (mainPlayer.playerResult > 0)
                    {
                        winEffect.setTextureRect(IntRect({ 0,mainPlayer.playerResult * 50 }, { 150,50 }));
                        cout << "player " << mainPlayer.playerResult << " win\n";
                    }
                    // xong 1 turn
                    mainPlayer.turn++;
                }
                // Dat con chuot vao vi tri (x,y)
                setSymbolPosition(mainPlayer.y, mainPlayer.x, cursor);

            }
        }

        // Xoa frame cu
        window.clear();


        // Ve frame moi
        renderBg(window);
        renderGame(window);
        //window.draw(winEffect);
        if (mainPlayer.playerResult > 0)
        {
            window.draw(winEffect);
        }

        // Chieu frame moi

        window.display();
    }

    // In ban co ra terminal
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 12; j++) cout << mainGameBoard[i][j] << ' ';
        cout << '\n';
    }
}