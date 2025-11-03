#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
#include <memory>
// Độ dài tên tối đa, nên được định nghĩa trong file header
const int MAX_NAME_LENGTH = 15;

class PlayerNameInput : public sf::Drawable
{
private:
    // Các thành phần private:
    sf::RectangleShape background;
    sf::Text text;
    std::string currentText;
    bool isActive;
    std::vector<Button*> menuButtons; // Danh sách các con trỏ tới tất cả các nút
    int selectedButtonIndex;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    // Hàm khởi tạo
    PlayerNameInput(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

    // Đặt trạng thái active (đang được chọn để nhập)
    void setActive(bool active);

    // Kiểm tra xem chuột có nhấp vào ô nhập liệu không
    bool checkClick(const sf::Vector2f& mousePos);

    // Xử lý sự kiện nhập ký tự
    void type(uint32_t unicode);

    // Lấy tên người chơi đã nhập
    std::string getName() const;
};