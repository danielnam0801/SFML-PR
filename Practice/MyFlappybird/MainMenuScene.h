#pragma once
#include "Scene.h"
#include "Core.h"
class MainMenuScene : public Scene
{
public:
	MainMenuScene(std::shared_ptr<GameData> _data);
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Sprite m_background;
	sf::Sprite m_title;
	sf::Sprite m_playbutton;
};

