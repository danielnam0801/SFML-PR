#pragma once
class InputMgr
{
public:
    //InputMgr() {}
    //~InputMgr() {}
    SINGLE(InputMgr);
    bool IsSpriteClicked(sf::Sprite _object, sf::Mouse::Button _button
        , sf::RenderWindow& _window);
    const sf::Vector2i GetMousePos(sf::RenderWindow& _window) const
    {
        return sf::Mouse::getPosition(_window);
    }
};