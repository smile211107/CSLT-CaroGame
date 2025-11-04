#pragma once
#include "BaseState.h"
using namespace sf;

class MainMenuState : public BaseState {
private:
	Texture backgroundTexture, newGameButtonTexture, loadGameButtonTexture, tutorialButtonTexture,
		settingsButtonTexture, quitButtonTexture, aboutButtonTexture;

	void setupLayout(unsigned int windowWidth, unsigned int windowHeight);
public:
	MainMenuState();
	~MainMenuState();
	Sprite backgroundSprite, newGameButton, loadGameButton, tutorialButton, 
		settingsButton, quitButton, aboutUsButton;

	void handleInput(const Event& event, RenderWindow& window) override;
	void update(Time dt) override;
	void draw(RenderWindow& window) override;

};