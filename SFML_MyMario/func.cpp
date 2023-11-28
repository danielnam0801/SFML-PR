#include "pch.h"
#include "func.h"

float Length(sf::Vector2f _vec)
{
	return float(sqrt(pow(_vec.x, 2) + pow(_vec.y, 2)));
}

sf::Vector2f Normalize(sf::Vector2f _vec, float _length)
{
	if (_length == 0)
		return sf::Vector2f(0.f, 0.f);
	else
		return _vec / _length;
}
