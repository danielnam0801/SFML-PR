#pragma once
#include "Object.h"
class Player : public Object
{
public:
    Player();
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
    virtual void EnterCollision(Collider* _other);
    virtual void ExitCollision(Collider* _other);
    virtual void StayCollision(Collider* _other);
};

