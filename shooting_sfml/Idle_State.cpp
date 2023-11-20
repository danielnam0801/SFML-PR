#include "pch.h"
#include "Idle_State.h"
#include "AI.h"
#include "Enemy.h"
Idle_State::Idle_State() 
	: State(ENEMY_STATE::IDLE)
{

}

Idle_State::~Idle_State()
{

}

void Idle_State::Update(float _dt)
{
	// move
	Vector2f curpos = m_pEnemy->GetSprite().getPosition();
	curpos.x += 500.f * _dt * m_pEnemy->GetDir().x;
	float fDist = abs(m_pEnemy->GetCenterPos().x - curpos.x) - m_pEnemy->GetMaxDis();
	Vector2f dir = m_pEnemy->GetDir();
	if (fDist > 0.f)
	{
		dir.x *= -1.f;
		curpos.x += fDist * dir.x;
	}
	/*if (m_pEnemy->GetClock().getElapsedTime().asSeconds() > 1.f)
	{
		m_pEnemy->SetState(ENEMY_STATE::ATTACK_CIRCLE);
		m_pEnemy->GetClock().restart();
	}*/
	m_pEnemy->SetDir(dir);
	m_pEnemy->SetPos(curpos);
}

void Idle_State::EnterState()
{
}

void Idle_State::ExitState()
{
}
