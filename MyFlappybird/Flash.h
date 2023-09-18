#pragma once
#include<SFML/Graphics.hpp>
#include "Core.h"
class Flash
{
private:
	std::shared_ptr<GameData> m_gamedata = std::make_shared<GameData>();
	sf::RectangleShape	m_backShape;
	float				m_flashSpeed;
	float			    lerp_value;
	bool				m_IsFlashOn;
	sf::Clock			m_clock;

public:
	Flash(std::shared_ptr<GameData> m_gamedata);
	void Update(float _dt);
	void Render();
};

