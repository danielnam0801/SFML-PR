#include "InputMgr.h"

bool InputMgr::IsSpliteClicked(sf::Sprite _object, sf::Mouse::Button _button, sf::RenderWindow& _window)
{
	if (sf::Mouse::isButtonPressed(_button))
	{
		//// contain 들어가있는지 판단 체크를 해야겠지.
		//sf::IntRect objrect(_object.getGlobalBounds().left, _object.getGlobalBounds().top
		//, _object.getGlobalBounds().width, _object.getGlobalBounds().height);
		//objrect.contains(sf::Mouse::getPosition(_window));

		sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(_window);
		if (_object.getGlobalBounds().contains(mousepos))
			return true;
	}
	return false;
}
