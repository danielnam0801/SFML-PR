#pragma once
#include "Object.h"
class DefTile : public Object
{
public:
    DefTile(Sprite& _sprite);
    ~DefTile();
public:
    void Update(float _dt);
    void Render();
private:
    sf::Sprite m_sprite;
};

