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
	case WEAPON::ROTATE:
	case WEAPON::ONLYROTATE:
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
	//m_enemyradius = Vector2f(_enemy.getGlobalBounds().width / 2, _enemy.getGlobalBounds().height / 2);
}

bool Bullet::Update(const float& _dt, Sprite _enemy)
{
	MoveMent(_dt, _enemy);

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

void Bullet::MoveMent(const float& _dt, Sprite _enemy)
{
	switch (m_eType)
	{
	case WEAPON::LASER_R:
	case WEAPON::MISSILE01:
	case WEAPON::MISSILE02:
	case WEAPON::BOMB:
	case WEAPON::ENEMY_BULLET:
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
	case WEAPON::SPLIT:
		break;
	case WEAPON::ONLYROTATE:
	{
		m_theta += _dt;
		static Vector2f radius = Vector2f(_enemy.getGlobalBounds().width / 2, _enemy.getGlobalBounds().height / 2);
		radius += Vector2f(10.f*_dt, 5.f*_dt);
		m_sprite.setPosition(_enemy.getPosition().x + radius.x * cosf(m_theta),
			_enemy.getPosition().y + radius.y * sinf(m_theta));
		
	}
		break;
	case WEAPON::ROTATE:
	{
		// 무조건 돈다
		m_theta += _dt;

		// 일정 시간이 되면 아래로 무브한다.
		if (m_clock.getElapsedTime().asSeconds() > 5.f)
		{
			m_clock.restart();
		}
		else if (m_clock.getElapsedTime().asSeconds() > 2.5f)
		{
			m_sprite.move(0.f, 700.f * _dt);
		}
		else
		{
			m_sprite.setPosition(_enemy.getPosition().x + _enemy.getGlobalBounds().width / 2 * cosf(m_theta),
				_enemy.getPosition().y + _enemy.getGlobalBounds().height / 2 * sinf(m_theta));
		}
	}
		break;
	}
	
}

void Bullet::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
}

