#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;

enum class StateType {
	None,
	MainMenu,
	Guide,
	Exit
};

class BaseState {
public:
	virtual ~BaseState() = default;

	virtual void handleInput(const Event& event, RenderWindow& window) = 0;
	virtual void update(Time dt) = 0;
	virtual void draw(RenderWindow& window) = 0;

	StateType getNextState() {
		return m_nextState;
	}
	void resetNextState() {
		m_nextState = StateType::None;
	}
protected:
	StateType m_nextState = StateType::None;
};
