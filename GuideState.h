#pragma once
#include "BaseState.h"
using namespace sf;

class GuideState : public BaseState {
private:
	Texture okButtonTexture, guidebgTexture;

public:
	GuideState();
	~GuideState();
	Sprite okButton, guideBackground;

	void handleInput(const Event& event, RenderWindow& window) override;
	void update(Time dt) override;
	void draw(RenderWindow& window) override;

};