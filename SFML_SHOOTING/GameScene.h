#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
class GameScene : public Scene
{
public:
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	void EnemyUpdate(float _dt);
	void PlayerUpdate(float _dt);
	void SpawnEnemy();
private:
	std::vector<std::shared_ptr<Player>> m_vecPlayer;
	std::vector<Enemy> m_vecEnemy;
	Sprite m_background;
	Clock m_clock;
	float spawnTime = 0.5f;
};

