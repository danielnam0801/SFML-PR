#include "pch.h"
#include "AttackAround_State.h"
#include "Enemy.h"

AttackAround_State::AttackAround_State()
	:State(ENEMY_STATE::ATTACK_AROUND)
{

}

AttackAround_State::~AttackAround_State()
{
}

void AttackAround_State::Update(float _dt)
{
	Sprite enemySprite = m_pEnemy->GetSprite();

	Vector2f circlebullet[12] =
	{ {0,3},{0,-3},{3,0},{-3,0},
	  {3,1},{3,-1},{-3,1},{-3,-1},
	{2,2},{-2,-2},{-2,2},{2,-2} };

	for (int i = 0; i < 12; ++i)
	{
		m_pEnemy->GetBullet().push_back(Bullet(Vector2f(enemySprite.getPosition()),
			2.f, 50.f, Vector2f(circlebullet[i]), 2.f, WEAPON::ENEMY_BULLET));
	}

	m_pEnemy->GetBullet().push_back(Bullet(Vector2f(enemySprite.getPosition()),
		2.f, 50.f, Vector2f(1.f, 0.f), 2.f, WEAPON::ROTATE));
	m_pEnemy->GetBullet().push_back(Bullet(Vector2f(enemySprite.getPosition()),
		2.f, 50.f, Vector2f(0.f, 1.f), 2.f, WEAPON::ROTATE));
}

void AttackAround_State::EnterState()
{
}

void AttackAround_State::ExitState()
{
}
