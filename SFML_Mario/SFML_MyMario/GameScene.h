#pragma once
#include "Scene.h"
#include "Map.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
public:
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	sf::RectangleShape m_rt;
	Map* m_map;
	sf::Music m_bgm;
};

