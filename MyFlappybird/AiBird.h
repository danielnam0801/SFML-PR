#pragma once
#include <SFML/Graphics.hpp>
#include "AiPipe.h"
class AiBird
{
public:
	AiBird();
	void  Update(float _dt, bool _isMove, std::vector<AiPipe> _pipe);
	void  Render(sf::RenderWindow& _window);
	float GetGapDiff(std::vector<AiPipe> _pipe);
	bool  GetDead() { return m_IsDead; }
private:
	bool  m_IsDead;
	float m_fSpeed;
	float m_birdx;
	float m_birdy;
	int	  m_score;
	sf::Sprite m_birdsprite;
	
};

