#include "Collision.h"

bool Collision::IsSpriteCollision(sf::Sprite _spr1, sf::Sprite _spr2)
{
    return _spr1.getGlobalBounds().intersects(_spr2.getGlobalBounds());
}

bool Collision::IsSpriteCollision(sf::Sprite _spr1, float _scale1, sf::Sprite _spr2, float _scale2)
{
    _spr1.setScale(_scale1, _scale1);
    _spr2.setScale(_scale2, _scale2);
    return _spr1.getGlobalBounds().intersects(_spr2.getGlobalBounds());
}
