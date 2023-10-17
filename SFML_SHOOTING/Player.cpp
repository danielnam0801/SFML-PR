#include "pch.h"
#include "Player.h"

Player::Player(bool player1)
	: m_isplayer1(player1)
{
	m_Sprite.setTexture(ResMgr::GetInst()->GetTexture("Player"));
	m_Sprite.setScale(0.12f, 0.12f);
}

void Player::Update(const float& _dt)
{
	MoveMent();
	for (size_t i = 0; i < m_vecbullet.size(); ++i)
		m_vecbullet[i].Update(_dt);
}

void Player::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_Sprite);
	for (size_t i = 0; i < m_vecbullet.size(); ++i)
		m_vecbullet[i].Render();
}

void Player::MoveMent()
{
	if (m_isplayer1)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			m_Sprite.move(0.f, -10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			m_Sprite.move(0.f, 10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			m_Sprite.move(-10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			m_Sprite.move(10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			m_vecbullet.push_back(Bullet(m_Sprite.getPosition()));
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			m_Sprite.move(0.f, -10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			m_Sprite.move(0.f, 10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Left))
		{
			m_Sprite.move(-10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
		{
			m_Sprite.move(10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::RShift))
		{
			m_vecbullet.push_back(Bullet(m_Sprite.getPosition()));
		}
	}

}
