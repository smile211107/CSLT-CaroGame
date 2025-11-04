#pragma once
#include "BaseState.h"
using namespace sf;

class GuideState : public BaseState {
private:
	Texture okButtonTexture, guidebgTexture;
	const float m_buttonScaleNormal = 1.0f;
	const float m_buttonScaleHover = 1.2f;

public:
	GuideState();
	~GuideState();
	Sprite okButton, guideBackground;

	void handleInput(const Event& event, RenderWindow& window) override;
	void update(Time dt, RenderWindow& window) override;
	void draw(RenderWindow& window) override;

};