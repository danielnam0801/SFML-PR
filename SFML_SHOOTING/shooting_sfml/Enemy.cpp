#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(Vector2f _pos, Vector2f _dir, Vector2f _scale, ENEMY _eType, 
	int _hpMax, int _damagemin, int _damagemax)
{
	m_eType = _eType;
	switch (m_eType)
	{
	case ENEMY::MOVEDOWN:
	case ENEMY::FOLLOW:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Enemy01"));
		m_sprite.setScale(_scale);
		m_sprite.setPosition(_pos);
	}
		break;
	case ENEMY::FOLLOWFAST:
		break;
	case ENEMY::FOLLOWSHOOT:
		break;
	case ENEMY::FOLLOWFASTSHOOT:
		break;
	case ENEMY::ELITE:
		break;
	case ENEMY::BOSS1:
		break;
	}
	m_hpMax = _hpMax;
	m_hp = m_hpMax;
	m_damagemax = _damagemax;
	m_damagemin = _damagemin;
	m_dir = _dir;
	m_hpBar.setSize(Vector2f(50.f, 10.f));
	m_hpBar.setFillColor(Color::Red);
	m_hpBar.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height);
	m_hpBarback = m_hpBar;
	m_hpBarback.setFillColor(Color(25, 25, 25, 200));

}

void Enemy::TakeDamage(int _damage)
{
	m_hp -= _damage;
	if (m_hp <= 0)
		m_hp = 0;
}

bool Enemy::Update(const float& _dt)
{
	MoveMent(_dt);
	UiUpdate();
	if(m_sprite.getPosition().y > SCREEN_HEIGHT)
		return true;
	return false;
}

void Enemy::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBarback);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBar);
}

void Enemy::MoveMent(const float& _dt)
{
	switch (m_eType)
	{
	case ENEMY::MOVEDOWN:
		m_sprite.move(m_dir.x * 80.f* _dt, m_dir.y *80.f * _dt);
		break;
	case ENEMY::FOLLOW:
		break;
	case ENEMY::FOLLOWFAST:
		break;
	case ENEMY::FOLLOWSHOOT:
		break;
	case ENEMY::FOLLOWFASTSHOOT:
		break;
	case ENEMY::ELITE:
		break;
	case ENEMY::BOSS1:
		break;
	}

}

void Enemy::UiUpdate()
{
	m_hpBar.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height);
	m_hpBarback.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height);
	m_hpBar.setScale((float)m_hp / (float)m_hpMax, 1.f);

}
