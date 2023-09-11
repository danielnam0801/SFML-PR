#pragma once
#include "Scene.h"
#include "Core.h"
class Pipe;
class GameScene : public Scene
{
public:
	GameScene(std::shared_ptr<GameData> _data);
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gameData;
	sf::Sprite m_background;
	Pipe* m_pPipe;
};

