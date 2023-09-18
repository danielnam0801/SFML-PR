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
	const std::vector<sf::Sprite>& GetSprite() const { return m_vecSprite; }
private:
	std::shared_ptr<GameData> m_gameData;
	std::vector<sf::Sprite> m_vecSprite;
public:
	float landHeight;
};

