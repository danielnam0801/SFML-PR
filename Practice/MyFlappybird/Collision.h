#pragma once
#include<SFML/Graphics.hpp>
class Collision
{
public:
	bool IsSpriteCollision(sf::Sprite _spr1, sf::Sprite _spr2);
	bool IsSpriteCollision(sf::Sprite _spr1, float _scale1, sf::Sprite _spr2, float _scale2);
};

