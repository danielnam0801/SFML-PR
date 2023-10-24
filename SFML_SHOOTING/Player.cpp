#include "pch.h"
#include "Player.h"
#include "FrontGun.h"

Player::Player(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, Keyboard::Key space,
	 float _initVelocity, float _maxvelocity,
	Vector2f _dir, float _acc, float _dcc)
{
	m_Sprite.setTexture(ResMgr::GetInst()->GetTexture("Player"));
	m_Sprite.setScale(0.12f, 0.12f);
	m_Sprite.setPosition
	(
		Vector2f(WindowMgr::GetInst()->GetWindow().getSize().x / 2,
			WindowMgr::GetInst()->GetWindow().getSize().y - m_Sprite.getGlobalBounds().height - 20)
	);

	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2,
		m_Sprite.getGlobalBounds().height / 2);

	m_maingun.setTexture(ResMgr::GetInst()->GetTexture("Gun0"));
	m_maingun.setOrigin(m_maingun.getGlobalBounds().width / 2,
		m_maingun.getGlobalBounds().height / 2);

	/*m_maingun.setPosition(Vector2f{
		m_Sprite.getGlobalBounds().width / 2,
		m_Sprite.getGlobalBounds().height
	});*/

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

	inputs.resize((int)InputType::END);
	inputs[(int)InputType::UP] = up;
	inputs[(int)InputType::DOWN] = down;
	inputs[(int)InputType::LEFT] = left;
	inputs[(int)InputType::RIGHT] = right;
	inputs[(int)InputType::Attack] = space;

	m_curWeapon = WEAPON::LASER_R;
	UiInit();
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
	Accessorypdate();
	Fight(_dt);
	UiUpdate();
}

void Player::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_Sprite);
	WindowMgr::GetInst()->GetWindow().draw(m_maingun);
	for (size_t i = 0; i < m_vecbullet.size(); ++i)
		m_vecbullet[i].Render();
	WindowMgr::GetInst()->GetWindow().draw(m_hpText);
}

void Player::MoveMent()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
		m_curWeapon = WEAPON::LASER_R;
	if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
		m_curWeapon = WEAPON::MISSILE01;

	if (Keyboard::isKeyPressed(inputs[(int)InputType::UP]))
	{
		m_dir = { 0.f, -1.f };
		if (m_curVelocity.y > -m_maxVelocity)
			m_curVelocity.y += m_dir.y * m_acceleration;
	}
	if (Keyboard::isKeyPressed(inputs[(int)InputType::DOWN]))
	{
		m_dir = { 0.f, 1.f };
		if (m_curVelocity.y < m_maxVelocity)
			m_curVelocity.y += m_dir.y * m_acceleration;
	}
	if (Keyboard::isKeyPressed(inputs[(int)InputType::LEFT]))
	{
		m_dir = { -1.f, 0.f };
		if (m_curVelocity.x > -m_maxVelocity)
			m_curVelocity.x += m_dir.x * m_acceleration;
	}
	if (Keyboard::isKeyPressed(inputs[(int)InputType::RIGHT]))
	{
		m_dir = { 1.f, 0.f };
		if (m_curVelocity.x > -m_maxVelocity)
			m_curVelocity.x += m_dir.x * m_acceleration;
	}

	if (m_curVelocity.x > 0)
	{
		m_curVelocity.x -= m_frictionForce;
		if (m_curVelocity.x < 0)
			m_curVelocity.x = 0;
	}
	else if (m_curVelocity.x < 0)
	{
		m_curVelocity.x += m_frictionForce;
		if (m_curVelocity.x > 0)
			m_curVelocity.x = 0;
	}

	if (m_curVelocity.y > 0)
	{
		m_curVelocity.y -= m_frictionForce;
		if (m_curVelocity.y < 0)
			m_curVelocity.y = 0;
	}
	else if (m_curVelocity.y < 0)
	{
		m_curVelocity.y += m_frictionForce;
		if (m_curVelocity.y > 0)
			m_curVelocity.y = 0;
	}

	m_Sprite.move(m_curVelocity);
}

void Player::Fight(const float& _dt)
{
	if (Keyboard::isKeyPressed(inputs[(int)InputType::Attack])
		&& m_shootTimer >= m_shootTimerMax)
	{
		switch (m_curWeapon)
		{
		case WEAPON::LASER_R:
			m_vecbullet.push_back(Bullet
			(
				Vector2f{m_playercenter.x - 5.f, m_playercenter.y - 70.f}, 2, 50,
				Vector2f{ 0,-1.f }, 2.f, WEAPON::LASER_R)
			);
			break;
		case WEAPON::MISSILE01:
			m_vecbullet.push_back(Bullet
			(
				Vector2f{ m_playercenter.x - 20.f, m_playercenter.y - 70.f }, 2, 50,
				Vector2f{ 0,-1.f }, 2.f, WEAPON::MISSILE01)
			);
			m_vecbullet.push_back(Bullet
			(
				Vector2f{ m_playercenter.x + 15.f, m_playercenter.y - 70.f }, 2, 50,
				Vector2f{ 0,-1.f }, 2.f, WEAPON::MISSILE01)
			);
			break;
		default:
			break;
		}
		m_maingun.move(0.f, 30.f);
		m_shootTimer = 0;
	}

}

void Player::UiInit()
{
	m_hpText.setString("                " + std::to_string(m_hp));
}

void Player::UiUpdate()
{
}

void Player::UiRender()
{
}

void Player::Accessorypdate()
{
	m_playercenter = Vector2f(m_Sprite.getPosition().x
		+ m_Sprite.getGlobalBounds().width / 2.5f, m_Sprite.getPosition().y);
	m_maingun.setPosition(m_playercenter);

}

