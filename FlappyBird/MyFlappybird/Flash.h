#pragma once
#include<SFML/Graphics.hpp>
#include "Core.h"
class Flash
{
public:
	Flash(std::shared_ptr<GameData> _data);
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::RectangleShape m_backShape;
	float			   m_flashSpeed;
	bool			   m_IsFlashOn;
};

