#include "PlayerNameInput.h"
#include <iostream>

// --- Triển khai Hàm Khởi tạo ---
PlayerNameInput::PlayerNameInput(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
    :text(font,"",24)
{
    background.setPosition(position);
    background.setSize(size);
    background.setFillColor(sf::Color(139, 69, 19, 180));
    background.setOutlineThickness(0.0f);

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    // Căn chỉnh vị trí chữ (tùy chỉnh để khớp với hình ảnh)
    text.setPosition({ position.x + 10, position.y + (size.y / 2.0f) - 20.0f });

    isActive = false;
    currentText = "";
    text.setString(currentText);
}

// --- Triển khai Hàm draw (Hàm vẽ) ---
void PlayerNameInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    target.draw(text, states);
}

// --- Triển khai Hàm setActive ---
void PlayerNameInput::setActive(bool active)
{
    isActive = active;
    // Đổi màu viền khi active
    background.setOutlineThickness(active ? 3.0f : 0.0f);
    background.setOutlineColor(sf::Color::Yellow);

    // Cập nhật text để hiển thị con trỏ | nếu đang active
    if (isActive) {
        text.setString(currentText + "|");
    }
    else {
        text.setString(currentText);
    }
}

// --- Triển khai Hàm checkClick ---
bool PlayerNameInput::checkClick(const sf::Vector2f& mousePos)
{
    return background.getGlobalBounds().contains(mousePos);
}

// --- Triển khai Hàm type (Xử lý nhập liệu) ---
void PlayerNameInput::type(uint32_t unicode)
{
    if (!isActive) return;

    if (unicode == 8) // Phím Backspace
    {
        if (!currentText.empty())
            currentText.pop_back();
    }
    else if (unicode == 13 || unicode == 10) // Phím Enter/Return
    {
        // Có thể thêm logic chuyển sang ô tiếp theo hoặc kết thúc nhập tại đây
    }
    else if (unicode < 128) // Ký tự in được thông thường
    {
        if (currentText.length() < MAX_NAME_LENGTH)
        {
            currentText += static_cast<char>(unicode);
        }
    }

    // Luôn cập nhật text, thêm | nếu đang active
    text.setString(currentText + (isActive ? "|" : ""));
}

// --- Triển khai Hàm getName ---
std::string PlayerNameInput::getName() const
{
    return currentText;
}