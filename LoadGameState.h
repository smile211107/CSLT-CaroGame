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
// Cấu trúc lưu thông tin của một file save
struct SaveFileInfo {
    std::string filename;   // Tên file thực tế (ví dụ: save1.txt)
    std::string gameName;   // Dòng 1: Tên màn chơi
    std::string date;       // Dòng 2: Ngày tạo
    int mode = 2;               // Dòng 3: Chế độ chơi
    std::string score;      // Dòng 4: Tỉ số
    long long timestamp = 1;    // Thời gian sửa đổi file (để sắp xếp)
};

class LoadState : public State {
public:
    LoadState(sf::RenderWindow& window, sf::Font& font);

    virtual GameState getNextState() override;
    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Vector2f mousePos) override;
    virtual void render(sf::RenderTarget& target) override;

    // Hàm trả về tên file được chọn để GamePlay xử lý
    std::string getSelectedFile() const;

private:
    sf::RenderWindow& window;
    sf::Font& font;
    GameState nextState;
    TextButton fileNo1, fileNo2, fileNo3, fileNo4, fileNo5;
    // Background
    std::unique_ptr<sf::Texture> backgroundTexture;
    std::unique_ptr<sf::Sprite> backgroundSprite;
    int selection;
    // Nút quay lại
    std::unique_ptr<Button> buttonBack;
    sf::Texture buttonBackTexture;

    // Danh sách các file save
    std::vector<SaveFileInfo> saveFiles;

    // UI cho các slot save (mỗi slot là 1 button)
    std::vector<std::unique_ptr<Button>> slotButtons;

    // Text hiển thị thông tin trên mỗi slot
    std::vector<sf::Text> slotTexts;

     // Lưu tên file người dùng click vào

    // Hàm hỗ trợ
    void loadSavedFilesFromDisk();
    void setupUISlots();
};