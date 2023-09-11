#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include "Core.h"
class Pipe
{
public:
	Pipe(std::shared_ptr<GameData> _dat);
	void Update(float _dt);
	void Render();
private:
	void SpawnPipeUp();
	void SpawnPipeDown();
private:
	std::shared_ptr<GameData> m_gameData;
	std::vector<sf::Sprite> m_vecpipesprite;
	sf::Clock m_clock;
};

