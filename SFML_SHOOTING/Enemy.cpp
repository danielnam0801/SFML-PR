#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(Vector2f _pos, Vector2f _dir, Vector2f _scale, ENEMY _eType, int _hpMax, int _damagemin, int _damagemax)
{
	m_eType = _eType;
	switch (m_eType)
	{
	case ENEMY::MOVEDOWN:
	case ENEMY::FOLLOW:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Enemy01"));
		m_sprite.setScale(_scale);
	}
		break;
	case ENEMY::FOLLOWFAST:

		break;
	case ENEMY::FOLOWSHOOT:
		break;
	case ENEMY::FOLOWFASTSHOOT:
		break;
	case ENEMY::ELITE:
		break;
	case ENEMY::BOSS1:
		break;
	default:
		break;
	}
	m_hpMax = _hpMax;
	m_hp = m_hpMax;
	m_damagemax = _damagemax;
	m_damagemin = _damagemin;
	m_sprite.setPosition(_pos);
}

void Enemy::TakeDamage(int _damage)
{
}

bool Enemy::Update(const float& _dt)
{
	MoveMent(_dt);
	if (m_sprite.getPosition().y > SCREEN_HEIGHT)
		return true;
	else
		return false;
}

void Enemy::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
}

void Enemy::MoveMent(const float& _dt)
{
	m_sprite.move(0.f, 20.f);
}
