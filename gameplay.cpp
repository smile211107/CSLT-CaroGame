#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>

// #include <conio.h>
using namespace sf;
using namespace std;
int menuSeclection = 0, getKey, turn = 0, playerNum = 2;
Texture sky, school, street, menu, board, xo, cursor;
Sprite player(xo);
// Kich thuoc cac sprite
const int buttonW = 72, buttonH = 27;
const int playerSize = 50;

// Do lech board so voi window
const int margin = 30;

// So luong button trong menu
const int menuSize = 5;

//Khoi tao ma tran ban co va toa do ban dau
int mainGameBoard[12][12];
vector<pair<int, int>> track;
pair<int, int> current = { 5,5 };



// Load cac texture
void loadTextures()
{
    sky.loadFromFile("assets/background/weebSky.png");
    // menu.loadFromFile("assets/menu/menu spritesheet.png");
    board.loadFromFile("assets/gameplay/board.png");
    xo.loadFromFile("assets/gameplay/xo.png");
}


int checkRow(int y)
{
    int res = 1;
    for (int i = 1; i < 12; i++)
    {
        if (mainGameBoard[y][i] == mainGameBoard[y][i - 1] && mainGameBoard[y][i] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[y][i];
    }
    return 0;
}

int checkCol(int x)
{
    int res = 1;
    for (int i = 0; i < 12; i++)
    { 
        if (mainGameBoard[i][x] == mainGameBoard[i - 1][x] && mainGameBoard[i][x] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[i][x];
    }
    return 0;
}

int checkDia2(int y, int x)
{
    int i = y, j = x, res = 1;
    if (y + x < 11)
    {
        i = 1;
        j = y + x - 1;
    }
    else
    {
        i = x + y - 10;
        j = 10;
    }
    while (i < 12 && j >= 0)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j + 1] && mainGameBoard[i][j] > 0) res++;
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
        i = y - x + 1;
        j = 1;
    }
    else
    {
        i = 1;
        j = x - y + 1;
    }
    while (i < 12 && j < 12)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j - 1] && mainGameBoard[i][j] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[i][j];
        i++; j++;
    }
    return 0;
}

int checkWin(int y, int x)
{
    if (mainGameBoard[y][x] > 0) return max(max(checkRow(y), checkCol(x)), max(checkDia1(y, x), checkDia2(y, x)));
    return 0;
}

// Tao window

void game(sf::RenderWindow& window) {
    Vector2u winSize = window.getSize();
    

    // Tao sprite
    loadTextures();
    Sprite bg(sky), scl(school), gnd(street), startButton(menu), gameBoard(board), reDrawPlayer(xo), mouse(xo), winEffect(xo), playAgainBox(xo);

    // Cat sprite trong spritesheet
    startButton.setTextureRect(IntRect({ 0, 0 }, { buttonW, buttonH }));
    mouse.setTextureRect(IntRect({ 3 * playerSize,0 }, { playerSize,playerSize }));
    winEffect.setTextureRect(IntRect({ 0,50 }, { 150,50 }));
    playAgainBox.setTextureRect(IntRect({ 200,0 }, { 263,150 }));

    // Can center cho sprite
    playAgainBox.setOrigin({ 130,75 });

    // Scale sprite button
    startButton.setScale({ 3,3 });

    // Scale cac sprite
    Vector2u txtSize = sky.getSize();
    
    Vector2f scale(static_cast<float>(winSize.x) / txtSize.x, static_cast<float>(winSize.y) / txtSize.y);
    bg.setScale({ scale.x , scale.y });
    gnd.setScale({ scale.x , scale.y });
    scl.setScale({ scale.x , scale.y });


    winEffect.setScale({ 5,5 });


    
    // Vong lap game
    while (window.isOpen())
    {


        while (optional event = window.pollEvent())
        {
            Vector2f position(static_cast<float>(20 + (current.second * 80) + margin), static_cast<float>(20 + (current.first * 80) + margin));
            mouse.setPosition(position);
            if (event->is<Event::Closed>()) window.close();
            else if (auto* key = event->getIf<Event::KeyPressed>())
            {
                if (key->scancode == Keyboard::Scancode::Escape) window.close();
                else if (key->scancode == Keyboard::Scancode::W) current.first = max(current.first - 1, 0);
                else if (key->scancode == Keyboard::Scancode::S) current.first = min(current.first + 1, 11);
                else if (key->scancode == Keyboard::Scancode::A) current.second = max(current.second - 1, 0);
                else if (key->scancode == Keyboard::Scancode::D) current.second = min(current.second + 1, 11);
                else if (key->scancode == Keyboard::Scancode::J && mainGameBoard[current.first][current.second] == 0)
                {
                    mainGameBoard[current.first][current.second] = (turn % playerNum) + 1;
                    track.push_back({ current });
                    turn++;
                    player.setPosition(position);
                }

            }
        }

        // Xoa frame cu
        window.clear();



        // Ve frame moi
        bg.setPosition({ 0,0 });
        gnd.setPosition({ 0,0 });
        scl.setPosition({ 0,0 });
        startButton.setPosition({ 852,500 });
        winEffect.setPosition({ 1000,700 });
        gameBoard.setPosition({ margin,margin });
        playAgainBox.setPosition({ 960,540 });




        window.draw(bg);
        window.draw(gnd);
        window.draw(scl);
        //window.draw(startButton);
        window.draw(gameBoard);


        // Ve lai man choi
        for (pair<int, int> tracker : track)
        {
            int y = tracker.first, x = tracker.second;
            int num = mainGameBoard[y][x];
            x = 20 + (80 * x) + margin; y = 20 + (80 * y) + margin;
            switch (num)
            {
                case 1:
                {
                    reDrawPlayer.setTextureRect(IntRect({ 0,0 }, { playerSize,playerSize }));
                    break;
                }
                case 2:
                {
                    reDrawPlayer.setTextureRect(IntRect({ playerSize,0 }, { playerSize,playerSize }));
                    break;
                }
                case 3:
                {
                    reDrawPlayer.setTextureRect(IntRect({ 2 * playerSize ,0 }, { playerSize,playerSize }));
                    break;
                }
            }
            Vector2f reposition(static_cast<float>(x), static_cast<float>(y));
            reDrawPlayer.setPosition(reposition);
            window.draw(reDrawPlayer);
        }
        window.draw(mouse);
        

        // Check win
        if (turn > playerNum * 4)
        {
            int result = checkWin(track[track.size()-1].first, track[track.size() - 1].second);
            cout << result << '\n';
            switch (result)
            {
                case 1:
                {
                    winEffect.setTextureRect(IntRect({ 0,50 }, { 150,50 }));
                    window.draw(winEffect);
                    break;
                }
                case 2:
                {
                    winEffect.setTextureRect(IntRect({ 0,100 }, { 150,50 }));
                    window.draw(winEffect);
                    break;
                }
                case 3:
                {
                    winEffect.setTextureRect(IntRect({ 0,150 }, { 150,50 }));
                    window.draw(winEffect);
                    break;
                }
            }
            /*if (result > 0)
            {
                window.draw(playAgainBox);
            }*/
        }



        // Chieu frame moi len window
        window.display();
    }
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++) cout << mainGameBoard[i][j] << ' ';
        cout << '\n';
    }
    // Ket thuc
}