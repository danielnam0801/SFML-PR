#pragma once
#include "Core.h"
class Hud
{
public:
	Hud(std::shared_ptr<GameData> _data);
	void Update(int _score);
	void Render();
	void HighUpdate(float _dt);
	void HighRender();

private:
	std::shared_ptr<GameData> m_gameData;
	sf::Text m_scoreText;
	sf::Text m_highScoreText;
	bool ishighScore = false;
	float m_twinkleSpeed;
};

