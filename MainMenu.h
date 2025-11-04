#pragma once
#include "BaseState.h"
using namespace sf;

class MainMenuState : public BaseState {
private:
	Texture backgroundTexture, newGameButtonTexture, loadGameButtonTexture, tutorialButtonTexture,
		settingsButtonTexture, quitButtonTexture, aboutButtonTexture;

	void setupLayout(unsigned int windowWidth, unsigned int windowHeight);
	const float m_buttonScaleNormal = 1.0f;
	const float m_buttonScaleHover = 1.2f;
public:
	MainMenuState();
	~MainMenuState();
	Sprite backgroundSprite, newGameButton, loadGameButton, tutorialButton, 
		settingsButton, quitButton, aboutUsButton;

	void handleInput(const Event& event, RenderWindow& window) override;
	void update(Time dt, RenderWindow& window) override;
	void draw(RenderWindow& window) override;

};