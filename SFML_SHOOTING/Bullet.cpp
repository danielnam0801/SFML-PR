#include "pch.h"
#include "Bullet.h"


Bullet::Bullet(Vector2f _pos, float _initvelocity, float _maxv, Vector2f dir, float _acc, WEAPON _weapon)
{
	switch (_weapon)
	{
	case WEAPON::LASER_R:
		m_Sprite.setTexture(ResMgr::GetInst()->GetTexture("Laser"));
		m_Sprite.setScale(0.2f, 0.2f);
		break;
	case WEAPON::MISSILE01:
		m_Sprite.setTexture(ResMgr::GetInst()->GetTexture("Bullet"));
		m_Sprite.setScale(0.07f, 0.07f);
		break;
	default:
		break;
	}
	m_maxVelocity = _maxv;
	m_acceleration = _acc;
	m_dir = dir;
	m_curVelocity = Vector2f(_initvelocity * m_dir.x, _initvelocity * m_dir.y);
	m_Sprite.setPosition(_pos);
}

bool Bullet::Update(const float& _dt)
{
	MoveMent();
	if (m_Sprite.getPosition().y < 0)
		return true;
	return false;
}


void Bullet::MoveMent()
{
	if (m_acceleration > 0.f)
	{
		if(m_curVelocity.x < m_maxVelocity)
		m_curVelocity.x += m_acceleration * m_dir.x;
		if(m_curVelocity.y < m_maxVelocity)
		m_curVelocity.y += m_acceleration * m_dir.y;
	}
	else
	{
		m_curVelocity = Vector2f(m_maxVelocity * m_dir.x,
			m_maxVelocity * m_dir.y);
	}
	m_Sprite.move(0, m_curVelocity.y);
}

void Bullet::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_Sprite);
}