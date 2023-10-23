#pragma once
#include "Scene.h"
class Player;
class GameScene : public Scene
{
public:
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	vector<std::shared_ptr<Player>> m_vecPlayer;
};

