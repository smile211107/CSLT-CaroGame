#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h" // Cần để báo cho Game biết phải chuyển state

class State {
public:
    virtual ~State() = default;

    // Yêu cầu Game chuyển sang state nào
    virtual GameState getNextState() = 0;

    // Xử lý sự kiện (như click chuột, gõ phím)
    virtual void handleEvent(const sf::Event& event) = 0;

    // Cập nhật logic (như di chuột qua nút)
    virtual void update(sf::Vector2f mousePos) = 0;

    // Vẽ trang
    virtual void render(sf::RenderTarget& target) = 0;
};