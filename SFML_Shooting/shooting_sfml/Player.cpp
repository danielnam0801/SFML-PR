#include "pch.h"
#include "Player.h"
Player::Player(Keyboard::Key _up, Keyboard::Key _down, Keyboard::Key _left
	, Keyboard::Key _right, Keyboard::Key _shoot, Keyboard::Key _bomb, int _num)
{
	m_timermax = 10.f;
	m_timer = 0;
	m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Player"));
	m_sprite.setScale(0.12f, 0.12f);
	m_sprite.setPosition(WindowMgr::GetInst()->GetWindow().getSize().x / 2,
		WindowMgr::GetInst()->GetWindow().getSize().y - m_sprite.getGlobalBounds().height - 20);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2
		, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setColor(Color(10, 10, 10, 150));

	m_mainGun.setTexture(ResMgr::GetInst()->GetTexture("Gun01"));
	m_mainGun.setOrigin(m_mainGun.getGlobalBounds().width / 2
		, m_mainGun.getGlobalBounds().height / 2);

	Vector2f vec = Vector2f(m_playercenter.x + 10, m_playercenter.y + 20);
	m_aura.setTexture(ResMgr::GetInst()->GetTexture("AURA8"));
	m_aura.setOrigin(m_aura.getGlobalBounds().width / 2,
		m_aura.getGlobalBounds().height / 2);
	m_aura.setPosition(vec);
	float scale = 0.7f;
	m_aura.setScale(scale, scale);
	m_auracntmax = 11;
	m_auracurnum = 8;

	m_cPit.setTexture(ResMgr::GetInst()->GetTexture("CPIT2"));
	m_cPit.setOrigin(m_cPit.getGlobalBounds().width / 2,
		m_cPit.getGlobalBounds().height / 2);
	m_cPit.setPosition(vec);
	m_cPit.setScale(scale, scale);
	m_cpitcntmax = 16;
	m_cpitcurnum = 2;

	m_lwing.setTexture(ResMgr::GetInst()->GetTexture("WINGLEFT2"));
	m_lwing.setOrigin(m_lwing.getGlobalBounds().width / 2,
		m_lwing.getGlobalBounds().height / 2);
	m_lwing.setPosition(vec);
	m_lwing.setScale(scale, scale);
	m_lwingcntmax = 13;
	m_lwingcurnum = 2;

	m_rwing.setTexture(ResMgr::GetInst()->GetTexture("WINGRIGHT2"));
	m_rwing.setOrigin(m_rwing.getGlobalBounds().width / 2,
		m_rwing.getGlobalBounds().height / 2);
	m_rwing.setPosition(vec);
	m_rwing.setScale(scale, scale);
	m_rwingcntmax = 13;
	m_rwingcurnum = 2;

	m_num = _num;
	// value init
	m_shootTimerMax = 25;
	m_shootTimer = m_shootTimerMax;
	m_damageTimerMax = 10;
	m_damageTimer = m_damageTimerMax;
	m_freezeTimer = 5;
	m_freezeTimerMax = m_freezeTimer;
	m_changeTimer = 6;
	m_changeTimer = m_changeTimerMax;
	m_hpMax = 10;
	m_hp = m_hpMax;
	m_statPoints = 0;
	m_str = 0; m_dex = 0; m_endurance = 0; m_defense = 0;
	m_level = 1;
	m_exp = 0;
	m_score = 0;
	m_expNext = 10 + m_level * (m_level + 1) * 25 - 50;

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
	m_controls[(int)CONTORLS::BOMB] = _bomb;

	m_eCurWeapon = WEAPON::LASER_R;
	m_text.setOrigin(m_text.getGlobalBounds().width + 50.f, m_text.getGlobalBounds().height);
	m_text.setStyle(sf::Text::Style::Bold);

	m_infoText.setCharacterSize(120);
	m_infoText.setStyle(sf::Text::Style::Bold);
	m_infoText.setFont(ResMgr::GetInst()->GetFont("Dosis Font"));
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

}
void Player::MoveMent(const float& _dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
		m_eCurWeapon = WEAPON::LASER_R;
	if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
		m_eCurWeapon = WEAPON::MISSILE01;
	if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
		m_eCurWeapon = WEAPON::MISSILE02;

	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::UP]))
	{
		m_dir = Vector2f(0.f, -1.f);
		if (m_curVelocity.y > -m_maxVelocity)
			m_curVelocity.y += m_dir.y * m_acceleration * _dt;
	}
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::DOWN]))
	{
		m_dir = Vector2f(0.f, 1.f);
		if (m_curVelocity.y < m_maxVelocity)
			m_curVelocity.y += m_dir.y * m_acceleration * _dt;
	}
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::LEFT]))
	{
		m_dir = Vector2f(-1.f, 0.f);
		if (m_curVelocity.x > -m_maxVelocity)
			m_curVelocity.x += m_dir.x * m_acceleration * _dt;
	}
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::RIGHT]))
	{
		m_dir = Vector2f(1.f, 0.f);
		if (m_curVelocity.x < m_maxVelocity)
			m_curVelocity.x += m_dir.x * m_acceleration * _dt;
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
	// window collision
	if (m_sprite.getPosition().x - m_sprite.getGlobalBounds().width / 2 <= 0)
	{
		m_sprite.setPosition(0.f + m_sprite.getGlobalBounds().width / 2,
			m_sprite.getPosition().y);
		m_curVelocity.x = 0.f;
	}
	else if (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width * 1.5f >= SCREEN_WIDTH)
	{
		m_sprite.setPosition(SCREEN_WIDTH - m_sprite.getGlobalBounds().width * 1.5f,
			m_sprite.getPosition().y);

		m_curVelocity.x = 0.f;
	}
	if (m_sprite.getPosition().y - m_sprite.getGlobalBounds().height / 2 <= 0)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, 0.f + m_sprite.getGlobalBounds().height / 2);
		m_curVelocity.y = 0.f;
	}
	else if (m_sprite.getPosition().y + m_sprite.getGlobalBounds().height * 2 >= SCREEN_HEIGHT)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, SCREEN_HEIGHT - m_sprite.getGlobalBounds().height * 2);
		m_curVelocity.y = 0.f;
	}
	m_normalDir = Normalize(m_curVelocity, vectorLength(m_curVelocity));

}

void Player::Fight(const float& _dt)
{
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::BOMB]))
	{
		m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x, m_playercenter.y),
			2.f, 50.f, Vector2f(0.f, -1.f), 20.f, WEAPON::BOMB));
	}
	if (Keyboard::isKeyPressed(m_controls[(int)CONTORLS::SHOOT])
		&& m_shootTimer >= m_shootTimerMax)
	{
		switch (m_eCurWeapon)
		{
		case WEAPON::LASER_R:
		{
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x - 5.f, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(0.f, -1.f), 50.f, WEAPON::LASER_R));
		}
		break;
		case WEAPON::MISSILE01:
		{
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x - 20.f, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(-0.25f, -1.f), 20.f, WEAPON::MISSILE01));
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(0.f, -1.f), 20.f, WEAPON::MISSILE01));
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x + 20.f, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(0.25f, -1.f), 20.f, WEAPON::MISSILE01));
		}
		break;
		case WEAPON::MISSILE02:
		{
			Vector2f circlebullet[16] = {
				{0,3},{0,-3}, {3,0}, {-3,0},
				{1,3}, {1,-3}, {-1,3}, {-1,-3},
				{3,1}, {3,-1}, {-3,1}, {-3,-1},
				{2,2}, {-2,-2}, {-2,2}, {2,-2} };
			for (int i = 0; i < 16; i++)
			{
				m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x, m_playercenter.y - 120.f),
					2.f, 50.f, Vector2f(circlebullet[i]), 2.f, WEAPON::MISSILE02));
			}
		}
		case WEAPON::DOUBLE:
		{
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x - 5.f, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(0.f, -1.f), 50.f, WEAPON::LASER_R));
			m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x + 5.f, m_playercenter.y - 70.f),
				2.f, 50.f, Vector2f(0.f, -1.f), 50.f, WEAPON::LASER_R));
		}
		case WEAPON::TRIPLE:
		{

		}
		break;
		case WEAPON::BOMB:
		{
		
		}
		m_mainGun.move(0.f, 400.f * _dt);
		m_shootTimer = 0; // 타이머 리셋
		}
		if (m_bombClock.getElapsedTime().asSeconds() >= 1.f)
		{
			for (size_t i = 0; i < m_vecbullet.size();)
			{
				if (m_vecbullet[i].GetType() == WEAPON::BOMB)
				{
					Vector2f circlebullet[16] = {
				{0,3},{0,-3}, {3,0}, {-3,0},
				{1,3}, {1,-3}, {-1,3}, {-1,-3},
				{3,1}, {3,-1}, {-3,1}, {-3,-1},
				{2,2}, {-2,-2}, {-2,2}, {2,-2} };
					for (int j = 0; j < 16; i++)
					{
						m_vecbullet.push_back(Bullet(Vector2f(m_playercenter.x, m_playercenter.y - 120.f),
							2.f, 50.f, Vector2f(circlebullet[j]), 2.f, WEAPON::MISSILE02));
					}
					m_vecbullet.erase(m_vecbullet.begin() + i);
				}
				else
					i++;
			}
		}
		
	}
}
void Player::UiUpdate()
{
	m_text.setPosition(m_sprite.getPosition().x + 10,
		m_sprite.getPosition().y);
	m_text.setString(std::to_string(m_num) + "P							" +
		std::to_string(m_hp) + " / " +
		std::to_string(m_hpMax) + "\n\n\n\n\n\n" + "Level: " + std::to_string(m_level));
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
	AccessoryChange();
	m_mainGun.setPosition(m_playercenter);

	m_cPit.setPosition(m_playercenter.x + 2, m_playercenter.y + 45);
	m_aura.setPosition(m_playercenter.x + 2, m_playercenter.y + 45);

	m_lwing.setPosition(m_playercenter.x + 2 - abs(m_curVelocity.x), m_playercenter.y + 45 - m_curVelocity.y);
	m_rwing.setPosition(m_playercenter.x + 2 + abs(m_curVelocity.x), m_playercenter.y + 45 - m_curVelocity.y);
}

void Player::AccessoryChange()
{
	if (m_changeTimer >= m_changeTimerMax)
	{
		if (Keyboard::isKeyPressed(Keyboard::F1))
		{
			if (m_lwingcurnum < m_lwingcntmax)
				m_lwingcurnum++;
			else
				m_lwingcurnum = 1;

			m_lwing.setTexture(ResMgr::GetInst()->GetTexture("WINGLEFT" + std::to_string(m_lwingcurnum)));
		}
		if (Keyboard::isKeyPressed(Keyboard::F2))
		{
			if (m_rwingcurnum < m_rwingcntmax)
				m_rwingcurnum++;
			else
				m_rwingcurnum = 1;

			m_rwing.setTexture(ResMgr::GetInst()->GetTexture("WINGRIGHT" + std::to_string(m_rwingcurnum)));
		}
		if (Keyboard::isKeyPressed(Keyboard::F3))
		{
			if (m_auracurnum < m_auracntmax)
				m_auracurnum++;
			else
				m_auracurnum = 1;

			m_aura.setTexture(ResMgr::GetInst()->GetTexture("AURA" + std::to_string(m_auracurnum)));
		}
		if (Keyboard::isKeyPressed(Keyboard::F4))
		{
			if (m_cpitcurnum < m_cpitcntmax)
				m_cpitcurnum++;
			else
				m_cpitcurnum = 1;

			m_cPit.setTexture(ResMgr::GetInst()->GetTexture("CPIT" + std::to_string(m_cpitcurnum)));
		}
		m_changeTimer = 0;
	}
}

void Player::TimerUpdate(const float& _dt)
{
	// Update Timer
	if (m_shootTimer < m_shootTimerMax)
		m_shootTimer++;
	if (m_damageTimer < m_damageTimerMax)
		m_damageTimer++;
	if (m_changeTimer < m_changeTimerMax)
		m_changeTimer++;
	
	//m_timer -= 1.f;
	if (m_timer > 0.f)
	{
		m_timer -= _dt;
		if (m_timer <= 0.f)
		{
			m_timer = 0.f;
		}
	}
}

void Player::CollisionEnemy(const float& _dt, vector<Enemy>& _vecenemy)
{
	// 플레이어 - 적 충돌
	for (size_t i = 0; i < _vecenemy.size(); ++i)
	{
		if (m_clock.getElapsedTime().asSeconds() > 2.f)
		{
			if (m_sprite.getGlobalBounds().intersects(_vecenemy[i].GetSprite().getGlobalBounds()))
			{
				TakeDamage(_vecenemy[i].GetDamage());
				m_vectextTag.push_back(TextTag("-" + std::to_string(_vecenemy[i].GetDamage()), 1.f, 20.f,
					Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - 20.f),
					Vector2f(0.f, 1.f), Color::Red, 30, true));
				m_freezeTimer = 0;
				m_curVelocity = { 0,0 };

				m_lwing.setColor(Color::Red);
				m_rwing.setColor(Color::Red);
				m_cPit.setColor(Color::Red);

				m_clock.restart();
			}
			else
			{
				m_lwing.setColor(Color::White);
				m_rwing.setColor(Color::White);
				m_cPit.setColor(Color::White);
			}
		}
	}
}

void Player::BulletCollisionEnemy(const float& _dt, vector<Enemy>& _vecenemy)
{
	// 플레이어의 총알 - 적 충돌
	bool IsBulletRemoved = false;
	for (size_t i = 0; i < m_vecbullet.size();)
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
						1.f, 20.f,
						Vector2f(_vecenemy[j].GetSprite().getPosition().x,
							_vecenemy[j].GetSprite().getPosition().y - 30.f),
						Vector2f(0.f, -1.f), Color::Red, 30, true));
				}
				if (_vecenemy[j].GetIsDead())
				{
					int exp = _vecenemy[j].GetHpMax();
					m_score += _vecenemy[j].GetHpMax();
					m_timer = m_timermax;
					//m_exp += exp;
					if (GainExp(exp))
					{
						m_vectextTag.push_back(TextTag("LEVEL UP!!",
							1.f, 20.f,
							Vector2f(m_sprite.getPosition().x,
								m_sprite.getPosition().y - 60.f),
							Vector2f(-1.f, 0.f), Color::Cyan, 20, true));
					}
					m_vectextTag.push_back(TextTag("+" + std::to_string(exp),
						1.f, 20.f,
						Vector2f(m_sprite.getPosition().x,
							m_sprite.getPosition().y - 30.f),
						Vector2f(0.f, -1.f), Color::Green, 20, true));
				}
			}
		}
		//m_vecbullet.erase(m_vecbullet.begin() + i);
		if (IsBulletRemoved)
		{
			m_vecbullet.erase(m_vecbullet.begin() + i);
			IsBulletRemoved = false;
		}
		else
			++i;
	}
}

void Player::Update(const float& _dt, vector<Enemy>& _vecenemy)
{
	TimerUpdate(_dt);
	if (m_freezeTimer < m_freezeTimerMax)
		m_freezeTimer++;
	else
		MoveMent(_dt);

	CollisionEnemy(_dt, _vecenemy);

	BulletCollisionEnemy(_dt, _vecenemy);

	TextTagUpdate(_dt);
	m_playercenter = Vector2f(m_sprite.getPosition().x +
		m_sprite.getGlobalBounds().width / 2.5f, m_sprite.getPosition().y);

	AccessoryUpdate();
	Fight(_dt);
	UiUpdate();
}

void Player::Render()
{
	for (auto& e : m_vecbullet)
		e.Render();
	WindowMgr::GetInst()->GetWindow().draw(m_aura);
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
	WindowMgr::GetInst()->GetWindow().draw(m_cPit);
	WindowMgr::GetInst()->GetWindow().draw(m_mainGun);
	WindowMgr::GetInst()->GetWindow().draw(m_lwing);
	WindowMgr::GetInst()->GetWindow().draw(m_rwing);
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
	if (m_hp < 0)
		m_hp = 0;
	m_curVelocity -= m_normalDir * 10.f;
}

bool Player::GainExp(int _exp)
{
	m_exp += _exp;
	// 레벨업
	if (m_exp >= m_expNext)
	{
		m_level++;
		m_statPoints++;
		m_str++;
		m_dex++;
		m_endurance++;
		m_defense++;

		m_exp -= m_expNext;
		m_expNext = m_level * (m_level + 1) * 25 - 50;

		m_hpMax = 10.f + m_endurance * 5;
		m_hp = m_hpMax;
		m_damage = m_str + 1;
		m_damageMax = m_str * 2 + 3;

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

void Player::ItemAbillity(ITEM_TYPE _eType)
{
	switch (_eType)
	{
	case ITEM_TYPE::HP_KIT:
		m_hp = m_hpMax;
		break;
	case ITEM_TYPE::STAT_POINT:
		m_statPoints += 1;
		break;
	case ITEM_TYPE::HPMAXUP:
		m_hpMax += 20;
		break;
	case ITEM_TYPE::DOUBLE:
		m_eCurWeapon = WEAPON::DOUBLE;
		break;
	case ITEM_TYPE::TRIPLE:
		m_eCurWeapon = WEAPON::TRIPLE;
		break;
	case ITEM_TYPE::PIERCING:
		break;
	case ITEM_TYPE::SHILED:
		break;
	default:
		break;
	}
}

