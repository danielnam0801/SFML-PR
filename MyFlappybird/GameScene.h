#pragma once
#include "Scene.h"
#include "Core.h"
class Pipe; class Land; class Bird;
class GameScene : public Scene
{
public:
	GameScene(std::shared_ptr<GameData> _data);
	~GameScene();
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gameData;
	sf::Sprite m_background;
	Land* m_pLand;
	Pipe* m_pPipe;
	Bird* m_pBird;
};

