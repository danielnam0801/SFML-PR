#pragma once
#include "Object.h"
class Brick : public Object
{
public:
    Brick(sf::Sprite& _sprite);
    bool m_IsBroken = false;
    Vector2f m_velocity;
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
    virtual void EnterCollision(Collider* _pOther);
    virtual void ExitCollision(Collider* _pOther);
    virtual void StayCollision(Collider* _pOther);
private:
    sf::Sound m_bumpsound;
    sf::Sound m_breaksound;
};

