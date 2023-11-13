#include "pch.h"
#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(Vector2f _pos, Vector2f _dir, Vector2f _scale, ENEMY _eType,
	int _hpMax, int _damagemin, int _damagemax, int _followplayernum)
{
	m_eType = _eType;

	switch (m_eType)
	{
	case ENEMY::MOVEDOWN:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Enemydown"));
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
			m_sprite.getGlobalBounds().height / 2);
		m_sprite.setRotation(270);
		m_sprite.setScale(_scale);
		m_sprite.setPosition(_pos);
	}
	break;
	case ENEMY::FOLLOW:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Enemy01"));
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
			m_sprite.getGlobalBounds().height / 2);
		m_sprite.setScale(_scale);
		m_sprite.setPosition(_pos);
	}
	break;
	case ENEMY::FOLLOWFAST:
		break;
	case ENEMY::FOLLOWSHOOT:
	case ENEMY::FOLLOWFASTSHOOT:
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("EnemyMoveShoot"));
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
			m_sprite.getGlobalBounds().height / 2);
		m_sprite.setScale(_scale);
		m_sprite.setPosition(_pos);
		break;
	case ENEMY::ELITE:
		m_centerpos = _pos;
		m_fMaxDis = SCREEN_WIDTH - m_sprite.getGlobalBounds().width * 2;
		break;
	case ENEMY::BOSS1:
		break;
	}

	m_hpMax = _hpMax;
	m_hp = m_hpMax;
	m_damagemax = _damagemax;
	m_damagemin = _damagemin;
	m_dir = _dir;
	m_hpBar.setSize(Vector2f(50.f, 10.f));
	m_hpBar.setFillColor(Color::Red);
	m_hpBar.setPosition(m_sprite.getPosition().x
		- m_sprite.getGlobalBounds().width / 2,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height / 2);
	m_hpBarback = m_hpBar;
	m_hpBarback.setFillColor(Color(25, 25, 25, 200));
	m_damageTimer = 0;
	m_damageTimerMax = 4;
	m_shootTimer = 0;
	m_shootTimerMax = 0.5;
	m_followPlayernum = _followplayernum;
}

void Enemy::TakeDamage(int _damage)
{
	m_hp -= _damage;
	m_damageTimer = m_damageTimerMax;
	if (m_hp <= 0)
		m_hp = 0;
}

bool Enemy::Update(const float& _dt, Vector2f _playerpos)
{
	MoveMent(_dt, _playerpos);
	UiUpdate();
	if (m_damageTimer > 0.f)
	{
		m_damageTimer--;
		m_sprite.setColor(Color::Red);
		m_sprite.move(m_normalizedir.x * 100.f * _dt,
			m_normalizedir.y * 100.f * _dt);
	}
	else
	{
		m_sprite.setColor(Color::White);
	}
	if (m_sprite.getPosition().y > SCREEN_HEIGHT)
		return true;
	return false;
}

void Enemy::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBarback);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBar);
	for (auto& e : m_vecBullet)
		WindowMgr::GetInst()->GetWindow().draw(e.GetSprite());
}

void Enemy::MoveMent(const float& _dt, Vector2f _playerpos)
{
	switch (m_eType)
	{
	case ENEMY::MOVEDOWN:
	{
		m_sprite.move(m_dir.x * 80.f * _dt, m_dir.y * 80.f * _dt);
	}
	break;
	case ENEMY::FOLLOW:
		// 수학이 쓰여야해.
		if (m_sprite.getPosition().y < _playerpos.y)
		{
			m_dir.x = _playerpos.x - m_sprite.getPosition().x;
			m_dir.y = _playerpos.y - m_sprite.getPosition().y;
		}
		m_normalizedir = Normalize(m_dir, vectorLength(m_dir));
		m_sprite.setRotation(atan2(m_normalizedir.y, m_normalizedir.x) * 180 / M_PI + 180);
		m_sprite.move(m_normalizedir.x * 110.f * _dt, m_normalizedir.y * 110.f * _dt);
		break;
	case ENEMY::FOLLOWFAST:
		break;
	case ENEMY::FOLLOWSHOOT:
	{

		if (m_sprite.getPosition().y < _playerpos.y)
		{
			m_dir.x = _playerpos.x - m_sprite.getPosition().x;
			m_dir.y = _playerpos.y - m_sprite.getPosition().y;
		}
		m_lookDir = _playerpos - m_sprite.getPosition();
		m_normalizelookDir = Normalize(m_lookDir, vectorLength(m_lookDir));
		m_sprite.setRotation(atan2(m_normalizelookDir.y, m_normalizelookDir.x) * 180 / M_PI + 180);
		m_normalizedir = Normalize(m_dir, vectorLength(m_dir));

		m_shootTimer += _dt;
		if (m_shootTimer > m_shootTimerMax)
		{
			m_shootTimer = 0;
			m_vecBullet.push_back(Bullet(m_sprite.getGlobalBounds().getPosition()
				, 1, 30, m_normalizelookDir, 10.0f, WEAPON::ENEMYBULLET));
		}

		m_sprite.move(m_normalizedir * 300.f * _dt);
		for (auto& e : m_vecBullet)
			e.Update(_dt);
	}
		break;
	case ENEMY::FOLLOWFASTSHOOT:
		break;
	case ENEMY::ELITE:
	{
		switch (m_eState)
		{
		case ENEMY_STATE::IDLE:
			Vector2f curpos = m_sprite.getPosition();
			curpos.x += 500.f * _dt * m_dir.x;
			float fDist = abs(m_centerpos.x - curpos.x) - m_fMaxDis;
			if (fDist > 0.f)
			{
				m_dir.x *= -1.f;
				curpos.x += fDist * m_dir.x;
			}
			m_sprite.setPosition(curpos);
			m_eState = ENEMY_STATE::ATTACTK_CIRCLE;
			break;
		case ENEMY_STATE::ATTACTK_CIRCLE:
			{
				if (m_shootTimer > m_shootTimerMax)
				{

				}
			}
			break;
		case ENEMY_STATE::ATTACTK_DEFAULT:
			break;
		case ENEMY_STATE::ATTACK_AROUND:
			break;
		default:
			break;
		}
	}
		break;
	case ENEMY::BOSS1:
		break;
	}

}

void Enemy::UiUpdate()
{
	m_hpBar.setPosition(m_sprite.getPosition().x -
		m_sprite.getGlobalBounds().width / 2,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height / 2);
	m_hpBarback.setPosition(m_sprite.getPosition().x -
		m_sprite.getGlobalBounds().width / 2,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height / 2);
	m_hpBar.setScale((float)m_hp / (float)m_hpMax, 1.f);

}
