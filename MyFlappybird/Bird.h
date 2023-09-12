#pragma once
#include "Core.h"
#include "SFML/Graphics.hpp"
#include "define.h"

class Bird
{
public:
	Bird(std::shared_ptr<GameData> _data);
public:
	void Init();
	void Update(float dt);
	void Render();
	void BirdMove();
	void AnimateBird(float _dt);
private:
	std::shared_ptr<GameData> m_gameData;
	sf::Sprite m_birdsprite;
	std::vector<sf::Texture> m_vecanim;
	size_t m_animiter;
	BirdState curState;
};

