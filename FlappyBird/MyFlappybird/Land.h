#pragma once
#include<SFML/Graphics.hpp>
#include "Core.h"
#include<vector>
class Land
{
public:
	Land(std::shared_ptr<GameData> _data);
	void Init();
	void Update(float _dt);
	void Render();
	const std::vector<sf::Sprite>& GetSprite() const { return m_vecSprite; }
private:
	std::shared_ptr<GameData> m_gamedata;
	std::vector<sf::Sprite> m_vecSprite;

};

