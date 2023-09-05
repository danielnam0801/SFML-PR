#pragma once
#include <SFML/Graphics.hpp>
class InputManager
{
public:
	bool IsSpriteClicked(sf::Sprite _sprite, sf::Mouse::Button _button, sf::RenderWindow _window);
	const sf::Vector2i GetMousePos(sf::RenderWindow _window) const
	{
		return sf::Mouse::getPosition(_window);
	}
};