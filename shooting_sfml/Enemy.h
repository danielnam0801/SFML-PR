#pragma once
#include<assert.h>
#include "Bullet.h"
class AI;
class Enemy
{
public:
	Enemy(Vector2f _pos, Vector2f _dir, Vector2f _scale, ENEMY _eType,
		int _hpMax, int _damagemin, int _damagemax,
		int _followplayernum);
	~Enemy();
public:
	void TakeDamage(int _damage);
	bool Update(const float& _dt, Vector2f _playerpos);
	void Render();
private:
	void MoveMent(const float& _dt, Vector2f _playerpos);
	void UiUpdate();
public:
					// 데미지를 1 ~ 10
	const int& GetDamage() const 
	{ return rand() % (m_damagemax - m_damagemin)+ m_damagemin; }
	const Vector2f& GetDir() const
	{
		return m_dir;
	}
	const Vector2f& GetCenterPos() const
	{
		return m_centerpos;
	}
	std::vector<Bullet>& GetBullet() { return m_vecBullet; }
	const float& GetMaxDis() const{ return m_fMaxDis; }
	const Sprite& GetSprite() const { return m_sprite; }
	const int& GetHp() const { return m_hp; }
	const int& GetHpMax() const { return m_hpMax; }
	const bool& GetIsDead() const { return m_hp <= 0; }
	const int& GetFollownum() const { return m_followPlayernum; }
	const Clock& GetClock() const { return m_clock; }
	void SetFollownum(int _num)
	{
		m_followPlayernum = _num;
		if (m_followPlayernum < 0)
			m_followPlayernum = 0;
	}
	void SetDir(Vector2f m_Dir)
	{
		m_dir = m_Dir;
	}
	void SetPos(Vector2f pos)
	{
		m_sprite.setPosition(pos);
	}
	void SetState(ENEMY_STATE _state)
	{
		m_eState = _state;
	}
public:
	float vectorLength(Vector2f _vec)
	{
		return sqrt(pow(_vec.x, 2) + pow(_vec.y, 2));
	}
	Vector2f Normalize(Vector2f _vec, float _length)
	{
		assert(_length != 0.f);
		return _vec / _length;
	}
private:
	AI* m_pAI;
	sf::Clock m_nextclock;
	sf::Clock m_clock;
	float m_fMaxDis;
	Vector2f m_centerpos;
	ENEMY_STATE m_eState;
	int m_followPlayernum;
	int m_damageTimer;	int m_damageTimerMax;
	Sprite m_sprite;
	ENEMY m_eType;
	int  m_hp; int m_hpMax;
	int m_damagemin; int m_damagemax;
	Vector2f m_dir;
	Vector2f m_normalizedir;

	Vector2f m_lookdir;
	Vector2f m_normalizelookdir;
	std::vector<Bullet> m_vecBullet;
	float m_shootTimer;
	float m_shootTimerMax;

	sf::RectangleShape m_hpBar;
	sf::RectangleShape m_hpBarback;
};

