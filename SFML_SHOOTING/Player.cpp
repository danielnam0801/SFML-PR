#include "pch.h"
#include "Player.h"

Player::Player(bool player1, Vector2f _pos, float _initVelocity, float _maxvelocity, Vector2f _dir, float _acc, float _dcc)
	: m_isplayer1(player1)
{
	m_Sprite.setPosition(_pos);
	m_Sprite.setTexture(ResMgr::GetInst()->GetTexture("Player"));
	m_Sprite.setScale(0.12f, 0.12f);

	m_shootTimerMax = 25;
	m_shootTimer = m_shootTimerMax;
	m_damageTimerMax = 10;
	m_damageTimer = m_damageTimerMax;
	m_hpMax = 10;
	m_hp = m_hpMax;
	
	m_level = 1;
	m_maxVelocity = 20.f;
	m_acceleration = 1.f;
	m_frictionForce = 0.5f;

	m_hpText.setFont(ResMgr::GetInst()->GetFont("Font"));
	m_hpText.setPosition(m_Sprite.getPosition());
}

void Player::Update(const float& _dt)
{
	//Update Timer
	if (m_shootTimer < m_shootTimerMax)
		m_shootTimer++;
	if (m_damageTimer < m_damageTimerMax)
		m_damageTimer++;
	MoveMent();
	for (size_t i = 0; i < m_vecbullet.size(); ++i)
	{
		if (m_vecbullet[i].Update(_dt))
			m_vecbullet.erase(m_vecbullet.begin() + i);
		else
			++i;
	}
	SetHpText();

}

void Player::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_Sprite);
	for (size_t i = 0; i < m_vecbullet.size(); ++i)
		m_vecbullet[i].Render();
	WindowMgr::GetInst()->GetWindow().draw(m_hpText);
}

void Player::MoveMent()
{
	if (m_isplayer1)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			m_dir = { 0.f, -1.f };
			//m_Sprite.move(0.f, -10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			m_dir = { 0.f, 1.f };
			//m_Sprite.move(0.f, 10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			m_dir = { -1.f, 0.f };
			if(m_curVelocity.x > -m_maxVelocity)
				m_curVelocity.x += m_dir.x * m_acceleration;
			//m_Sprite.move(-10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			//m_Sprite.move(10.f, 0.f);
		}

		m_curVelocity.x += m_frictionForce;
		m_curVelocity.x -= m_frictionForce;
		if (Keyboard::isKeyPressed(Keyboard::Space) 
			&& m_shootTimer >= m_shootTimerMax)
		{
			m_vecbullet.push_back(Bullet(m_Sprite.getPosition()));
			m_shootTimer = 0;
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			//m_Sprite.move(0.f, -10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			//m_Sprite.move(0.f, 10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Left))
		{
			//m_Sprite.move(-10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
		{
			//m_Sprite.move(10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::RShift)
			&& m_shootTimer >= m_shootTimerMax)
		{
			m_vecbullet.push_back(Bullet(m_Sprite.getPosition()));
			m_shootTimer = 0;
		}
	}
	m_Sprite.move(m_curVelocity);
}

void Player::Fight(const float& _dt)
{
	
}

void Player::SetHpText()
{
	m_hpText.setString("                " + std::to_string(m_hp));
}
