#pragma once
#include "SFML/Graphics.hpp"
#include "Core.h"
class Land
{
public:
	Land(std::shared_ptr<GameData> _data);
public:
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gameData;
	std::vector<sf::Sprite> m_vecSprite;
public:
	float landHeight;
};

