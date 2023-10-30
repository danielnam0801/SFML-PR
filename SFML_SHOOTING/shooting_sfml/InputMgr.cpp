#include "pch.h"
#include "InputMgr.h"

bool InputMgr::IsSpriteClicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow& _window)
{
	if (sf::Mouse::isButtonPressed(_button))
	{
		sf::IntRect ButtonRect(_object.getGlobalBounds().left, _object.getGlobalBounds().top
			, _object.getGlobalBounds().width, _object.getGlobalBounds().height);
		if (ButtonRect.contains(sf::Mouse::getPosition(_window)))
			return true;
	}
	return false;
}