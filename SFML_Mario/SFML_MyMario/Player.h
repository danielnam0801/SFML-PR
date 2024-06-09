#pragma once
#include "Object.h"
enum class MARIO_STATE
{
    IDLE, WALK, JUMP, DOWN, DIE
};
class Player :
    public Object
{
public:
    Player(sf::Vector2f _pos);
public:
    virtual void Update(float _dt) override;
    virtual void Render() override;
    virtual void EnterCollision(Collider* _pOther);
    virtual void ExitCollision(Collider* _pOther);
    virtual void StayCollision(Collider* _pOther);
private:
    //sf::Sound m_sounds[(int)SOUND_TYPE::END];
    sf::Sound m_jumpsound;
    sf::Sound m_diesound;
    void MoveUpdate(float _dt);
    void StateUpdate(float _dt);
    void AnimationUpdate(float _dt);
    MARIO_STATE m_eCurState;
    MARIO_STATE m_ePrevState;
    sf::Texture m_tex;
    float m_acctime;
};

