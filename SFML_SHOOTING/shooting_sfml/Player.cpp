#include "pch.h"
#include "Player.h"
Player::Player(Keyboard::Key _up, Keyboard::Key _down, Keyboard::Key _left
	, Keyboard::Key _right, Keyboard::Key _shoot, int _num)
{
	m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Player"));
	m_sprite.setScale(0.12f,0.12f);
	m_sprite.setPosition(WindowMgr::GetInst()->GetWindow().getSize().x / 2, 
		WindowMgr::GetInst()->GetWindow().getSize().y - m_sprite.getGlobalBounds().height - 20);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width /2
					, m_sprite.getGlobalBounds().height/ 2);
	m_mainGun.setTexture(ResMgr::GetInst()->GetTexture("Gun01"));
	m_mainGun.setOrigin(m_mainGun.getGlobalBounds().width / 2
					,m_mainGun.getGlobalBounds().height / 2);

	m_num = _num;
	// value init
	m_shootTimerMax = 25;
	m_shootTimer = m_shootTimerMax;
	m_damageTimerMax = 10;
	m_damageTimer = m_damageTimerMax;
	m_hpMax = 10;
	m_hp = m_hpMax;
	
	
	m_level = 1;
	m_exp = 0;
	m_expNext = 10 + m_level * (m_level + 1) * 25 - 50;
	m_statPoints = 0;
	m_str = 0;
	m_dex = 0;
	m_endurance = 0;
	m_defense = 0;
	
	m_maxVelocity = 100.f;
	m_acceleration = 50.f;
	m_frictionForce = 0.5f;
	m_curVelocity = Vector2f(10.f, 10.f);
	// controls
	m_controls[(int)CONTORLS::UP] = _up;
	m_controls[(int)CONTORLS::DOWN] = _down;
	m_controls[(int)CONTORLS::LEFT] = _left;
	m_controls[(int)CONTORLS::RIGHT] = _right;
	m_controls[(int)CONTORLS::SHOOT] = _shoot;

	m_eCurWeapon = WEAPON::LASER_R;
	m_text.setOrigin(m_text.getGlobalBounds().width + 50.f, m_text.getGlobalBounds().height);
	m_text.setStyle(sf::Text::Style::Bold);
	//m_hp -= 1;
	UiInit();
}
void Player::UiInit()
{
	m_text.setFont(ResMgr::GetInst()->GetFont("Dosis Font"));
	m_text.setCharacterSize(12);
	m_text.setFillColor(Color::White);
	//m_text.setColor(Color::White);
	static int count = 1;
	m_text.setString(std::to_string(count++));

	m_hpBar.setSize(Vector2f(50.f, 10.f));
	m_hpBar.setFillColor(Color::Red);
	m_hpBar.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height);
	m_hpBarback = m_hpBar;
	m_hpBarback.setFillColor(Color(25, 25, 25, 200));
	m_expBar.setSize(Vector2f(50.f, 10.f));
	m_expBar.setFillColor(Color(0.f, 200.f, 50.f, 200.f));
	m_expBar.setPosition(m_hpBar.getPosition().x, 
		m_hpBar.getPosition().y + m_hpBar.getGlobalBounds().height);
	m_expBar.setScale((float)m_exp / (float)m_expNext, 1.f);

}
void Player::MoveMent(const float& _dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
		m_eCurWeapon = WEAPON::LASER_R;
	if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
		m_eCurWeapon = WEAPON::MISSILE01;

	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::UP]))
	{
		m_dir = Vector2f(0.f, -1.f);
		if (m_curVelocity.y > -m_maxVelocity)
			m_curVelocity.y += m_dir.y * m_acceleration *_dt;
	}
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::DOWN]))
	{
		m_dir = Vector2f(0.f, 1.f);
		if (m_curVelocity.y < m_maxVelocity)
			m_curVelocity.y += m_dir.y * m_acceleration *_dt;
	}
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::LEFT]))
	{
		m_dir = Vector2f(-1.f,0.f);
		if(m_curVelocity.x > -m_maxVelocity)
			m_curVelocity.x += m_dir.x * m_acceleration *_dt;
	}
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::RIGHT]))
	{
		m_dir = Vector2f(1.f, 0.f);
		if (m_curVelocity.x < m_maxVelocity)
			m_curVelocity.x += m_dir.x * m_acceleration *_dt;

	}
	// 마찰력.
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
	m_sprite.move(m_curVelocity);
}

void Player::Fight(const float& _dt)
{
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::SHOOT])
		&& m_shootTimer >= m_shootTimerMax)
	{
		switch (m_eCurWeapon)
		{
		case WEAPON::LASER_R:
		{
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x - 5.f, m_playercenter.y -70.f),
				2.f, 50.f, Vector2f(0.f, -1.f), 50.f,WEAPON::LASER_R));
		}
			break;
		case WEAPON::MISSILE01:
		{
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x - 20.f, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(0.f, -1.f), 20.f, WEAPON::MISSILE01));
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x + 15.f, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(0.f, -1.f), 20.f, WEAPON::MISSILE01));

		}
			break;
		}
		m_mainGun.move(0.f, 400.f * _dt);
		m_shootTimer = 0; // 타이머 리셋
	}
}



void Player::UiUpdate()
{
	m_text.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y);
	m_text.setString(std::to_string(m_num) + "P							" + 
		std::to_string(m_hp) + " / " + 
		std::to_string(m_hpMax)+ "\n\n\n\n\n\n" + "Level: " + std::to_string(m_level));
	m_hpBar.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height);
	m_hpBarback.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height);
	m_hpBar.setScale((float)m_hp / (float)m_hpMax, 1.f);
	m_expBar.setPosition(m_hpBar.getPosition().x,
		m_hpBar.getPosition().y + m_hpBar.getGlobalBounds().height);
	m_expBar.setScale((float)m_exp / (float)m_expNext, 1.f);
}

void Player::UiRender()
{
}

void Player::AccessoryUpdate()
{
	m_mainGun.setPosition(m_playercenter);
}

void Player::Update(const float& _dt, vector<Enemy>& _vecenemy)
{
	// Update Timer
	if (m_shootTimer < m_shootTimerMax)
		m_shootTimer++;
	if (m_damageTimer < m_damageTimerMax)
		m_damageTimer++;
	MoveMent(_dt);
	if (isHit)
	{
		if (m_damageTimer >= m_damageTimerMax) {
			m_sprite.setColor(Color::White);
			isHit = false;
		}
	}
	// 플레이어 - 적 충돌
	for (size_t i = 0; i < _vecenemy.size();)
	{
		if (m_sprite.getGlobalBounds().intersects(_vecenemy[i].GetSprite().getGlobalBounds()))
		{
			int damage = _vecenemy[i].GetDamage();
			m_hp -= damage;
			m_vectextTag.push_back(TextTag("-" + std::to_string(damage), 1.f, 20.f,
				Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - 20.f),
				Vector2f(0.f, 1.f), Color::Red, 30, true));
			Hit();
			_vecenemy.erase(_vecenemy.begin() + i);
		}
		else
			++i;
	}

	// 플레이어의 총알.. 
	bool IsBulletRemoved = false;
	for (size_t i = 0; i < m_vecbullet.size(); )
	{
		if (m_vecbullet[i].Update(_dt))
			IsBulletRemoved = true;
		for (size_t j = 0; j < _vecenemy.size(); ++j)
		{
			if (m_vecbullet[i].GetSprite().getGlobalBounds().intersects(_vecenemy[j].GetSprite().getGlobalBounds()))
			{
				IsBulletRemoved = true;
				if (!_vecenemy[j].GetIsDead())
				{
					int damage = m_vecbullet[i].GetDamage();
					_vecenemy[j].TakeDamage(damage);
					m_vectextTag.push_back(TextTag("-" + std::to_string(damage),
						1.f, 20.f
						, Vector2f(_vecenemy[j].GetSprite().getPosition().x
						, _vecenemy[j].GetSprite().getPosition().y - 30.f)
						, Vector2f(0.f, -1.f), Color::Red, 30, true));
				}
				if (_vecenemy[j].GetIsDead())
				{
					int exp = _vecenemy[j].GetHpMax();
					GainExp(exp);
					m_vectextTag.push_back(TextTag("+" + std::to_string(exp),
						1.f, 20.f
						, Vector2f(m_sprite.getPosition().x
						, m_sprite.getPosition().y - 30.f)
						, Vector2f(0.f, -1.f), Color::Green, 20, true));
				}
			}
		}
		
		if (IsBulletRemoved)
		{
			m_vecbullet.erase(m_vecbullet.begin() + i);
			IsBulletRemoved = false;
		}
		else
			++i;
	}

	TextTagUpdate(_dt);
	m_playercenter = Vector2f(m_sprite.getPosition().x + 
		m_sprite.getGlobalBounds().width / 2.5f,m_sprite.getPosition().y);

	AccessoryUpdate();
	Fight(_dt);
	UiUpdate();
}

void Player::Render()
{
	for (auto& e : m_vecbullet)
		e.Render();
	WindowMgr::GetInst()->GetWindow().draw(m_mainGun);
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
	WindowMgr::GetInst()->GetWindow().draw(m_text);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBarback);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBar);
	WindowMgr::GetInst()->GetWindow().draw(m_expBar);
	
	for (auto& e : m_vectextTag)
		e.Render();
}

void Player::TakeDamage(int _damage)
{
	m_hp -= _damage;
}

void Player::Hit()
{
	isHit = true;
	m_damageTimer = 0;
	m_sprite.setColor(Color::Red);
}

bool Player::GainExp(int _exp)
{
	m_exp += _exp;
	if (m_exp >= m_expNext)
	{
		m_level++;
		m_statPoints++;
		m_exp -= m_expNext;
		m_expNext = m_level * (m_level + 1) * 25 - 50;
		m_hp = m_hpMax;
		m_vectextTag.push_back(TextTag("level up!", 1.f, 20.f,
			Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - 60),
			Vector2f(0.f, 1.f), Color::Blue, 40, true));
		return true;
	}
	return false;
}

void Player::TextTagUpdate(const float& _dt)
{
	for (size_t i = 0; i < m_vectextTag.size();)
	{
		m_vectextTag[i].Update(_dt);
		if (m_vectextTag[i].GetIsErase())
			m_vectextTag.erase(m_vectextTag.begin() + i);
		else
			++i;
	}
}

