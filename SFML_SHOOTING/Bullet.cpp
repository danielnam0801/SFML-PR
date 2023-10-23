#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Vector2f _pos, float _initvelocity,
	float _maxv, Vector2f curVelocity, Vector2f dir)
{
	m_Sprite.setTexture(ResMgr::GetInst()->GetTexture("Bullet"));
	m_maxVelocity = _maxv;
	m_accerlation;
	m_dir = _dr;
	m_curVelocity = Vector2f(_initvelocity * m_dir.x, _initvelocity * m_dir.y);
	m_Sprite.setScale(0.07f, 0.07f);
	m_Sprite.setPosition(_pos);
	m_clock.restart();
}

bool Bullet::Update(const float& _dt)
{
	MoveMent();
	if (m_Sprite.getPosition().y < 0)
		return true;
	return false;
}

void Bullet::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_Sprite);
}

void Bullet::MoveMent()
{
	if (m_accerlation > 0.f)
	{
		if(m_curVelocity.x < m_maxVelocity)
		m_curVelocity.x += m_accerlation * m_dir.x;
		if(m_curVelocity.y < m_maxVelocity)
		m_curVelocity.y += m_accerlation * m_dir.y;
	}
	else
	{
		m_curVelocity = Vector2f(m_maxVelocity * m_dir.x,
			m_maxVelocity * m_dir.y);
	}
	m_Sprite.move(0.f, m_curVelocity);
}
