#include "pch.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AI.h"
#include "Idle_State.h"
#include "AttackAround_State.h"
Enemy::Enemy(Vector2f _pos, Vector2f _dir, Vector2f _scale, ENEMY _eType, 
	int _hpMax, int _damagemin, int _damagemax, int _followplayernum)
{
	m_pAI = new AI;
	m_pAI->m_pOwner = this;
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
	case ENEMY::FOLLOWFAST:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Enemy01"));
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
			m_sprite.getGlobalBounds().height / 2);
		m_sprite.setScale(Vector2f(0.07f,0.07f));
		m_sprite.setPosition(_pos);
	}
		break;
	case ENEMY::FOLLOWSHOOT:
	case ENEMY::FOLLOWFASTSHOOT:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Enemyshoot"));
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
			m_sprite.getGlobalBounds().height / 2);
		m_sprite.setScale(Vector2f(0.2f, 0.2f));
		m_sprite.setRotation(270);
		m_shootTimerMax = 50.f;
		m_shootTimer = 0.f;
		m_sprite.setPosition(_pos);
	}
		break;
	case ENEMY::ELITE:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Elite"));
		m_sprite.setPosition(Vector2f(SCREEN_WIDTH / 2, 100.f));
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
			m_sprite.getGlobalBounds().height / 2);
		m_sprite.setScale(Vector2f(2.f,2.f));
		m_eState = ENEMY_STATE::READY;
		m_centerpos = _pos;
		m_fMaxDis = SCREEN_WIDTH - m_sprite.getGlobalBounds().width * 3;
		
		m_pAI->AddState(new Idle_State);
		m_pAI->AddState(new AttackAround_State);
	}
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
		- m_sprite.getGlobalBounds().width /2,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height / 2);
	m_hpBarback = m_hpBar;
	m_hpBarback.setFillColor(Color(25, 25, 25, 200));
	m_damageTimer = 0;
	m_damageTimerMax = 4;
	m_followPlayernum = _followplayernum;
}

Enemy::~Enemy()
{
	if (nullptr != m_pAI)
		delete m_pAI;
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
	if (m_shootTimer < m_shootTimerMax)
		m_shootTimer++;
	MoveMent(_dt, _playerpos);
	UiUpdate();
	if (m_damageTimer > 0.f)
	{
		m_damageTimer--;
		m_sprite.setColor(Color::Red);
		//m_sprite.move(0.f, -m_dir.y * 100.f * _dt);
		m_sprite.move(m_normalizedir.x * 100.f * _dt,
					m_normalizedir.y * 100.f * _dt);
	}
	else
	{
		m_sprite.setColor(Color::White);
	}
	if(m_sprite.getPosition().y > SCREEN_HEIGHT)
		return true;
	return false;
}

void Enemy::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBarback);
	WindowMgr::GetInst()->GetWindow().draw(m_hpBar);
	for (auto& e : m_vecBullet)
		e.Render();
}

void Enemy::MoveMent(const float& _dt, Vector2f _playerpos)
{
	switch (m_eType)
	{
	case ENEMY::MOVEDOWN:
		m_sprite.move(m_dir.x * 80.f * _dt, m_dir.y * 80.f * _dt);
		break;
	case ENEMY::FOLLOW:
		// ������ ��������.
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
		if (m_sprite.getPosition().y < _playerpos.y)
		{
			m_dir.x = _playerpos.x - m_sprite.getPosition().x;
			m_dir.y = _playerpos.y - m_sprite.getPosition().y;
		}
		m_normalizedir = Normalize(m_dir, vectorLength(m_dir));
		m_sprite.setRotation(atan2(m_normalizedir.y, m_normalizedir.x) * 180 / M_PI + 180);
		m_sprite.move(m_normalizedir.x * 200.f * _dt, m_normalizedir.y * 200.f * _dt);
		break;
	case ENEMY::FOLLOWSHOOT:
	{
		// �÷��̾� ��ġ - �� ��ġ => ����.
		m_lookdir = _playerpos - m_sprite.getPosition();
		m_normalizelookdir = Normalize(m_lookdir, vectorLength(m_lookdir));
		m_sprite.setRotation(atan2(m_normalizelookdir.y, m_normalizelookdir.x) * 180 / M_PI + 180);

		m_normalizedir = Normalize(m_dir, vectorLength(m_dir));
		m_sprite.move(m_normalizedir * 300.f * _dt);

		// follow shoot�� �Ѿ��� ���.
		if (m_shootTimer >= m_shootTimerMax)
		{
			m_vecBullet.push_back(Bullet(m_sprite.getPosition(), 1.f, 30.f,
				m_normalizelookdir, 10.f, WEAPON::ENEMY_BULLET));
			m_shootTimer = 0.f;
		}
	}
	break;
	case ENEMY::FOLLOWFASTSHOOT:
		break;
	case ENEMY::ELITE:
	{
		m_pAI->ChangeState(ENEMY_STATE::IDLE);
		if (m_shootTimer < m_shootTimerMax)
			m_shootTimer++;

		if (m_shootTimer >= m_shootTimerMax)
		{
			// 12����ź
			m_pAI->ChangeState(ENEMY_STATE::ATTACK_AROUND);
			//m_eState = ENEMY_STATE::ATTACK_CIRCLE;
			m_shootTimer = 0.f;
		}
	};
	//	case ENEMY_STATE::ATTACK_CIRCLE:
	//	{
	//		if (m_clock.getElapsedTime().asSeconds() > 0.5f)
	//		{
	//			m_vecBullet.push_back(Bullet(Vector2f(m_sprite.getPosition()),
	//				2.f, 50.f, Vector2f(-1.f, 0.f), 2.f, WEAPON::ROTATE));
	//			m_clock.restart();

	//		}
	//		if (m_nextclock.getElapsedTime().asSeconds() > 5.f)
	//		{
	//			//m_eState = ENEMY_STATE::IDLE;
	//			m_nextclock.restart();
	//		}
	//	}
	//	break;
	//	case ENEMY_STATE::READY:
	//	{
	//		if (m_clock.getElapsedTime().asSeconds() > 0.1f)
	//		{
	//			m_vecBullet.push_back(Bullet(Vector2f(m_sprite.getPosition()),
	//				2.f, 50.f, Vector2f(-1.f, 0.f), 2.f, WEAPON::ONLYROTATE));
	//			m_clock.restart();
	//		}
	//		if (m_nextclock.getElapsedTime().asSeconds() > 5.f)
	//		{
	//			m_eState = ENEMY_STATE::ATTACK_PLAYER;
	//			m_nextclock.restart();
	//		}
	//	}
	//		break;
	//	case ENEMY_STATE::ATTACK_PLAYER:
	//	{
	//		m_dir = _playerpos - m_sprite.getPosition();
	//		m_normalizedir = Normalize(m_dir, vectorLength(m_dir));
	//		m_sprite.move(m_normalizedir * 100.f * _dt);

	//	}
	//	break;
	//	case ENEMY_STATE::BACK:
	//	{

	//	}
	//	break;
	//	}

	//}
	//break;
	//case ENEMY::BOSS1:
	//{
	//}
	//	break;
	//}
	for (auto& e : m_vecBullet)
		e.Update(_dt, m_sprite);
	}
}

void Enemy::UiUpdate()
{
	m_hpBar.setPosition(m_sprite.getPosition().x - 
		m_sprite.getGlobalBounds().width /2,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height / 2);
	m_hpBarback.setPosition(m_sprite.getPosition().x -
		m_sprite.getGlobalBounds().width / 2,
		m_sprite.getPosition().y +
		m_sprite.getGlobalBounds().height / 2);
	m_hpBar.setScale((float)m_hp / (float)m_hpMax, 1.f);

}
