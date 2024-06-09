#pragma once
#include "Object.h"
enum class GOOMBA_STATE
{
    WALK, DIE, FALL
};
class Goomba :
    public Object
{
public:
    Goomba(sf::Vector2f _pos);
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
    virtual void EnterCollision(Collider* _pOther);
    virtual void ExitCollision(Collider* _pOther);
    virtual void StayCollision(Collider* _pOther);
public:
    //void SetDir(float _fdir) { m_fDir = _fdir; }
private:
    void MoveUpdate(float _dt);
private:
    GOOMBA_STATE eState;
    sf::Texture m_tex;
    float m_fSpeed; // 몬스터 스피드
    Vector2f m_vSpeed;
    sf::Sound m_kicksound;
};
