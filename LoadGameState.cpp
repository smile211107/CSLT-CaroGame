#include "LoadGameState.h"
#include "PlayerNameInput.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#define gap 100
#define textsize 40
namespace fs = std::filesystem;
string selectedFile = "";
void align(TextButton& button)
{
    button.buttonText.setCharacterSize(textsize);
    sf::FloatRect textBounds = button.buttonText.getLocalBounds();
    button.buttonText.setOrigin({ textBounds.size.x / 2.0f, textBounds.size.y / 2.0f });
}
extern bool g_language;
extern std::string ngonngu[2];

LoadState::LoadState(sf::RenderWindow& window, sf::Font& font)
    : window(window), font(font),
    fileNo1("File not found",font,{1500.0F, 60.0F}, {window.getSize().x / 2.0f, window.getSize().y * 0.4f}),
    fileNo2("File not found",font,{1500.0F, 60.0F}, {window.getSize().x / 2.0f, window.getSize().y * 0.4f + gap}),
    fileNo3("File not found",font,{1500.0F, 60.0F}, {window.getSize().x / 2.0f, window.getSize().y * 0.4f + gap * 2}),
    fileNo4("File not found",font,{1500.0F, 60.0F}, {window.getSize().x / 2.0f, window.getSize().y * 0.4f + gap * 3 }),
    fileNo5("File not found",font,{1500.0F, 60.0F}, {window.getSize().x / 2.0f, window.getSize().y * 0.4f + gap * 4 }) 
{
    nextState = GameState::LoadGame;
    selection = 1;
    backgroundTexture = std::make_unique<sf::Texture>();
    if (!backgroundTexture->loadFromFile("Assets/Image/" + ngonngu[g_language] + "/loadGame-background.png")) {
        std::cerr << " Khong the tai background load game\n";
    }
    backgroundSprite = std::make_unique<sf::Sprite>(*backgroundTexture);

    sf::Vector2f scale(
        static_cast<float>(window.getSize().x) / backgroundTexture->getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture->getSize().y
    );
    backgroundSprite->setScale(scale);

    if (!buttonBackTexture.loadFromFile("Assets/image/" + ngonngu[g_language] + "/return-button.png")) {
        std::cout << "Khong the mo return-button\n";
    }
    buttonBack = std::make_unique<Button>(buttonBackTexture,
        sf::Vector2f(window.getSize().x / 2.f, window.getSize().y * 0.9f));

    loadSavedFilesFromDisk();
    setupUISlots();
}

void LoadState::loadSavedFilesFromDisk() {
    saveFiles.clear();
    std::string path = "saved";

    if (!fs::exists(path)) {
        fs::create_directory(path);
        return;
    }

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".txt") {
            SaveFileInfo info;
            info.filename = entry.path().filename().string();

            auto ftime = fs::last_write_time(entry);
            info.timestamp = ftime.time_since_epoch().count();

            std::ifstream inFile(entry.path());
            if (inFile.is_open()) {
                std::getline(inFile, info.gameName); 
                std::getline(inFile, info.date);     
                inFile >> info.mode;                 
                inFile.ignore(); 
                std::getline(inFile, playerNames[1]);
                inFile >> player1Score;
                inFile.ignore();
                std::getline(inFile, playerNames[2]);
                inFile >> player2Score;
                inFile.ignore();
                info.score = to_string(player1Score) + " / " + to_string(player2Score);
                if (info.mode == 3)
                {
                    std::getline(inFile, playerNames[3]);
                    inFile >> player3Score;
                    inFile.ignore();
                    info.score += " / " + to_string(player3Score);
                }
                saveFiles.push_back(info);
                inFile.close();
            }
        }
    }

    std::sort(saveFiles.begin(), saveFiles.end(), [](const SaveFileInfo& a, const SaveFileInfo& b) {
        return a.timestamp > b.timestamp;
        });

    if (saveFiles.size() > 5) {
        saveFiles.resize(5);
    }

}

void LoadState::setupUISlots() {
    float startY = window.getSize().y * 0.4f; 

    for (size_t i = 0; i < saveFiles.size(); ++i) {
        std::string modeStr = (saveFiles[i].mode == 2) ? "2 players" : "3 players"; // Ví dụ convert mode
        std::string displayStr = saveFiles[i].gameName + "                    " +
            saveFiles[i].date + "                     " +
            modeStr + "                    " +
            saveFiles[i].score;
        sf::Text text(font, displayStr, 50);
        if (i==0) fileNo1.buttonText.setString(displayStr);
        else if (i==1) fileNo2.buttonText.setString(displayStr);
        else if (i==2) fileNo3.buttonText.setString(displayStr);
        else if (i==3) fileNo4.buttonText.setString(displayStr);
        else if (i==4) fileNo5.buttonText.setString(displayStr);
        text.setFillColor(sf::Color::White); 
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin({ textRect.position.x + textRect.size.x / 2.0f,
            textRect.position.y + textRect.size.y / 2.0f });
        text.setPosition({ window.getSize().x / 2.f, startY + i * gap });

        slotTexts.push_back(text);
    }
    align(fileNo1);
    align(fileNo2);
    align(fileNo3);
    align(fileNo4);
    align(fileNo5);
}

void LoadState::handleEvent(const sf::Event& event) {
    fileNo1.setSelected(false);
    fileNo2.setSelected(false);
    fileNo3.setSelected(false);
    fileNo4.setSelected(false);
    fileNo5.setSelected(false);
    switch (selection)
    {
       
    case 1:
        fileNo1.setSelected(true);
        buttonBack->setSelected(false);
        break;
    case 2:
        buttonBack->setSelected(false);
        fileNo2.setSelected(true);
        break;
    case 3:
        buttonBack->setSelected(false);
        fileNo3.setSelected(true);
        break;
    case 4:
        buttonBack->setSelected(false);
        fileNo4.setSelected(true);
        break;
    case 5:
        buttonBack->setSelected(false);
        fileNo5.setSelected(true);
        break;
    case 6:
        buttonBack->setSelected(true);
        break;
    }
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) {
            selection--;
            if (selection < 1) selection = 6;
        }
        else if (key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) {

            selection++;
            if (selection > 6) selection = 1;

        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter) {

            if (selection == 6) {
                selection = 1;
                nextState = GameState::MainMenu;
                return;
            }
            
            selectedFile = "saved/" + saveFiles[selection - 1].filename;
            std::ifstream inFile(selectedFile);
            string temp;
            int moves = 0, y, x, val;
            gameMode = saveFiles[selection - 1].mode;
            std::getline(inFile, temp); 
            std::getline(inFile, temp);
            std::getline(inFile, temp);
            std::getline(inFile, playerNames[1]);
            inFile >> player1Score; inFile.ignore();
            std::getline(inFile, playerNames[2]);
            inFile >> player2Score; inFile.ignore();
            if (gameMode == 3)
            {
                std::getline(inFile, playerNames[3]);
                inFile >> player3Score; inFile.ignore();
            }
            inFile >> moves;
            for (int i = 0; i < moves; i++)
            {
                inFile >> y >> x >> val;
                track.push_back({ {y,x},val });
            }
            previousState = GameState::LoadGame;
            nextState = GameState::Playing;

        }
    }
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {

        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(
                { mouseEvent->position.x, mouseEvent->position.y });

            if (buttonBack->isMouseOver(mousePos)) {
                nextState = GameState::MainMenu;
            }

            for (size_t i = 0; i < slotButtons.size(); ++i) {
                if (slotButtons[i]->isMouseOver(mousePos)) {
                    selectedFile = saveFiles[i].filename;
                    std::cout << "Loading file: " << selectedFile << std::endl;

                    nextState = GameState::Playing;
                }
            }
        }
    }
}

void LoadState::update(sf::Vector2f mousePos) {
    buttonBack->update(mousePos);
    for (auto& btn : slotButtons) {
        btn->update(mousePos);
    }
}

void LoadState::render(sf::RenderTarget& target) {
    target.draw(*backgroundSprite);

    buttonBack->render(target);
    fileNo1.render(target);
    fileNo2.render(target);
    fileNo3.render(target);
    fileNo4.render(target);
    fileNo5.render(target);
}

GameState LoadState::getNextState() {
    return nextState;
}

std::string LoadState::getSelectedFile() const {
    return selectedFile;
}
