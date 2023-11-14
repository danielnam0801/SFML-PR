#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Vector2f _pos, float _initvelocity
	, float _maxvelocity, Vector2f _dir, 
	float _acc, WEAPON _eWeapon)
{
	m_eType = _eWeapon;
	switch (m_eType)
	{
	case WEAPON::LASER_R:
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Laser"));
		m_sprite.setScale(0.2f, 0.2f);
		m_damage = 1;
		break;
	case WEAPON::MISSILE01:
	case WEAPON::MISSILE02:
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Bullet"));
		m_sprite.setScale(0.07f, 0.07f);
		m_damage = 2;
		break;
	case WEAPON::ENEMY_BULLET:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("EnemyBullet"));
		m_sprite.setScale(0.15f, 0.15f);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
			m_sprite.getGlobalBounds().height / 2);
		//m_sprite.setRotation(atan2(m_dir.y, m_dir.x) * 180 / M_PI);
		m_damage = rand() % 2 + 1;
	}
		break;
	case WEAPON::BOMB:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Bomb"));
		m_damage = 5;
	}
		break;
	}
	m_maxVelocity = _maxvelocity;
	m_accerlation = _acc;
	m_dir = _dir;
	m_curVelocity = Vector2f(_initvelocity * m_dir.x
							,_initvelocity * m_dir.y);
	m_sprite.setPosition(_pos);
}

bool Bullet::Update(const float& _dt)
{
	MoveMent(_dt);

	//// 총알 - 적 충돌
	//for (size_t i = 0; i < _vecenemy.size();)
	//{
	//	if (m_sprite.getGlobalBounds().intersects(_vecenemy[i].GetSprite().getGlobalBounds()))
	//	{
	//		//_vecenemy.erase(_vecenemy.begin() + i);
	//		if (!_vecenemy[i].GetIsDead())
	//			_vecenemy[i].TakeDamage(m_damage);
	//		return true;
	//	}
	//	else
	//		++i;
	//}
	//if (m_sprite.getPosition().y < 0)
	//	return true;
	//return false;
	return m_sprite.getPosition().y < 0;
}

void Bullet::MoveMent(const float& _dt)
{
	switch (m_eType)
	{
	case WEAPON::LASER_R:
	case WEAPON::MISSILE01:
	case WEAPON::MISSILE02:
	case WEAPON::BOMB:
	{
		if (m_accerlation > 0.f)
		{
			if (m_curVelocity.x < m_maxVelocity)
				m_curVelocity.x += m_accerlation * m_dir.x * _dt;
			if (m_curVelocity.y < m_maxVelocity)
				m_curVelocity.y += m_accerlation * m_dir.y * _dt;
		}
		else // to do : 가속도 감소 총알?
		{
			m_curVelocity = Vector2f(m_maxVelocity * m_dir.x
				, m_maxVelocity * m_dir.y);
		}
		m_sprite.move(m_curVelocity);
	}
		break;
	case WEAPON::ENEMY_BULLET:
	{
		m_curVelocity = m_dir * _dt * m_maxVelocity * 10.f;
		m_sprite.move(m_curVelocity);
	}
		break;
	case WEAPON::SPLIT:
		break;
	case WEAPON::ROTATE:
	{
		m_theta++;
	}
		break;
	default:
		break;
	}
	
}

void Bullet::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
}

