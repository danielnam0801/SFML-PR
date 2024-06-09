#pragma once
#include "Object.h"
class Ground :
    public Object
{
public:
    Ground(sf::Sprite& _sprite);
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
    virtual void EnterCollision(Collider* _pOther);
    virtual void ExitCollision(Collider* _pOther);
    virtual void StayCollision(Collider* _pOther);
};

