#pragma once
#include "Scene.h"
#include "Core.h"
class GameOverScene : public Scene
{
public:
	GameOverScene(std::shared_ptr<GameData> _data);
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Sprite m_background;
};

