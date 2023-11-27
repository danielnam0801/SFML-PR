#pragma once
#include "Scene.h"
class MenuScene : public Scene
{
public:
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	Sprite m_background;
	Sprite m_title;
	Sprite m_button1;
	Sprite m_button2;
	Sprite m_butonExit;
};

