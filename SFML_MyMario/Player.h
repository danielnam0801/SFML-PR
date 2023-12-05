#pragma once
#include "Object.h"
class Player :
    public Object
{
public:
    Player();
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
    virtual void EnterCollision(Collider* _pOther);
    virtual void ExitCollision(Collider* _pOther);
    virtual void StayCollision(Collider* _pOther);
private:
    void MoveUpdate(float _dt);
    void CircleUpdate(float _dt);
private:
    sf::CircleShape _circleShape;
    sf::Clock m_Clock;
};

