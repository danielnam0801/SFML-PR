#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Vector2f _pos, float _maxv)
{
	m_Sprite.setTexture(ResMgr::GetInst()->GetTexture("Bullet"));
	m_maxVelocity = m_curVelocity = _maxv;
	m_Sprite.setScale(0.07f, 0.07f);
	m_Sprite.setPosition(_pos);
	m_clock.restart();
}

void Bullet::Update(const float& _dt)
{
	MoveMent();
}

void Bullet::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_Sprite);
}

void Bullet::MoveMent()
{
	if (m_clock.getElapsedTime().asSeconds() >= 1)
	{
		m_curVelocity = m_maxVelocity;
	}
	else
	{
		m_curVelocity = m_maxVelocity / 2 * m_clock.getElapsedTime().asSeconds();
	}
	m_Sprite.move(0.f, m_curVelocity);
}
