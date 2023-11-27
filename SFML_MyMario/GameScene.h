#pragma once
#include "Scene.h"
#include "Camera.h"
class GameScene : public Scene
{
public:
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	sf::RectangleShape m_rt;
};

