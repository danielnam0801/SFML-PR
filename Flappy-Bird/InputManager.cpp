#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow _window)
{
	if (sf::Mouse::isButtonPressed(_button))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(_window);
		if(_object.getGlobalBounds().contains(mousePos))
			return true;
	}
	return false;
}
