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
    float circleTime;
    float curTime;
    sf::CircleShape m_circle;
private:
    void MakeCircleShape();
    void MoveUpdate(float _dt);
};

