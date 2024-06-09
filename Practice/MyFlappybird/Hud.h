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
	std::shared_ptr<GameData> m_gamedata;
	sf::Text m_scoretext;
	sf::Text m_highScoretext;
	bool m_isHighScore;
	float m_twinkelSpeed;
};

